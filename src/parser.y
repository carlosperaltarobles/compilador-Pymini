/* parser.y - Analizador sintáctico para PyMini usando Bison */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/ast.h"

/* Declaraciones externas */
extern int yylex(void);
extern int yyline;
extern int yycolumn;
extern FILE* yyin;
extern void lex_reset(void);

/* Variables globales */
Ast* parse_result = NULL;
int parse_error_count = 0;

/* Función de error */
void yyerror(const char* msg);

/* Helper para crear Location */
Location make_location(int line, int col) {
    Location loc;
    loc.line = line;
    loc.column = col;
    return loc;
}

#define LOC make_location(yylloc.first_line, yylloc.first_column)

%}

/* ========== Configuración de Bison ========== */

%define parse.error verbose
%locations

/* ========== Tipos de Valores Semánticos ========== */

%union {
    int int_val;
    bool bool_val;
    char* str_val;
    Ast* ast_node;
    OpKind op_kind;
}

/* ========== Tokens ========== */

/* Palabras clave */
%token KW_IF KW_ELIF KW_ELSE KW_WHILE KW_DEF KW_RETURN KW_PRINT

/* Operadores lógicos */
%token TOK_AND TOK_OR TOK_NOT

/* Operadores de comparación */
%token TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE

/* Operadores aritméticos */
%token TOK_PLUS TOK_MINUS TOK_STAR TOK_SLASH TOK_MOD

/* Símbolos */
%token ASSIGN LPAREN RPAREN LBRACE RBRACE COLON COMMA

/* Literales e identificadores */
%token <int_val> INT_LIT
%token <bool_val> BOOL_LIT
%token <str_val> IDENT

/* ========== No-terminales con tipos ========== */

%type <ast_node> program stmt_list stmt
%type <ast_node> simple_stmt compound_stmt
%type <ast_node> assign_stmt print_stmt return_stmt
%type <ast_node> if_stmt elif_list elif_clause opt_else
%type <ast_node> while_stmt func_def block
%type <ast_node> expr or_expr and_expr not_expr
%type <ast_node> comparison_expr add_expr mult_expr unary_expr primary_expr
%type <ast_node> call_expr
%type <ast_node> opt_params param_list
%type <ast_node> opt_args arg_list

/* ========== Precedencia y Asociatividad ========== */

%left TOK_OR
%left TOK_AND
%right TOK_NOT
%left TOK_EQ TOK_NE TOK_LT TOK_LE TOK_GT TOK_GE
%left TOK_PLUS TOK_MINUS
%left TOK_STAR TOK_SLASH TOK_MOD
%right UNARY

%%

/* ========== Reglas de Gramática ========== */

/* Programa principal */
program:
    stmt_list
        { 
            $$ = ast_new_program($1, LOC);
            parse_result = $$;
        }
    ;

/* Lista de sentencias */
stmt_list:
    /* vacío */
        { $$ = ast_new_stmt_list(LOC); }
    | stmt_list stmt
        { 
            $$ = $1;
            ast_stmt_list_add($$, $2);
        }
    ;

/* Sentencia genérica */
stmt:
    simple_stmt
        { $$ = $1; }
    | compound_stmt
        { $$ = $1; }
    ;

/* Sentencias simples */
simple_stmt:
    assign_stmt
        { $$ = $1; }
    | print_stmt
        { $$ = $1; }
    | return_stmt
        { $$ = $1; }
    ;

/* Asignación */
assign_stmt:
    IDENT ASSIGN expr
        { 
            $$ = ast_new_assign($1, $3, LOC);
            free($1);
        }
    ;

/* Print */
print_stmt:
    KW_PRINT LPAREN expr RPAREN
        { $$ = ast_new_print($3, LOC); }
    ;

/* Return */
return_stmt:
    KW_RETURN expr
        { $$ = ast_new_return($2, LOC); }
    | KW_RETURN
        { $$ = ast_new_return(NULL, LOC); }
    ;

/* Sentencias compuestas */
compound_stmt:
    if_stmt
        { $$ = $1; }
    | while_stmt
        { $$ = $1; }
    | func_def
        { $$ = $1; }
    ;

/* Condicional if */
if_stmt:
    KW_IF expr COLON block elif_list opt_else
        { $$ = ast_new_if($2, $4, $5, $6, LOC); }
    ;

/* Lista de elif (puede estar vacía) */
elif_list:
    /* vacío */
        { $$ = NULL; }
    | elif_list elif_clause
        { 
            if ($1 == NULL) {
                $$ = ast_new_elif_list(LOC);
            } else {
                $$ = $1;
            }
            ast_elif_list_add($$, $2);
        }
    ;

/* Cláusula elif individual */
elif_clause:
    KW_ELIF expr COLON block
        { $$ = ast_new_elif($2, $4, LOC); }
    ;

/* Else opcional */
opt_else:
    /* vacío */
        { $$ = NULL; }
    | KW_ELSE COLON block
        { $$ = ast_new_else($3, LOC); }
    ;

/* Bucle while */
while_stmt:
    KW_WHILE expr COLON block
        { $$ = ast_new_while($2, $4, LOC); }
    ;

/* Definición de función */
func_def:
    KW_DEF IDENT LPAREN opt_params RPAREN COLON block
        { 
            $$ = ast_new_func_def($2, $4, $7, LOC);
            free($2);
        }
    ;

