/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    KW_IF = 258,                   /* KW_IF  */
    KW_ELIF = 259,                 /* KW_ELIF  */
    KW_ELSE = 260,                 /* KW_ELSE  */
    KW_WHILE = 261,                /* KW_WHILE  */
    KW_DEF = 262,                  /* KW_DEF  */
    KW_RETURN = 263,               /* KW_RETURN  */
    KW_PRINT = 264,                /* KW_PRINT  */
    KW_INPUT = 265,                /* KW_INPUT  */
    TOK_AND = 266,                 /* TOK_AND  */
    TOK_OR = 267,                  /* TOK_OR  */
    TOK_NOT = 268,                 /* TOK_NOT  */
    TOK_EQ = 269,                  /* TOK_EQ  */
    TOK_NE = 270,                  /* TOK_NE  */
    TOK_LT = 271,                  /* TOK_LT  */
    TOK_LE = 272,                  /* TOK_LE  */
    TOK_GT = 273,                  /* TOK_GT  */
    TOK_GE = 274,                  /* TOK_GE  */
    TOK_PLUS = 275,                /* TOK_PLUS  */
    TOK_MINUS = 276,               /* TOK_MINUS  */
    TOK_STAR = 277,                /* TOK_STAR  */
    TOK_SLASH = 278,               /* TOK_SLASH  */
    TOK_MOD = 279,                 /* TOK_MOD  */
    ASSIGN = 280,                  /* ASSIGN  */
    LPAREN = 281,                  /* LPAREN  */
    RPAREN = 282,                  /* RPAREN  */
    COLON = 283,                   /* COLON  */
    COMMA = 284,                   /* COMMA  */
    INDENT = 285,                  /* INDENT  */
    DEDENT = 286,                  /* DEDENT  */
    NEWLINE = 287,                 /* NEWLINE  */
    INT_LIT = 288,                 /* INT_LIT  */
    BOOL_LIT = 289,                /* BOOL_LIT  */
    IDENT = 290,                   /* IDENT  */
    UNARY = 291                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 43 "src/parser.y"

    int int_val;
    bool bool_val;
    char* str_val;
    Ast* ast_node;
    OpKind op_kind;

#line 108 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
