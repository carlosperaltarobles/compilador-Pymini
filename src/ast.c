/* ast.c - Implementación del AST para PyMini */

#include "ast.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Declarar strdup si no está disponible */
#ifndef _GNU_SOURCE
extern char *strdup(const char *s);
#endif

/* ========== Utilidades Internas ========== */

static Ast* ast_alloc(AstKind kind, Location loc) {
    Ast* node = (Ast*)calloc(1, sizeof(Ast));
    if (!node) {
        fprintf(stderr, "Error: no se pudo asignar memoria para el nodo AST\n");
        exit(1);
    }
    node->kind = kind;
    node->loc = loc;
    node->type = TY_UNKNOWN;  // Inicializar tipo como desconocido
    return node;
}

static char* str_dup(const char* s) {
    if (!s) return NULL;
    char* copy = strdup(s);
    if (!copy) {
        fprintf(stderr, "Error: no se pudo asignar memoria para string\n");
        exit(1);
    }
    return copy;
}

/* ========== Constructores: Programa y Listas ========== */

Ast* ast_new_program(Ast* body, Location loc) {
    Ast* node = ast_alloc(AST_PROGRAM, loc);
    node->data.program.body = body;
    return node;
}

Ast* ast_new_stmt_list(Location loc) {
    Ast* node = ast_alloc(AST_STMT_LIST, loc);
    node->data.stmt_list.stmts = NULL;
    node->data.stmt_list.count = 0;
    node->data.stmt_list.capacity = 0;
    return node;
}

void ast_stmt_list_add(Ast* list, Ast* stmt) {
    if (!list || list->kind != AST_STMT_LIST) return;
    
    if (list->data.stmt_list.count >= list->data.stmt_list.capacity) {
        size_t new_cap = list->data.stmt_list.capacity == 0 ? 8 : list->data.stmt_list.capacity * 2;
        Ast** new_stmts = (Ast**)realloc(list->data.stmt_list.stmts, new_cap * sizeof(Ast*));
        if (!new_stmts) {
            fprintf(stderr, "Error: no se pudo expandir lista de statements\n");
            exit(1);
        }
        list->data.stmt_list.stmts = new_stmts;
        list->data.stmt_list.capacity = new_cap;
    }
    
    list->data.stmt_list.stmts[list->data.stmt_list.count++] = stmt;
}

/* ========== Constructores: Statements ========== */

Ast* ast_new_assign(char* name, Ast* value, Location loc) {
    Ast* node = ast_alloc(AST_ASSIGN, loc);
    node->data.assign.name = str_dup(name);
    node->data.assign.value = value;
    return node;
}

Ast* ast_new_print(Ast* expr, Location loc) {
    Ast* node = ast_alloc(AST_PRINT, loc);
    node->data.print.expr = expr;
    return node;
}

Ast* ast_new_return(Ast* expr, Location loc) {
    Ast* node = ast_alloc(AST_RETURN, loc);
    node->data.ret.expr = expr;
    return node;
}

Ast* ast_new_if(Ast* condition, Ast* then_block, Ast* elif_list, Ast* else_block, Location loc) {
    Ast* node = ast_alloc(AST_IF, loc);
    node->data.if_stmt.condition = condition;
    node->data.if_stmt.then_block = then_block;
    node->data.if_stmt.elif_list = elif_list;
    node->data.if_stmt.else_block = else_block;
    return node;
}

Ast* ast_new_elif(Ast* condition, Ast* block, Location loc) {
    Ast* node = ast_alloc(AST_ELIF, loc);
    node->data.elif.condition = condition;
    node->data.elif.block = block;
    return node;
}

Ast* ast_new_elif_list(Location loc) {
    Ast* node = ast_alloc(AST_ELIF_LIST, loc);
    node->data.elif_list.elifs = NULL;
    node->data.elif_list.count = 0;
    node->data.elif_list.capacity = 0;
    return node;
}

void ast_elif_list_add(Ast* list, Ast* elif) {
    if (!list || list->kind != AST_ELIF_LIST) return;
    
    if (list->data.elif_list.count >= list->data.elif_list.capacity) {
        size_t new_cap = list->data.elif_list.capacity == 0 ? 4 : list->data.elif_list.capacity * 2;
        Ast** new_elifs = (Ast**)realloc(list->data.elif_list.elifs, new_cap * sizeof(Ast*));
        if (!new_elifs) {
            fprintf(stderr, "Error: no se pudo expandir lista de elif\n");
            exit(1);
        }
        list->data.elif_list.elifs = new_elifs;
        list->data.elif_list.capacity = new_cap;
    }
    
    list->data.elif_list.elifs[list->data.elif_list.count++] = elif;
}

Ast* ast_new_else(Ast* block, Location loc) {
    Ast* node = ast_alloc(AST_ELSE, loc);
    node->data.else_stmt.block = block;
    return node;
}

Ast* ast_new_while(Ast* condition, Ast* body, Location loc) {
    Ast* node = ast_alloc(AST_WHILE, loc);
    node->data.while_stmt.condition = condition;
    node->data.while_stmt.body = body;
    return node;
}

