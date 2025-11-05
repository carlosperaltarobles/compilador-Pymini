/**
 * codegen_c.c - Generador de código C desde AST anotado
 */
#include "codegen_c.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/* ========== Helpers de Indentación y Output ========== */

static void emit_indent(CodegenCtx* ctx) {
    for (int i = 0; i < ctx->indent_level; i++) {
        fprintf(ctx->out, "    ");
    }
}

static void emit_line(CodegenCtx* ctx, const char* fmt, ...) {
    emit_indent(ctx);
    va_list args;
    va_start(args, fmt);
    vfprintf(ctx->out, fmt, args);
    va_end(args);
    fprintf(ctx->out, "\n");
}

static void emit_raw(CodegenCtx* ctx, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(ctx->out, fmt, args);
    va_end(args);
}

/* ========== Forward Declarations ========== */

static void codegen_expr(CodegenCtx* ctx, Ast* node);
static void codegen_stmt(CodegenCtx* ctx, Ast* node);
static void codegen_stmt_list(CodegenCtx* ctx, Ast* node);

/* ========== Nombre de tipo C ========== */

static const char* type_to_c(Type t) {
    switch (t) {
        case TY_INT:
        case TY_BOOL:
            return "int";
        default:
            return "int"; // fallback
    }
}

/* ========== Generación de Expresiones ========== */

static void codegen_bin_op(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_BIN_OP);
    
    // Para operadores lógicos con short-circuit, usamos && y ||
    const char* op_str = NULL;
    switch (node->data.bin_op.op) {
        case OP_ADD: op_str = "+"; break;
        case OP_SUB: op_str = "-"; break;
        case OP_MUL: op_str = "*"; break;
        case OP_DIV:
            if (ctx->opts.use_runtime_checks) {
                emit_raw(ctx, "rt_div(");
                codegen_expr(ctx, node->data.bin_op.left);
                emit_raw(ctx, ", ");
                codegen_expr(ctx, node->data.bin_op.right);
                emit_raw(ctx, ")");
                return;
            } else {
                op_str = "/";
            }
            break;
        case OP_MOD:
            if (ctx->opts.use_runtime_checks) {
                emit_raw(ctx, "rt_mod(");
                codegen_expr(ctx, node->data.bin_op.left);
                emit_raw(ctx, ", ");
                codegen_expr(ctx, node->data.bin_op.right);
                emit_raw(ctx, ")");
                return;
            } else {
                op_str = "%";
            }
            break;
        case OP_EQ:  op_str = "=="; break;
        case OP_NE:  op_str = "!="; break;
        case OP_LT:  op_str = "<"; break;
        case OP_LE:  op_str = "<="; break;
        case OP_GT:  op_str = ">"; break;
        case OP_GE:  op_str = ">="; break;
        case OP_AND: op_str = "&&"; break;
        case OP_OR:  op_str = "||"; break;
        default:
            fprintf(stderr, "Codegen Error: Unknown binary operator\n");
            ctx->had_error = true;
            return;
    }
    
    emit_raw(ctx, "(");
    codegen_expr(ctx, node->data.bin_op.left);
    emit_raw(ctx, " %s ", op_str);
    codegen_expr(ctx, node->data.bin_op.right);
    emit_raw(ctx, ")");
}

static void codegen_un_op(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_UN_OP);
    
    const char* op_str = NULL;
    switch (node->data.un_op.op) {
        case OP_NEG: op_str = "-"; break;
        case OP_NOT: op_str = "!"; break;
        default:
            fprintf(stderr, "Codegen Error: Unknown unary operator\n");
            ctx->had_error = true;
            return;
    }
    
    emit_raw(ctx, "(%s", op_str);
    codegen_expr(ctx, node->data.un_op.operand);
    emit_raw(ctx, ")");
}

static void codegen_call(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_CALL);
    
    emit_raw(ctx, "%s(", node->data.call.name);
    
    if (node->data.call.args) {
        Ast* args = node->data.call.args;
        for (size_t i = 0; i < args->data.list.count; i++) {
            if (i > 0) emit_raw(ctx, ", ");
            codegen_expr(ctx, args->data.list.exprs[i]);
        }
    }
    
    emit_raw(ctx, ")");
}

static void codegen_expr(CodegenCtx* ctx, Ast* node) {
    if (!node) return;
    
    switch (node->kind) {
        case AST_INT_LIT:
            emit_raw(ctx, "%d", node->data.int_lit.value);
            break;
            
        case AST_BOOL_LIT:
            emit_raw(ctx, "%d", node->data.bool_lit.value ? 1 : 0);
            break;
            
        case AST_NAME:
            emit_raw(ctx, "%s", node->data.name.id);
            break;
            
        case AST_BIN_OP:
            codegen_bin_op(ctx, node);
            break;
            
        case AST_UN_OP:
            codegen_un_op(ctx, node);
            break;
            
        case AST_CALL:
            codegen_call(ctx, node);
            break;
        
        case AST_INPUT:
            emit_raw(ctx, "rt_input_int()");
            break;
            
        default:
            fprintf(stderr, "Codegen Error: Unexpected expression kind %d\n", node->kind);
            ctx->had_error = true;
            break;
    }
}

