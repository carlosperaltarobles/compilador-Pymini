/* lexer.l - Analizador Léxico para PyMini usando Flex */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/ast.h"
#include "parser.tab.h"

/* Declarar strdup si no está disponible */
#ifndef _GNU_SOURCE
extern char *strdup(const char *s);
#endif

/* Variables globales para rastrear línea y columna */
int yyline = 1;
int yycolumn = 1;

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
    fprintf(stderr, "Error léxico en línea %d, columna %d: %s '%s'\n", 
            yyline, yycolumn, msg, text);
}

%}

/* Opciones de Flex */
%option noyywrap
%option nounput
%option noinput

/* Definiciones de patrones */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
IDENT       {LETTER}({LETTER}|{DIGIT})*
INTEGER     {DIGIT}+
WHITESPACE  [ \t]+
NEWLINE     \n
COMMENT     #.*

%%

    /* ========== Palabras Clave ========== */
"if"        { return KW_IF; }
"elif"      { return KW_ELIF; }
"else"      { return KW_ELSE; }
"while"     { return KW_WHILE; }
"def"       { return KW_DEF; }
"return"    { return KW_RETURN; }
"print"     { return KW_PRINT; }
"True"      { yylval.bool_val = true; return BOOL_LIT; }
"False"     { yylval.bool_val = false; return BOOL_LIT; }
"and"       { return TOK_AND; }
"or"        { return TOK_OR; }
"not"       { return TOK_NOT; }

    /* ========== Operadores de Comparación ========== */
"=="        { return TOK_EQ; }
"!="        { return TOK_NE; }
"<="        { return TOK_LE; }
">="        { return TOK_GE; }
"<"         { return TOK_LT; }
">"         { return TOK_GT; }

    /* ========== Operadores Aritméticos ========== */
"+"         { return TOK_PLUS; }
"-"         { return TOK_MINUS; }
"*"         { return TOK_STAR; }
"/"         { return TOK_SLASH; }
"%"         { return TOK_MOD; }

    /* ========== Símbolos ========== */
"="         { return ASSIGN; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
":"         { return COLON; }
","         { return COMMA; }

    /* ========== Identificadores y Literales ========== */
{IDENT}     { 
                yylval.str_val = strdup(yytext); 
                return IDENT; 
            }

{INTEGER}   { 
                yylval.int_val = atoi(yytext); 
                return INT_LIT; 
            }

    /* ========== Espacios en Blanco ========== */
{WHITESPACE}    { /* Ignorar espacios y tabs */ }

{NEWLINE}   { 
                yyline++; 
                yycolumn = 1; 
            }

    /* ========== Comentarios ========== */
{COMMENT}   { /* Ignorar comentarios */ }

    /* ========== Caracteres Inválidos ========== */
.           { 
                lex_error("carácter inválido", yytext); 
                /* Continuar parseando */
            }

%%

/* ========== Funciones Auxiliares ========== */

/* Inicializar el lexer */
void lex_init(void) {
    yyline = 1;
    yycolumn = 1;
}

/* Resetear el lexer para un nuevo archivo */
void lex_reset(void) {
    yyrestart(yyin);
    yyline = 1;
    yycolumn = 1;
}
