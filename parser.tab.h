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
    TOK_AND = 265,                 /* TOK_AND  */
    TOK_OR = 266,                  /* TOK_OR  */
    TOK_NOT = 267,                 /* TOK_NOT  */
    TOK_EQ = 268,                  /* TOK_EQ  */
    TOK_NE = 269,                  /* TOK_NE  */
    TOK_LT = 270,                  /* TOK_LT  */
    TOK_LE = 271,                  /* TOK_LE  */
    TOK_GT = 272,                  /* TOK_GT  */
    TOK_GE = 273,                  /* TOK_GE  */
    TOK_PLUS = 274,                /* TOK_PLUS  */
    TOK_MINUS = 275,               /* TOK_MINUS  */
    TOK_STAR = 276,                /* TOK_STAR  */
    TOK_SLASH = 277,               /* TOK_SLASH  */
    TOK_MOD = 278,                 /* TOK_MOD  */
    ASSIGN = 279,                  /* ASSIGN  */
    LPAREN = 280,                  /* LPAREN  */
    RPAREN = 281,                  /* RPAREN  */
    COLON = 282,                   /* COLON  */
    COMMA = 283,                   /* COMMA  */
    INDENT = 284,                  /* INDENT  */
    DEDENT = 285,                  /* DEDENT  */
    NEWLINE = 286,                 /* NEWLINE  */
    INT_LIT = 287,                 /* INT_LIT  */
    BOOL_LIT = 288,                /* BOOL_LIT  */
    IDENT = 289,                   /* IDENT  */
    UNARY = 290                    /* UNARY  */
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

#line 107 "parser.tab.h"

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
