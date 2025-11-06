/* ast.h - Definiciones del Árbol de Sintaxis Abstracta (AST) para PyMini */

#ifndef AST_H
#define AST_H

#include <stddef.h>
#include <stdbool.h>
#include "types.h"

/* ========== Tipos de Nodos AST ========== */

typedef enum {
    AST_PROGRAM,
    AST_STMT_LIST,
    AST_ASSIGN,
    AST_PRINT,
    AST_RETURN,
    AST_IF,
    AST_ELIF,
    AST_ELSE,
    AST_WHILE,
    AST_FUNC_DEF,
    AST_BLOCK,
    AST_EXPR_STMT,
    
    /* Expresiones */
    AST_BIN_OP,
    AST_UN_OP,
    AST_CALL,
    AST_INPUT,
    AST_INT_CONV,
    AST_STR_CONV,
    AST_NAME,
    AST_INT_LIT,
    AST_BOOL_LIT,
    AST_STRING_LIT,
    
    /* Listas y auxiliares */
    AST_PARAM_LIST,
    AST_ARG_LIST,
    AST_ELIF_LIST
} AstKind;

/* ========== Tipos de Operadores ========== */

typedef enum {
    OP_ADD,      // +
    OP_SUB,      // -
    OP_MUL,      // *
    OP_DIV,      // /
    OP_MOD,      // %
    OP_EQ,       // ==
    OP_NE,       // !=
    OP_LT,       // <
    OP_LE,       // <=
    OP_GT,       // >
    OP_GE,       // >=
    OP_AND,      // and
    OP_OR,       // or
    OP_NOT,      // not (unario)
    OP_NEG       // - (unario)
} OpKind;

/* ========== Estructura de Ubicación ========== */

typedef struct {
    int line;
    int column;
} Location;

/* ========== Estructura del AST ========== */

typedef struct Ast Ast;

struct Ast {
    AstKind kind;
    Location loc;
    Type type;  // Tipo inferido durante análisis semántico
    
    union {
        /* AST_PROGRAM */
        struct {
            Ast* body;  // AST_STMT_LIST
        } program;
        
        /* AST_STMT_LIST */
        struct {
            Ast** stmts;
            size_t count;
            size_t capacity;
        } stmt_list;
        
        /* AST_ASSIGN */
        struct {
            char* name;
            Ast* value;
        } assign;
        
        /* AST_PRINT */
        struct {
            Ast* expr;
        } print;
        
        /* AST_RETURN */
        struct {
            Ast* expr;  // puede ser NULL
        } ret;
        
        /* AST_IF */
        struct {
            Ast* condition;
            Ast* then_block;
            Ast* elif_list;  // AST_ELIF_LIST o NULL
            Ast* else_block; // AST_ELSE o NULL
        } if_stmt;
        
        /* AST_ELIF */
        struct {
            Ast* condition;
            Ast* block;
        } elif;
        
        /* AST_ELIF_LIST */
        struct {
            Ast** elifs;
            size_t count;
            size_t capacity;
        } elif_list;
        
        /* AST_ELSE */
        struct {
            Ast* block;
        } else_stmt;
        
        /* AST_WHILE */
        struct {
            Ast* condition;
            Ast* body;
        } while_stmt;
        
        /* AST_FUNC_DEF */
        struct {
            char* name;
            Ast* params;  // AST_PARAM_LIST o NULL
            Ast* body;    // AST_BLOCK
        } func_def;
        
        /* AST_BLOCK */
        struct {
            Ast* stmts;  // AST_STMT_LIST
        } block;
        
        /* AST_BIN_OP */
        struct {
            OpKind op;
            Ast* left;
            Ast* right;
        } bin_op;
        
        /* AST_UN_OP */
        struct {
            OpKind op;
            Ast* operand;
        } un_op;
        
        /* AST_CALL */
        struct {
            char* name;
            Ast* args;  // AST_ARG_LIST o NULL
        } call;
        
        /* AST_NAME */
        struct {
            char* id;
        } name;
        
        /* AST_INT_LIT */
        struct {
            int value;
        } int_lit;
        
        /* AST_BOOL_LIT */
        struct {
            bool value;
        } bool_lit;
        
        /* AST_STRING_LIT */
        struct {
            char* value;
        } string_lit;
        
        /* AST_INT_CONV */
        struct {
            Ast* expr;
        } int_conv;
        
        /* AST_STR_CONV */
        struct {
            Ast* expr;
        } str_conv;
        
        /* AST_INPUT */
        struct {
            Ast* prompt;  // expresión string opcional para el prompt
        } input;
        
        /* AST_PARAM_LIST / AST_ARG_LIST */
        struct {
            char** names;     // para params
            Ast** exprs;      // para args
            size_t count;
            size_t capacity;
        } list;
    } data;
};

/* ========== Funciones de Fábrica (Constructores) ========== */

Ast* ast_new_program(Ast* body, Location loc);
Ast* ast_new_stmt_list(Location loc);
void ast_stmt_list_add(Ast* list, Ast* stmt);

Ast* ast_new_assign(char* name, Ast* value, Location loc);
Ast* ast_new_print(Ast* expr, Location loc);
Ast* ast_new_return(Ast* expr, Location loc);
Ast* ast_new_if(Ast* condition, Ast* then_block, Ast* elif_list, Ast* else_block, Location loc);
Ast* ast_new_elif(Ast* condition, Ast* block, Location loc);
Ast* ast_new_elif_list(Location loc);
void ast_elif_list_add(Ast* list, Ast* elif);
Ast* ast_new_else(Ast* block, Location loc);
Ast* ast_new_while(Ast* condition, Ast* body, Location loc);
Ast* ast_new_func_def(char* name, Ast* params, Ast* body, Location loc);
Ast* ast_new_block(Ast* stmts, Location loc);

Ast* ast_new_bin_op(OpKind op, Ast* left, Ast* right, Location loc);
Ast* ast_new_un_op(OpKind op, Ast* operand, Location loc);
Ast* ast_new_call(char* name, Ast* args, Location loc);
Ast* ast_new_input(Ast* prompt, Location loc);
Ast* ast_new_int_conv(Ast* expr, Location loc);
Ast* ast_new_str_conv(Ast* expr, Location loc);
Ast* ast_new_name(char* id, Location loc);
Ast* ast_new_int_lit(int value, Location loc);
Ast* ast_new_bool_lit(bool value, Location loc);
Ast* ast_new_string_lit(char* value, Location loc);

Ast* ast_new_param_list(Location loc);
void ast_param_list_add(Ast* list, char* name);
Ast* ast_new_arg_list(Location loc);
void ast_arg_list_add(Ast* list, Ast* expr);

/* ========== Utilidades ========== */

const char* ast_kind_to_string(AstKind kind);
const char* op_kind_to_string(OpKind op);
void ast_free(Ast* node);

#endif /* AST_H */