Ast* ast_new_func_def(char* name, Ast* params, Ast* body, Location loc) {
    Ast* node = ast_alloc(AST_FUNC_DEF, loc);
    node->data.func_def.name = str_dup(name);
    node->data.func_def.params = params;
    node->data.func_def.body = body;
    return node;
}

Ast* ast_new_block(Ast* stmts, Location loc) {
    Ast* node = ast_alloc(AST_BLOCK, loc);
    node->data.block.stmts = stmts;
    return node;
}

/* ========== Constructores: Expresiones ========== */

Ast* ast_new_bin_op(OpKind op, Ast* left, Ast* right, Location loc) {
    Ast* node = ast_alloc(AST_BIN_OP, loc);
    node->data.bin_op.op = op;
    node->data.bin_op.left = left;
    node->data.bin_op.right = right;
    return node;
}

Ast* ast_new_un_op(OpKind op, Ast* operand, Location loc) {
    Ast* node = ast_alloc(AST_UN_OP, loc);
    node->data.un_op.op = op;
    node->data.un_op.operand = operand;
    return node;
}

Ast* ast_new_call(char* name, Ast* args, Location loc) {
    Ast* node = ast_alloc(AST_CALL, loc);
    node->data.call.name = str_dup(name);
    node->data.call.args = args;
    return node;
}

Ast* ast_new_input(Ast* prompt, Location loc) {
    Ast* node = ast_alloc(AST_INPUT, loc);
    node->data.input.prompt = prompt;
    return node;
}

Ast* ast_new_int_conv(Ast* expr, Location loc) {
    Ast* node = ast_alloc(AST_INT_CONV, loc);
    node->data.int_conv.expr = expr;
    return node;
}

Ast* ast_new_str_conv(Ast* expr, Location loc) {
    Ast* node = ast_alloc(AST_STR_CONV, loc);
    node->data.str_conv.expr = expr;
    return node;
}

Ast* ast_new_name(char* id, Location loc) {
    Ast* node = ast_alloc(AST_NAME, loc);
    node->data.name.id = str_dup(id);
    return node;
}

Ast* ast_new_int_lit(int value, Location loc) {
    Ast* node = ast_alloc(AST_INT_LIT, loc);
    node->data.int_lit.value = value;
    return node;
}

Ast* ast_new_bool_lit(bool value, Location loc) {
    Ast* node = ast_alloc(AST_BOOL_LIT, loc);
    node->data.bool_lit.value = value;
    return node;
}

Ast* ast_new_string_lit(char* value, Location loc) {
    Ast* node = ast_alloc(AST_STRING_LIT, loc);
    node->data.string_lit.value = value;
    return node;
}

/* ========== Constructores: Listas de Parámetros/Argumentos ========== */

Ast* ast_new_param_list(Location loc) {
    Ast* node = ast_alloc(AST_PARAM_LIST, loc);
    node->data.list.names = NULL;
    node->data.list.exprs = NULL;
    node->data.list.count = 0;
    node->data.list.capacity = 0;
    return node;
}

void ast_param_list_add(Ast* list, char* name) {
    if (!list || list->kind != AST_PARAM_LIST) return;
    
    if (list->data.list.count >= list->data.list.capacity) {
        size_t new_cap = list->data.list.capacity == 0 ? 4 : list->data.list.capacity * 2;
        char** new_names = (char**)realloc(list->data.list.names, new_cap * sizeof(char*));
        if (!new_names) {
            fprintf(stderr, "Error: no se pudo expandir lista de parámetros\n");
            exit(1);
        }
        list->data.list.names = new_names;
        list->data.list.capacity = new_cap;
    }
    
    list->data.list.names[list->data.list.count++] = str_dup(name);
}

Ast* ast_new_arg_list(Location loc) {
    Ast* node = ast_alloc(AST_ARG_LIST, loc);
    node->data.list.names = NULL;
    node->data.list.exprs = NULL;
    node->data.list.count = 0;
    node->data.list.capacity = 0;
    return node;
}

void ast_arg_list_add(Ast* list, Ast* expr) {
    if (!list || list->kind != AST_ARG_LIST) return;
    
    if (list->data.list.count >= list->data.list.capacity) {
        size_t new_cap = list->data.list.capacity == 0 ? 4 : list->data.list.capacity * 2;
        Ast** new_exprs = (Ast**)realloc(list->data.list.exprs, new_cap * sizeof(Ast*));
        if (!new_exprs) {
            fprintf(stderr, "Error: no se pudo expandir lista de argumentos\n");
            exit(1);
        }
        list->data.list.exprs = new_exprs;
        list->data.list.capacity = new_cap;
    }
    
    list->data.list.exprs[list->data.list.count++] = expr;
}

/* ========== Utilidades: Conversión a String ========== */

