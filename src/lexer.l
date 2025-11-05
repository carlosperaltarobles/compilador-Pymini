/* lexer.l - Analizador Léxico para PyMini con Indentación Significativa */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "parser.tab.h"

/* Declarar strdup si no está disponible */
#ifndef _GNU_SOURCE
extern char *strdup(const char *s);
#endif

/* Variables globales para rastrear línea y columna */
int yyline = 1;
int yycolumn = 1;

/* Pila de indentación */
#define MAX_INDENT_DEPTH 100
static int indent_stack[MAX_INDENT_DEPTH];
static int indent_stack_top = 0;

/* Buffer para tokens pendientes (DEDENT múltiples) */
#define MAX_PENDING_TOKENS 100
static int pending_tokens[MAX_PENDING_TOKENS];
static int pending_count = 0;

/* Estado del lexer */
static bool at_line_start = true;
static bool saw_newline = false;
static int pending_dedents = 0;
static bool last_was_newline = true;  /* Al inicio, consideramos que estamos en "nueva línea" */

/* Actualizar la ubicación después de cada token */
#define YY_USER_ACTION \
    do { \
        yylloc.first_line = yyline; \
        yylloc.first_column = yycolumn; \
        yylloc.last_line = yyline; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng; \
    } while (0);

/* Función para reportar errores léxicos */
void lex_error(const char* msg, const char* text) {
    fprintf(stderr, "IndentationError: %s en línea %d, columna %d: '%s'\n", 
            msg, yyline, yycolumn, text);
}

/* Función para manejar indentación */
int handle_indentation(int spaces);

%}

/* Opciones de Flex */
%option noyywrap
%option nounput
%option noinput

/* Estados exclusivos para manejo de indentación */
%x INDENT_STATE

/* Definiciones de patrones */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
IDENT       {LETTER}({LETTER}|{DIGIT})*
INTEGER     {DIGIT}+
SPACE       [ ]
TAB         \t
COMMENT     #.*

%%

    /* ========== Manejo de Indentación al Inicio de Línea ========== */
<INDENT_STATE>^{SPACE}+ {
    at_line_start = false;
    BEGIN(INITIAL);  /* Volver al estado normal */
    
    /* Verificar que no hay tabs mezclados */
    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == '\t') {
            lex_error("mezcla de espacios y tabs en indentación", yytext);
            exit(1);
        }
    }
    
    int result = handle_indentation(yyleng);
    if (result != -1) {
        return result;
    }
    /* Si retorna -1, continuar normalmente (misma indentación) */
}

<INDENT_STATE>^{TAB}+ {
    lex_error("uso de tabs en indentación (use espacios)", yytext);
    exit(1);
}

<INDENT_STATE>^{SPACE}*{TAB} {
    lex_error("mezcla de espacios y tabs en indentación", yytext);
    exit(1);
}

<INDENT_STATE>^\n {
    /* Línea vacía - ignorar (no afecta indentación) */
    yyline++;
    yycolumn = 1;
    at_line_start = true;
    /* NO cambiar last_was_newline aquí */
}

<INDENT_STATE>^{COMMENT}\n {
    /* Línea con solo comentario - ignorar */
    yyline++;
    yycolumn = 1;
    at_line_start = true;
}

<INDENT_STATE>^[^ \t\n] {
    /* Inicio de línea sin indentación */
    at_line_start = false;
    BEGIN(INITIAL);  /* Volver al estado normal */
    yyless(0);  /* Devolver el carácter */
    int result = handle_indentation(0);
    if (result != -1) {
        return result;
    }
    /* Si retorna -1, continuar normalmente (misma indentación) */
}

    /* ========== Palabras Clave ========== */
"if"        { at_line_start = false; last_was_newline = false; return KW_IF; }
"elif"      { at_line_start = false; last_was_newline = false; return KW_ELIF; }
"else"      { at_line_start = false; last_was_newline = false; return KW_ELSE; }
"while"     { at_line_start = false; last_was_newline = false; return KW_WHILE; }
"def"       { at_line_start = false; last_was_newline = false; return KW_DEF; }
"return"    { at_line_start = false; last_was_newline = false; return KW_RETURN; }
"print"     { at_line_start = false; last_was_newline = false; return KW_PRINT; }
"input"     { at_line_start = false; last_was_newline = false; return KW_INPUT; }
"True"      { at_line_start = false; last_was_newline = false; yylval.bool_val = true; return BOOL_LIT; }
"False"     { at_line_start = false; last_was_newline = false; yylval.bool_val = false; return BOOL_LIT; }
"and"       { at_line_start = false; last_was_newline = false; return TOK_AND; }
"or"        { at_line_start = false; last_was_newline = false; return TOK_OR; }
"not"       { at_line_start = false; last_was_newline = false; return TOK_NOT; }

    /* ========== Operadores de Comparación ========== */
"=="        { at_line_start = false; last_was_newline = false; return TOK_EQ; }
"!="        { at_line_start = false; last_was_newline = false; return TOK_NE; }
"<="        { at_line_start = false; last_was_newline = false; return TOK_LE; }
">="        { at_line_start = false; last_was_newline = false; return TOK_GE; }
"<"         { at_line_start = false; last_was_newline = false; return TOK_LT; }
">"         { at_line_start = false; last_was_newline = false; return TOK_GT; }

    /* ========== Operadores Aritméticos ========== */