/* ========== Generación de Sentencias ========== */

static void codegen_assign(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_ASSIGN);
    emit_indent(ctx);
    emit_raw(ctx, "%s = ", node->data.assign.name);
    codegen_expr(ctx, node->data.assign.value);
    emit_raw(ctx, ";\n");
}

static void codegen_print(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_PRINT);
    emit_indent(ctx);
    
    // Determinar si es bool o int según el tipo inferido
    Type expr_type = node->data.print.expr->type;
    
    if (expr_type == TY_BOOL) {
        emit_raw(ctx, "rt_print_bool(");
    } else {
        emit_raw(ctx, "rt_print_int(");
    }
    
    codegen_expr(ctx, node->data.print.expr);
    emit_raw(ctx, ");\n");
}

static void codegen_return(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_RETURN);
    emit_indent(ctx);
    emit_raw(ctx, "return");
    if (node->data.ret.expr) {
        emit_raw(ctx, " ");
        codegen_expr(ctx, node->data.ret.expr);
    }
    emit_raw(ctx, ";\n");
}

static void codegen_if(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_IF);
    
    // if
    emit_indent(ctx);
    emit_raw(ctx, "if (");
    codegen_expr(ctx, node->data.if_stmt.condition);
    emit_raw(ctx, ") {\n");
    
    ctx->indent_level++;
    codegen_stmt_list(ctx, node->data.if_stmt.then_block->data.block.stmts);
    ctx->indent_level--;
    emit_line(ctx, "}");
    
    // elif
    if (node->data.if_stmt.elif_list) {
        Ast* elif_list = node->data.if_stmt.elif_list;
        for (size_t i = 0; i < elif_list->data.elif_list.count; i++) {
            Ast* elif = elif_list->data.elif_list.elifs[i];
            emit_indent(ctx);
            emit_raw(ctx, "else if (");
            codegen_expr(ctx, elif->data.elif.condition);
            emit_raw(ctx, ") {\n");
            
            ctx->indent_level++;
            codegen_stmt_list(ctx, elif->data.elif.block->data.block.stmts);
            ctx->indent_level--;
            emit_line(ctx, "}");
        }
    }
    
    // else
    if (node->data.if_stmt.else_block) {
        emit_line(ctx, "else {");
        ctx->indent_level++;
        codegen_stmt_list(ctx, node->data.if_stmt.else_block->data.else_stmt.block->data.block.stmts);
        ctx->indent_level--;
        emit_line(ctx, "}");
    }
}

static void codegen_while(CodegenCtx* ctx, Ast* node) {
    assert(node->kind == AST_WHILE);
    
    emit_indent(ctx);
    emit_raw(ctx, "while (");
    codegen_expr(ctx, node->data.while_stmt.condition);
    emit_raw(ctx, ") {\n");
    
    ctx->indent_level++;
    codegen_stmt_list(ctx, node->data.while_stmt.body->data.block.stmts);
    ctx->indent_level--;
    emit_line(ctx, "}");
}

static void codegen_stmt(CodegenCtx* ctx, Ast* node) {
    if (!node) return;
    
    switch (node->kind) {
        case AST_ASSIGN:
            codegen_assign(ctx, node);
            break;
            
        case AST_PRINT:
            codegen_print(ctx, node);
            break;
            
        case AST_RETURN:
            codegen_return(ctx, node);
            break;
            
        case AST_IF:
            codegen_if(ctx, node);
            break;
            
        case AST_WHILE:
            codegen_while(ctx, node);
            break;
            
        case AST_EXPR_STMT:
            emit_indent(ctx);
            codegen_expr(ctx, node);
            emit_raw(ctx, ";\n");
            break;
            
        default:
            fprintf(stderr, "Codegen Error: Unexpected statement kind %d\n", node->kind);
            ctx->had_error = true;
            break;
    }
}

static void codegen_stmt_list(CodegenCtx* ctx, Ast* node) {
    if (!node || node->kind != AST_STMT_LIST) return;
    
    for (size_t i = 0; i < node->data.stmt_list.count; i++) {
        codegen_stmt(ctx, node->data.stmt_list.stmts[i]);
    }
}

/* ========== Recolección de Variables Locales ========== */

typedef struct {
    char** names;
    size_t count;
    size_t capacity;
} VarSet;

static VarSet varset_new(void) {
    VarSet vs;
    vs.capacity = 16;
    vs.count = 0;
    vs.names = malloc(sizeof(char*) * vs.capacity);
    return vs;
}

