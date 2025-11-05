/* sema.c - Análisis Semántico para PyMini */

#include "sema.h"
#include "diag.h"
#include "types.h"
#include <stdio.h>
#include <string.h>

/* ========== Declaraciones Forward ========== */

static Type sema_visit_expr(SemaCtx* ctx, Ast* node);
static void sema_visit_stmt(SemaCtx* ctx, Ast* node);
static void sema_collect_functions(SemaCtx* ctx, Ast* node);

/* ========== Utilidades de Chequeo de Tipos ========== */

static Type check_bin_op_types(SemaCtx* ctx, Ast* node, Type left_ty, Type right_ty) {
    (void)ctx;
    
    if (left_ty == TY_ERROR || right_ty == TY_ERROR) {
        return TY_ERROR;
    }
    
    OpKind op = node->data.bin_op.op;
    
    // Operadores aritméticos
    if (op == OP_ADD || op == OP_SUB || op == OP_MUL || op == OP_DIV || op == OP_MOD) {
        if (left_ty != TY_INT || right_ty != TY_INT) {
            diag_error(node->loc.line, node->loc.column,
                "operador aritmético '%s' requiere int (encontrado %s y %s)",
                op_kind_to_string(op), type_name(left_ty), type_name(right_ty));
            return TY_ERROR;
        }
        return TY_INT;
    }
    
    // Comparaciones de igualdad
    if (op == OP_EQ || op == OP_NE) {
        if (!types_compatible(left_ty, right_ty)) {
            diag_error(node->loc.line, node->loc.column,
                "comparación de tipos incompatibles (%s vs %s)",
                type_name(left_ty), type_name(right_ty));
            return TY_ERROR;
        }
        return TY_BOOL;
    }
    
    // Comparaciones relacionales
    if (op == OP_LT || op == OP_LE || op == OP_GT || op == OP_GE) {
        if (left_ty != TY_INT || right_ty != TY_INT) {
            diag_error(node->loc.line, node->loc.column,
                "comparación '%s' requiere int (encontrado %s y %s)",
                op_kind_to_string(op), type_name(left_ty), type_name(right_ty));
            return TY_ERROR;
        }
        return TY_BOOL;
    }
    
    // Operadores lógicos
    if (op == OP_AND || op == OP_OR) {
        if (left_ty != TY_BOOL || right_ty != TY_BOOL) {
            diag_error(node->loc.line, node->loc.column,
                "operador lógico '%s' requiere bool (encontrado %s y %s)",
                op_kind_to_string(op), type_name(left_ty), type_name(right_ty));
            return TY_ERROR;
        }
        return TY_BOOL;
    }
    
    diag_error(node->loc.line, node->loc.column,
        "operador binario desconocido");
    return TY_ERROR;
}

static Type check_un_op_types(SemaCtx* ctx, Ast* node, Type operand_ty) {
    (void)ctx;
    
    if (operand_ty == TY_ERROR) {
        return TY_ERROR;
    }
    
    OpKind op = node->data.un_op.op;
    
    // Negación aritmética
    if (op == OP_NEG || op == OP_ADD) {  // unario + también existe
        if (operand_ty != TY_INT) {
            diag_error(node->loc.line, node->loc.column,
                "operador unario '%s' requiere int (encontrado %s)",
                op_kind_to_string(op), type_name(operand_ty));
            return TY_ERROR;
        }
        return TY_INT;
    }
    
    // Negación lógica
    if (op == OP_NOT) {
        if (operand_ty != TY_BOOL) {
            diag_error(node->loc.line, node->loc.column,
                "operador 'not' requiere bool (encontrado %s)",
                type_name(operand_ty));
            return TY_ERROR;
        }
        return TY_BOOL;
    }
    
    diag_error(node->loc.line, node->loc.column,
        "operador unario desconocido");
    return TY_ERROR;
}

/* ========== Pase 0: Recolección de Firmas de Funciones ========== */

static void sema_collect_functions(SemaCtx* ctx, Ast* node) {
    if (!node) return;
    
    
    if (node->kind == AST_PROGRAM) {
        sema_collect_functions(ctx, node->data.program.body);
        return;
    }
    
    if (node->kind == AST_STMT_LIST) {
        for (size_t i = 0; i < node->data.stmt_list.count; i++) {
            Ast* stmt = node->data.stmt_list.stmts[i];
            if (stmt->kind == AST_FUNC_DEF) {
                char* name = stmt->data.func_def.name;
                
                Symbol* existing = sym_lookup_current(ctx->scope, name);
                if (existing) {
                    diag_error(stmt->loc.line, stmt->loc.column,
                        "función '%s' ya declarada", name);
                    continue;
                }
                
                // Contar parámetros
                int arity = 0;
                if (stmt->data.func_def.params && stmt->data.func_def.params->kind == AST_PARAM_LIST) {
                    arity = (int)stmt->data.func_def.params->data.list.count;
                }
                
                Symbol func = sym_make_func(name, arity);
                sym_insert(ctx->scope, func);
            }
        }
    }
}