"+"         { at_line_start = false; last_was_newline = false; return TOK_PLUS; }
"-"         { at_line_start = false; last_was_newline = false; return TOK_MINUS; }
"*"         { at_line_start = false; last_was_newline = false; return TOK_STAR; }
"/"         { at_line_start = false; last_was_newline = false; return TOK_SLASH; }
"%"         { at_line_start = false; last_was_newline = false; return TOK_MOD; }

    /* ========== Símbolos ========== */
"="         { at_line_start = false; last_was_newline = false; return ASSIGN; }
"("         { at_line_start = false; last_was_newline = false; return LPAREN; }
")"         { at_line_start = false; last_was_newline = false; return RPAREN; }
":"         { at_line_start = false; last_was_newline = false; return COLON; }
","         { at_line_start = false; last_was_newline = false; return COMMA; }

    /* ========== Identificadores y Literales ========== */
{IDENT}     { 
                at_line_start = false;
                last_was_newline = false;
                yylval.str_val = strdup(yytext); 
                return IDENT; 
            }

{INTEGER}   { 
                at_line_start = false;
                last_was_newline = false;
                yylval.int_val = atoi(yytext); 
                return INT_LIT; 
            }

    /* ========== Espacios en Blanco (no al inicio de línea) ========== */
[ \t]+      { /* Ignorar espacios y tabs en medio de línea */ }

    /* ========== Nueva Línea ========== */
\n          { 
                yyline++; 
                yycolumn = 1;
                at_line_start = true;
                last_was_newline = true;
                /* Cambiar a estado de indentación para la siguiente línea */
                BEGIN(INDENT_STATE);
                /* Retornar NEWLINE para que el parser sepa que acabó una línea */
                return NEWLINE;
            }

    /* ========== Comentarios ========== */
{COMMENT}   { /* Ignorar comentarios */ }

    /* ========== Caracteres Inválidos ========== */
.           { 
                at_line_start = false;
                lex_error("carácter inválido", yytext); 
                /* Continuar parseando */
            }

%%

/* ========== Funciones Auxiliares para Indentación ========== */

/* Inicializar la pila de indentación */
void init_indent_stack(void) {
    indent_stack[0] = 0;  /* Nivel base */
    indent_stack_top = 0;
    pending_count = 0;
    at_line_start = true;
    saw_newline = false;
    pending_dedents = 0;
    last_was_newline = true;  /* Al inicio, consideramos que estamos en "nueva línea" */
}

/* Maneja cambios de indentación y retorna INDENT, DEDENT o continúa */
int handle_indentation(int spaces) {
    int current_indent = indent_stack[indent_stack_top];
    
    if (spaces > current_indent) {
        /* Incremento de indentación */
        if (indent_stack_top >= MAX_INDENT_DEPTH - 1) {
            lex_error("indentación demasiado profunda", "");
            exit(1);
        }
        indent_stack_top++;
        indent_stack[indent_stack_top] = spaces;
        return INDENT;
    }
    else if (spaces < current_indent) {
        /* Decremento de indentación - puede necesitar múltiples DEDENT */
        
        /* Buscar el nivel correspondiente en la pila */
        int found = 0;
        for (int i = indent_stack_top; i >= 0; i--) {
            if (indent_stack[i] == spaces) {
                found = 1;
                /* Generar DEDENT tokens para cada nivel que bajamos */
                int dedent_count = indent_stack_top - i;
                indent_stack_top = i;
                
                if (dedent_count > 0) {
                    /* Guardar DEDENT tokens pendientes */
                    for (int j = 1; j < dedent_count; j++) {
                        if (pending_count < MAX_PENDING_TOKENS) {
                            pending_tokens[pending_count++] = DEDENT;
                        }
                    }
                    return DEDENT;
                }
                break;
            }
        }
        
        if (!found) {
            lex_error("indentación inconsistente", "");
            exit(1);
        }
    }
    
    /* Misma indentación - continuar normalmente */
    return -1;  /* Señal para no retornar token */
}

/* Declaración de la función generada por Flex */
int yylex(void);

/* Wrapper personalizado para manejar tokens pendientes e indentación */
int real_yylex(void) {
    /* Si hay tokens pendientes, retornarlos primero */
    if (pending_count > 0) {
        return pending_tokens[--pending_count];
    }
    
    int token = yylex();  /* Llamar a la función generada por Flex */
    
    /* Al final del archivo */
    if (token == 0) {
        /* Si la última sentencia no terminó con NEWLINE, agregar uno */
        if (!last_was_newline) {
            last_was_newline = true;
            /* Encolar todos los DEDENT para niveles de indentación restantes */
            if (indent_stack_top > 0) {
                for (int i = 0; i < indent_stack_top; i++) {
                    if (pending_count < MAX_PENDING_TOKENS) {
                        pending_tokens[pending_count++] = DEDENT;
                    }
                }
                indent_stack_top = 0;
            }
            return NEWLINE;
        }
        
        /* Si ya retornamos NEWLINE, retornar DEDENT si aún quedan en la pila */
        if (indent_stack_top > 0) {
            indent_stack_top--;
            return DEDENT;
        }
    }
    
    return token;
}

/* ========== Funciones de Inicialización ========== */

/* Inicializar el lexer */
void lex_init(void) {
    yyline = 1;
    yycolumn = 1;
    init_indent_stack();
    BEGIN(INDENT_STATE);  /* Comenzar en estado de indentación */
}

/* Resetear el lexer para un nuevo archivo */
void lex_reset(void) {
    yyrestart(yyin);
    yyline = 1;
    yycolumn = 1;
    init_indent_stack();
    BEGIN(INDENT_STATE);  /* Comenzar en estado de indentación */
}