static void varset_free(VarSet* vs) {
    free(vs->names);
}

static bool varset_contains(VarSet* vs, const char* name) {
    for (size_t i = 0; i < vs->count; i++) {
        if (strcmp(vs->names[i], name) == 0) return true;
    }
    return false;
}

static void varset_add(VarSet* vs, const char* name) {
    if (varset_contains(vs, name)) return;
    
    if (vs->count >= vs->capacity) {
        vs->capacity *= 2;
        vs->names = realloc(vs->names, sizeof(char*) * vs->capacity);
    }
    vs->names[vs->count++] = (char*)name;
}

static void collect_vars_from_expr(VarSet* vs, Ast* node) {
    if (!node) return;
    
    switch (node->kind) {
        case AST_NAME:
            varset_add(vs, node->data.name.id);
            break;
        case AST_BIN_OP:
            collect_vars_from_expr(vs, node->data.bin_op.left);
            collect_vars_from_expr(vs, node->data.bin_op.right);
            break;
        case AST_UN_OP:
            collect_vars_from_expr(vs, node->data.un_op.operand);
            break;
        case AST_CALL:
            if (node->data.call.args) {
                Ast* args = node->data.call.args;
                for (size_t i = 0; i < args->data.list.count; i++) {
                    collect_vars_from_expr(vs, args->data.list.exprs[i]);
                }
            }
            break;
        default:
            break;
    }
}

static void collect_vars_from_stmt(VarSet* vs, Ast* node);

static void collect_vars_from_stmt_list(VarSet* vs, Ast* node) {
    if (!node || node->kind != AST_STMT_LIST) return;
    for (size_t i = 0; i < node->data.stmt_list.count; i++) {
        collect_vars_from_stmt(vs, node->data.stmt_list.stmts[i]);
    }
}

static void collect_vars_from_stmt(VarSet* vs, Ast* node) {
    if (!node) return;
    
    switch (node->kind) {
        case AST_ASSIGN:
            varset_add(vs, node->data.assign.name);
            collect_vars_from_expr(vs, node->data.assign.value);
            break;
        case AST_PRINT:
            collect_vars_from_expr(vs, node->data.print.expr);
            break;
        case AST_RETURN:
            collect_vars_from_expr(vs, node->data.ret.expr);
            break;
        case AST_IF:
            collect_vars_from_expr(vs, node->data.if_stmt.condition);
            collect_vars_from_stmt_list(vs, node->data.if_stmt.then_block->data.block.stmts);
            if (node->data.if_stmt.elif_list) {
                Ast* elif_list = node->data.if_stmt.elif_list;
                for (size_t i = 0; i < elif_list->data.elif_list.count; i++) {
                    Ast* elif = elif_list->data.elif_list.elifs[i];
                    collect_vars_from_expr(vs, elif->data.elif.condition);
                    collect_vars_from_stmt_list(vs, elif->data.elif.block->data.block.stmts);
                }
            }
            if (node->data.if_stmt.else_block) {
                collect_vars_from_stmt_list(vs, node->data.if_stmt.else_block->data.else_stmt.block->data.block.stmts);
            }
            break;
        case AST_WHILE:
            collect_vars_from_expr(vs, node->data.while_stmt.condition);
            collect_vars_from_stmt_list(vs, node->data.while_stmt.body->data.block.stmts);
            break;
        default:
            break;
    }
}

/* ========== Generación de Funciones ========== */

static void codegen_func_def(CodegenCtx* ctx, Ast* node, Scope* scope) {
    assert(node->kind == AST_FUNC_DEF);
    
    // Buscar símbolo de función
    Symbol* func_sym = sym_lookup(scope, node->data.func_def.name);
    if (!func_sym) {
        fprintf(stderr, "Codegen Error: Function symbol not found: %s\n", node->data.func_def.name);
        ctx->had_error = true;
        return;
    }
    
    // Determinar tipo de retorno
    Type ret_type = func_sym->return_type;
    if (ret_type == TY_UNKNOWN) ret_type = TY_INT; // default
    
    const char* c_ret_type = type_to_c(ret_type);
    
    // Firma de función
    fprintf(ctx->out, "%s %s(", c_ret_type, node->data.func_def.name);
    
    Ast* params = node->data.func_def.params;
    if (params && params->data.list.count > 0) {
        for (size_t i = 0; i < params->data.list.count; i++) {
            if (i > 0) fprintf(ctx->out, ", ");
            Type param_type = func_sym->param_types[i];
            fprintf(ctx->out, "%s %s", type_to_c(param_type), params->data.list.names[i]);
        }
    } else {
        fprintf(ctx->out, "void");
    }
    
    fprintf(ctx->out, ") {\n");
    
    ctx->indent_level++;
    ctx->current_func = func_sym;
    
    // Recolectar variables locales (excluyendo parámetros)
    VarSet vars = varset_new();
    Ast* body_stmts = node->data.func_def.body->data.block.stmts;
    collect_vars_from_stmt_list(&vars, body_stmts);
    
    // Remover parámetros del set de variables
    if (params) {
        for (size_t i = 0; i < params->data.list.count; i++) {
            // No agregamos parámetros como variables locales
            const char* param_name = params->data.list.names[i];
            for (size_t j = 0; j < vars.count; j++) {
                if (strcmp(vars.names[j], param_name) == 0) {
                    // Remover
                    vars.names[j] = vars.names[vars.count - 1];
                    vars.count--;
                    break;
                }
            }
        }
    }
    
    // Declarar variables locales
    if (vars.count > 0) {
        for (size_t i = 0; i < vars.count; i++) {
            emit_line(ctx, "int %s;", vars.names[i]);
        }
        fprintf(ctx->out, "\n");
    }
    
    varset_free(&vars);
    
    // Generar cuerpo
    codegen_stmt_list(ctx, body_stmts);
    
    ctx->current_func = NULL;
    ctx->indent_level--;
    
    fprintf(ctx->out, "}\n\n");
}