/* ========== Visitador de Expresiones ========== */

static Type sema_visit_expr(SemaCtx* ctx, Ast* node) {
    if (!node) return TY_UNKNOWN;
    
    switch (node->kind) {
        case AST_INT_LIT:
            node->type = TY_INT;
            return TY_INT;
        
        case AST_BOOL_LIT:
            node->type = TY_BOOL;
            return TY_BOOL;
        
        case AST_STRING_LIT:
            node->type = TY_STRING;
            return TY_STRING;
        
        case AST_NAME: {
            char* name = node->data.name.id;
            Symbol* sym = sym_lookup(ctx->scope, name);
            
            if (!sym) {
                diag_error(node->loc.line, node->loc.column,
                    "variable '%s' no declarada o usada antes de asignar", name);
                node->type = TY_ERROR;
                return TY_ERROR;
            }
            
            if (sym->kind == SYM_FUNC) {
                diag_error(node->loc.line, node->loc.column,
                    "'%s' es una función, no una variable", name);
                node->type = TY_ERROR;
                return TY_ERROR;
            }
            
            node->type = sym->type;
            return sym->type;
        }
        
        case AST_BIN_OP: {
            Type left_ty = sema_visit_expr(ctx, node->data.bin_op.left);
            Type right_ty = sema_visit_expr(ctx, node->data.bin_op.right);
            Type result_ty = check_bin_op_types(ctx, node, left_ty, right_ty);
            node->type = result_ty;
            return result_ty;
        }
        
        case AST_UN_OP: {
            Type operand_ty = sema_visit_expr(ctx, node->data.un_op.operand);
            Type result_ty = check_un_op_types(ctx, node, operand_ty);
            node->type = result_ty;
            return result_ty;
        }
        
        case AST_CALL: {
            char* name = node->data.call.name;
            Symbol* sym = sym_lookup(ctx->scope, name);
            
            if (!sym) {
                diag_error(node->loc.line, node->loc.column,
                    "función '%s' no declarada", name);
                node->type = TY_ERROR;
                return TY_ERROR;
            }
            
            if (sym->kind != SYM_FUNC) {
                diag_error(node->loc.line, node->loc.column,
                    "'%s' no es una función", name);
                node->type = TY_ERROR;
                return TY_ERROR;
            }
            
            // Contar argumentos
            int arg_count = 0;
            if (node->data.call.args && node->data.call.args->kind == AST_ARG_LIST) {
                arg_count = (int)node->data.call.args->data.list.count;
            }
            
            if (arg_count != sym->arity) {
                diag_error(node->loc.line, node->loc.column,
                    "función '%s' espera %d argumento(s), pero se le pasaron %d",
                    name, sym->arity, arg_count);
                node->type = TY_ERROR;
                return TY_ERROR;
            }
            
            // Visitar argumentos para chequear tipos
            if (node->data.call.args && node->data.call.args->kind == AST_ARG_LIST) {
                for (size_t i = 0; i < node->data.call.args->data.list.count; i++) {
                    sema_visit_expr(ctx, node->data.call.args->data.list.exprs[i]);
                }
            }
            
            node->type = TY_INT;  // Todas las funciones retornan int por defecto
            return TY_INT;
        }
        
        case AST_INPUT:
            // input() siempre retorna int
            node->type = TY_INT;
            return TY_INT;
        
        default:
            diag_error(node->loc.line, node->loc.column,
                "nodo inesperado en expresión");
            node->type = TY_ERROR;
            return TY_ERROR;
    }
}

/* ========== Visitador de Sentencias ========== */