/* Bloque de código */
block:
    LBRACE stmt_list RBRACE
        { $$ = ast_new_block($2, LOC); }
    ;

/* ========== Parámetros de Función ========== */

opt_params:
    /* vacío */
        { $$ = NULL; }
    | param_list
        { $$ = $1; }
    ;

param_list:
    IDENT
        { 
            $$ = ast_new_param_list(LOC);
            ast_param_list_add($$, $1);
            free($1);
        }
    | param_list COMMA IDENT
        { 
            $$ = $1;
            ast_param_list_add($$, $3);
            free($3);
        }
    ;

/* ========== Expresiones ========== */

expr:
    or_expr
        { $$ = $1; }
    ;

/* OR tiene menor precedencia */
or_expr:
    and_expr
        { $$ = $1; }
    | or_expr TOK_OR and_expr
        { $$ = ast_new_bin_op(OP_OR, $1, $3, LOC); }
    ;

/* AND */
and_expr:
    not_expr
        { $$ = $1; }
    | and_expr TOK_AND not_expr
        { $$ = ast_new_bin_op(OP_AND, $1, $3, LOC); }
    ;

/* NOT (unario) */
not_expr:
    comparison_expr
        { $$ = $1; }
    | TOK_NOT not_expr
        { $$ = ast_new_un_op(OP_NOT, $2, LOC); }
    ;

/* Comparaciones */
comparison_expr:
    add_expr
        { $$ = $1; }
    | comparison_expr TOK_EQ add_expr
        { $$ = ast_new_bin_op(OP_EQ, $1, $3, LOC); }
    | comparison_expr TOK_NE add_expr
        { $$ = ast_new_bin_op(OP_NE, $1, $3, LOC); }
    | comparison_expr TOK_LT add_expr
        { $$ = ast_new_bin_op(OP_LT, $1, $3, LOC); }
    | comparison_expr TOK_LE add_expr
        { $$ = ast_new_bin_op(OP_LE, $1, $3, LOC); }
    | comparison_expr TOK_GT add_expr
        { $$ = ast_new_bin_op(OP_GT, $1, $3, LOC); }
    | comparison_expr TOK_GE add_expr
        { $$ = ast_new_bin_op(OP_GE, $1, $3, LOC); }
    ;

/* Suma y resta */
add_expr:
    mult_expr
        { $$ = $1; }
    | add_expr TOK_PLUS mult_expr
        { $$ = ast_new_bin_op(OP_ADD, $1, $3, LOC); }
    | add_expr TOK_MINUS mult_expr
        { $$ = ast_new_bin_op(OP_SUB, $1, $3, LOC); }
    ;

/* Multiplicación, división y módulo */
mult_expr:
    unary_expr
        { $$ = $1; }
    | mult_expr TOK_STAR unary_expr
        { $$ = ast_new_bin_op(OP_MUL, $1, $3, LOC); }
    | mult_expr TOK_SLASH unary_expr
        { $$ = ast_new_bin_op(OP_DIV, $1, $3, LOC); }
    | mult_expr TOK_MOD unary_expr
        { $$ = ast_new_bin_op(OP_MOD, $1, $3, LOC); }
    ;

/* Expresiones unarias */
unary_expr:
    primary_expr
        { $$ = $1; }
    | TOK_MINUS unary_expr %prec UNARY
        { $$ = ast_new_un_op(OP_NEG, $2, LOC); }
    ;

/* Expresiones primarias */
primary_expr:
    INT_LIT
        { $$ = ast_new_int_lit($1, LOC); }
    | BOOL_LIT
        { $$ = ast_new_bool_lit($1, LOC); }
    | IDENT
        { 
            $$ = ast_new_name($1, LOC);
            free($1);
        }
    | call_expr
        { $$ = $1; }
    | LPAREN expr RPAREN
        { $$ = $2; }
    ;

/* Llamada a función */
call_expr:
    IDENT LPAREN opt_args RPAREN
        { 
            $$ = ast_new_call($1, $3, LOC);
            free($1);
        }
    ;

/* ========== Argumentos de Función ========== */

opt_args:
    /* vacío */
        { $$ = NULL; }
    | arg_list
        { $$ = $1; }
    ;

arg_list:
    expr
        { 
            $$ = ast_new_arg_list(LOC);
            ast_arg_list_add($$, $1);
        }
    | arg_list COMMA expr
        { 
            $$ = $1;
            ast_arg_list_add($$, $3);
        }
    ;

%%

/* ========== Implementación de Funciones de Error ========== */

void yyerror(const char* msg) {
    fprintf(stderr, "Error sintáctico en línea %d, columna %d: %s\n", 
            yylloc.first_line, yylloc.first_column, msg);
    parse_error_count++;
}

/* ========== Funciones Auxiliares de Parseo ========== */

Ast* parse_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr, "Error: no se pudo abrir el archivo '%s'\n", filename);
        return NULL;
    }
    
    yyin = f;
    parse_result = NULL;
    parse_error_count = 0;
    yyline = 1;
    yycolumn = 1;
    
    /* Parsear el archivo */
    int result = yyparse();
    
    fclose(f);
    
    if (result != 0 || parse_error_count > 0) {
        /* Hubo errores de parseo */
        if (parse_result) {
            ast_free(parse_result);
            parse_result = NULL;
        }
        return NULL;
    }
    
    return parse_result;
}