/* ========== Función Principal ========== */

CodegenOptions codegen_default_options(void) {
    CodegenOptions opts;
    opts.emit_comments = false;
    opts.use_runtime_checks = true;
    return opts;
}

int codegen_emit_c(Ast* root, Scope* global_scope, const CodegenOptions* opts, FILE* out) {
    if (!root || !out) return 1;
    if (root->kind != AST_PROGRAM) return 1;
    
    CodegenCtx ctx;
    ctx.out = out;
    ctx.opts = opts ? *opts : codegen_default_options();
    ctx.global_scope = global_scope;
    ctx.current_func = NULL;
    ctx.indent_level = 0;
    ctx.had_error = false;
    
    // Prólogo
    fprintf(out, "/* Generated by PyMini Compiler */\n");
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include \"runtime.h\"\n\n");
    
    Ast* body = root->data.program.body;
    if (!body || body->kind != AST_STMT_LIST) {
        fprintf(stderr, "Codegen Error: Invalid program body\n");
        return 1;
    }
    
    // Primera pasada: recolectar prototipos de funciones
    for (size_t i = 0; i < body->data.stmt_list.count; i++) {
        Ast* stmt = body->data.stmt_list.stmts[i];
        if (stmt->kind == AST_FUNC_DEF) {
            Symbol* func_sym = sym_lookup(global_scope, stmt->data.func_def.name);
            if (!func_sym) continue;
            
            Type ret_type = func_sym->return_type;
            if (ret_type == TY_UNKNOWN) ret_type = TY_INT;
            
            fprintf(out, "%s %s(", type_to_c(ret_type), stmt->data.func_def.name);
            
            Ast* params = stmt->data.func_def.params;
            if (params && params->data.list.count > 0) {
                for (size_t j = 0; j < params->data.list.count; j++) {
                    if (j > 0) fprintf(out, ", ");
                    fprintf(out, "%s", type_to_c(func_sym->param_types[j]));
                }
            } else {
                fprintf(out, "void");
            }
            
            fprintf(out, ");\n");
        }
    }
    fprintf(out, "\n");
    
    // Segunda pasada: generar funciones
    for (size_t i = 0; i < body->data.stmt_list.count; i++) {
        Ast* stmt = body->data.stmt_list.stmts[i];
        if (stmt->kind == AST_FUNC_DEF) {
            codegen_func_def(&ctx, stmt, global_scope);
        }
    }
    
    // Generar __pymini_main con statements top-level
    fprintf(out, "int __pymini_main(void) {\n");
    ctx.indent_level = 1;
    
    // Recolectar variables globales
    VarSet global_vars = varset_new();
    for (size_t i = 0; i < body->data.stmt_list.count; i++) {
        Ast* stmt = body->data.stmt_list.stmts[i];
        if (stmt->kind != AST_FUNC_DEF) {
            collect_vars_from_stmt(&global_vars, stmt);
        }
    }
    
    // Declarar variables globales
    if (global_vars.count > 0) {
        for (size_t i = 0; i < global_vars.count; i++) {
            emit_line(&ctx, "int %s;", global_vars.names[i]);
        }
        fprintf(out, "\n");
    }
    varset_free(&global_vars);
    
    // Generar statements top-level
    for (size_t i = 0; i < body->data.stmt_list.count; i++) {
        Ast* stmt = body->data.stmt_list.stmts[i];
        if (stmt->kind != AST_FUNC_DEF) {
            codegen_stmt(&ctx, stmt);
        }
    }
    
    emit_line(&ctx, "return 0;");
    fprintf(out, "}\n");
    
    return ctx.had_error ? 1 : 0;
}