static void sema_visit_stmt(SemaCtx* ctx, Ast* node) {
    if (!node) return;
    
    switch (node->kind) {
        case AST_PROGRAM: {
            sema_visit_stmt(ctx, node->data.program.body);
            break;
        }
        
        case AST_ASSIGN: {
            char* name = node->data.assign.name;
            Ast* value = node->data.assign.value;
            
            Type value_ty = sema_visit_expr(ctx, value);
            
            if (value_ty == TY_ERROR) return;
            
            Symbol* sym = sym_lookup_current(ctx->scope, name);
            
            if (!sym) {
                Symbol var = sym_make_var(name, value_ty);
                sym_insert(ctx->scope, var);
            } else {
                if (sym->kind != SYM_VAR) {
                    diag_error(node->loc.line, node->loc.column,
                        "'%s' ya existe como función", name);
                    return;
                }
                
                if (sym->type == TY_UNKNOWN) {
                    sym->type = value_ty;
                } else if (!types_compatible(sym->type, value_ty)) {
                    diag_error(node->loc.line, node->loc.column,
                        "reasignación de '%s' con tipo incompatible (esperado %s, encontrado %s)",
                        name, type_name(sym->type), type_name(value_ty));
                }
            }
            break;
        }
        
        case AST_PRINT: {
            Type expr_ty = sema_visit_expr(ctx, node->data.print.expr);
            if (expr_ty != TY_INT && expr_ty != TY_BOOL && expr_ty != TY_STRING && expr_ty != TY_ERROR) {
                diag_error(node->loc.line, node->loc.column,
                    "print() espera int, bool o str (encontrado %s)", type_name(expr_ty));
            }
            break;
        }
        
        case AST_RETURN: {
            if (!ctx->in_function) {
                diag_error(node->loc.line, node->loc.column,
                    "return fuera de función");
                return;
            }
            
            if (node->data.ret.expr) {
                sema_visit_expr(ctx, node->data.ret.expr);
            }
            break;
        }
        
        case AST_IF: {
            Type cond_ty = sema_visit_expr(ctx, node->data.if_stmt.condition);
            if (cond_ty != TY_BOOL && cond_ty != TY_ERROR) {
                diag_error(node->loc.line, node->loc.column,
                    "condición de 'if' debe ser bool (encontrado %s)", type_name(cond_ty));
            }
            
            sema_visit_stmt(ctx, node->data.if_stmt.then_block);
            
            if (node->data.if_stmt.elif_list) {
                sema_visit_stmt(ctx, node->data.if_stmt.elif_list);
            }
            
            if (node->data.if_stmt.else_block) {
                sema_visit_stmt(ctx, node->data.if_stmt.else_block);
            }
            break;
        }
        
        case AST_ELIF: {
            Type cond_ty = sema_visit_expr(ctx, node->data.elif.condition);
            if (cond_ty != TY_BOOL && cond_ty != TY_ERROR) {
                diag_error(node->loc.line, node->loc.column,
                    "condición de 'elif' debe ser bool (encontrado %s)", type_name(cond_ty));
            }
            sema_visit_stmt(ctx, node->data.elif.block);
            break;
        }
        
        case AST_ELIF_LIST: {
            for (size_t i = 0; i < node->data.elif_list.count; i++) {
                sema_visit_stmt(ctx, node->data.elif_list.elifs[i]);
            }
            break;
        }
        
        case AST_ELSE:
            sema_visit_stmt(ctx, node->data.else_stmt.block);
            break;
        
        case AST_WHILE: {
            Type cond_ty = sema_visit_expr(ctx, node->data.while_stmt.condition);
            if (cond_ty != TY_BOOL && cond_ty != TY_ERROR) {
                diag_error(node->loc.line, node->loc.column,
                    "condición de 'while' debe ser bool (encontrado %s)", type_name(cond_ty));
            }
            
            sema_visit_stmt(ctx, node->data.while_stmt.body);
            break;
        }
        
        case AST_FUNC_DEF: {
            char* name = node->data.func_def.name;
            Symbol* func_sym = sym_lookup_current(ctx->scope, name);
            
            if (!func_sym) {
                diag_error(node->loc.line, node->loc.column,
                    "función '%s' no encontrada en tabla (error interno)", name);
                return;
            }
            
            ctx->in_function = 1;
            ctx->current_func = func_sym;
            
            ctx->scope = scope_push(ctx->scope);
            
            // Añadir parámetros al scope
            if (node->data.func_def.params && node->data.func_def.params->kind == AST_PARAM_LIST) {
                Ast* params = node->data.func_def.params;
                if (params->data.list.names) {
                    for (size_t i = 0; i < params->data.list.count; i++) {
                        char* param_name = params->data.list.names[i];
                        if (param_name) {
                            Symbol param_var = sym_make_var(param_name, TY_INT);  // Por defecto int
                            sym_insert(ctx->scope, param_var);
                        }
                    }
                }
            }
            
            sema_visit_stmt(ctx, node->data.func_def.body);
            
            ctx->scope = scope_pop(ctx->scope);
            
            ctx->in_function = 0;
            ctx->current_func = NULL;
            break;
        }
        
        case AST_BLOCK: {
            sema_visit_stmt(ctx, node->data.block.stmts);
            break;
        }
        
        case AST_STMT_LIST: {
            for (size_t i = 0; i < node->data.stmt_list.count; i++) {
                sema_visit_stmt(ctx, node->data.stmt_list.stmts[i]);
            }
            break;
        }
        
        case AST_EXPR_STMT: {
            sema_visit_expr(ctx, node);
            break;
        }
        
        default:
            break;
    }
}

/* ========== Punto de Entrada ========== */

SemaResult sema_check_ex(Ast* root) {
    SemaResult result;
    result.error_count = 0;
    result.global_scope = NULL;
    
    if (!root) return result;
    
    diag_reset();
    
    SemaCtx ctx;
    ctx.scope = scope_push(NULL);
    ctx.in_function = 0;
    ctx.current_func = NULL;
    
    sema_collect_functions(&ctx, root);
    
    sema_visit_stmt(&ctx, root);
    
    result.error_count = g_error_count;
    result.global_scope = ctx.scope;
    
    return result;
}

int sema_check(Ast* root) {
    SemaResult result = sema_check_ex(root);
    if (result.global_scope) {
        scope_free(result.global_scope);
    }
    return result.error_count;
}