const char* ast_kind_to_string(AstKind kind) {
    switch (kind) {
        case AST_PROGRAM: return "Program";
        case AST_STMT_LIST: return "StmtList";
        case AST_ASSIGN: return "Assign";
        case AST_PRINT: return "Print";
        case AST_RETURN: return "Return";
        case AST_IF: return "If";
        case AST_ELIF: return "Elif";
        case AST_ELSE: return "Else";
        case AST_WHILE: return "While";
        case AST_FUNC_DEF: return "FuncDef";
        case AST_BLOCK: return "Block";
        case AST_EXPR_STMT: return "ExprStmt";
        case AST_BIN_OP: return "BinOp";
        case AST_UN_OP: return "UnOp";
        case AST_CALL: return "Call";
        case AST_INPUT: return "Input";
        case AST_INT_CONV: return "IntConv";
        case AST_STR_CONV: return "StrConv";
        case AST_NAME: return "Name";
        case AST_INT_LIT: return "IntLit";
        case AST_BOOL_LIT: return "BoolLit";
        case AST_STRING_LIT: return "StringLit";
        case AST_PARAM_LIST: return "ParamList";
        case AST_ARG_LIST: return "ArgList";
        case AST_ELIF_LIST: return "ElifList";
        default: return "Unknown";
    }
}

const char* op_kind_to_string(OpKind op) {
    switch (op) {
        case OP_ADD: return "+";
        case OP_SUB: return "-";
        case OP_MUL: return "*";
        case OP_DIV: return "/";
        case OP_MOD: return "%";
        case OP_EQ: return "==";
        case OP_NE: return "!=";
        case OP_LT: return "<";
        case OP_LE: return "<=";
        case OP_GT: return ">";
        case OP_GE: return ">=";
        case OP_AND: return "and";
        case OP_OR: return "or";
        case OP_NOT: return "not";
        case OP_NEG: return "-";
        default: return "?";
    }
}

/* ========== Liberación de Memoria ========== */

void ast_free(Ast* node) {
    if (!node) return;
    
    switch (node->kind) {
        case AST_PROGRAM:
            ast_free(node->data.program.body);
            break;
            
        case AST_STMT_LIST:
            for (size_t i = 0; i < node->data.stmt_list.count; i++) {
                ast_free(node->data.stmt_list.stmts[i]);
            }
            free(node->data.stmt_list.stmts);
            break;
            
        case AST_ASSIGN:
            free(node->data.assign.name);
            ast_free(node->data.assign.value);
            break;
            
        case AST_PRINT:
            ast_free(node->data.print.expr);
            break;
            
        case AST_RETURN:
            ast_free(node->data.ret.expr);
            break;
            
        case AST_IF:
            ast_free(node->data.if_stmt.condition);
            ast_free(node->data.if_stmt.then_block);
            ast_free(node->data.if_stmt.elif_list);
            ast_free(node->data.if_stmt.else_block);
            break;
            
        case AST_ELIF:
            ast_free(node->data.elif.condition);
            ast_free(node->data.elif.block);
            break;
            
        case AST_ELIF_LIST:
            for (size_t i = 0; i < node->data.elif_list.count; i++) {
                ast_free(node->data.elif_list.elifs[i]);
            }
            free(node->data.elif_list.elifs);
            break;
            
        case AST_ELSE:
            ast_free(node->data.else_stmt.block);
            break;
            
        case AST_WHILE:
            ast_free(node->data.while_stmt.condition);
            ast_free(node->data.while_stmt.body);
            break;
            
        case AST_FUNC_DEF:
            free(node->data.func_def.name);
            ast_free(node->data.func_def.params);
            ast_free(node->data.func_def.body);
            break;
            
        case AST_BLOCK:
            ast_free(node->data.block.stmts);
            break;
            
        case AST_BIN_OP:
            ast_free(node->data.bin_op.left);
            ast_free(node->data.bin_op.right);
            break;
            
        case AST_UN_OP:
            ast_free(node->data.un_op.operand);
            break;
            
        case AST_CALL:
            free(node->data.call.name);
            ast_free(node->data.call.args);
            break;
            
        case AST_INT_CONV:
            ast_free(node->data.int_conv.expr);
            break;
        
        case AST_STR_CONV:
            ast_free(node->data.str_conv.expr);
            break;
        
        case AST_INPUT:
            ast_free(node->data.input.prompt);
            break;
            
        case AST_NAME:
            free(node->data.name.id);
            break;
            
        case AST_PARAM_LIST:
            for (size_t i = 0; i < node->data.list.count; i++) {
                free(node->data.list.names[i]);
            }
            free(node->data.list.names);
            break;
            
        case AST_ARG_LIST:
            for (size_t i = 0; i < node->data.list.count; i++) {
                ast_free(node->data.list.exprs[i]);
            }
            free(node->data.list.exprs);
            break;
            
        case AST_STRING_LIT:
            free(node->data.string_lit.value);
            break;
            
        case AST_INT_LIT:
        case AST_BOOL_LIT:
        case AST_EXPR_STMT:
            /* Sin datos dinámicos */
            break;
            
        default:
            break;
    }
    
    free(node);
}
