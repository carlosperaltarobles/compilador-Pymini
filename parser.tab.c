/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/ast.h"

/* Declaraciones externas */
extern int real_yylex(void);  /* Wrapper personalizado */
#define yylex real_yylex      /* Redirigir llamadas a nuestro wrapper */
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


#line 104 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_KW_IF = 3,                      /* KW_IF  */
  YYSYMBOL_KW_ELIF = 4,                    /* KW_ELIF  */
  YYSYMBOL_KW_ELSE = 5,                    /* KW_ELSE  */
  YYSYMBOL_KW_WHILE = 6,                   /* KW_WHILE  */
  YYSYMBOL_KW_DEF = 7,                     /* KW_DEF  */
  YYSYMBOL_KW_RETURN = 8,                  /* KW_RETURN  */
  YYSYMBOL_KW_PRINT = 9,                   /* KW_PRINT  */
  YYSYMBOL_TOK_AND = 10,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 11,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 12,                   /* TOK_NOT  */
  YYSYMBOL_TOK_EQ = 13,                    /* TOK_EQ  */
  YYSYMBOL_TOK_NE = 14,                    /* TOK_NE  */
  YYSYMBOL_TOK_LT = 15,                    /* TOK_LT  */
  YYSYMBOL_TOK_LE = 16,                    /* TOK_LE  */
  YYSYMBOL_TOK_GT = 17,                    /* TOK_GT  */
  YYSYMBOL_TOK_GE = 18,                    /* TOK_GE  */
  YYSYMBOL_TOK_PLUS = 19,                  /* TOK_PLUS  */
  YYSYMBOL_TOK_MINUS = 20,                 /* TOK_MINUS  */
  YYSYMBOL_TOK_STAR = 21,                  /* TOK_STAR  */
  YYSYMBOL_TOK_SLASH = 22,                 /* TOK_SLASH  */
  YYSYMBOL_TOK_MOD = 23,                   /* TOK_MOD  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_LPAREN = 25,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 26,                    /* RPAREN  */
  YYSYMBOL_COLON = 27,                     /* COLON  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_INDENT = 29,                    /* INDENT  */
  YYSYMBOL_DEDENT = 30,                    /* DEDENT  */
  YYSYMBOL_NEWLINE = 31,                   /* NEWLINE  */
  YYSYMBOL_INT_LIT = 32,                   /* INT_LIT  */
  YYSYMBOL_BOOL_LIT = 33,                  /* BOOL_LIT  */
  YYSYMBOL_IDENT = 34,                     /* IDENT  */
  YYSYMBOL_UNARY = 35,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_stmt_list = 38,                 /* stmt_list  */
  YYSYMBOL_stmt = 39,                      /* stmt  */
  YYSYMBOL_simple_stmt = 40,               /* simple_stmt  */
  YYSYMBOL_assign_stmt = 41,               /* assign_stmt  */
  YYSYMBOL_print_stmt = 42,                /* print_stmt  */
  YYSYMBOL_return_stmt = 43,               /* return_stmt  */
  YYSYMBOL_compound_stmt = 44,             /* compound_stmt  */
  YYSYMBOL_if_stmt = 45,                   /* if_stmt  */
  YYSYMBOL_elif_list = 46,                 /* elif_list  */
  YYSYMBOL_elif_clause = 47,               /* elif_clause  */
  YYSYMBOL_opt_else = 48,                  /* opt_else  */
  YYSYMBOL_while_stmt = 49,                /* while_stmt  */
  YYSYMBOL_func_def = 50,                  /* func_def  */
  YYSYMBOL_block = 51,                     /* block  */
  YYSYMBOL_opt_params = 52,                /* opt_params  */
  YYSYMBOL_param_list = 53,                /* param_list  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_or_expr = 55,                   /* or_expr  */
  YYSYMBOL_and_expr = 56,                  /* and_expr  */
  YYSYMBOL_not_expr = 57,                  /* not_expr  */
  YYSYMBOL_comparison_expr = 58,           /* comparison_expr  */
  YYSYMBOL_add_expr = 59,                  /* add_expr  */
  YYSYMBOL_mult_expr = 60,                 /* mult_expr  */
  YYSYMBOL_unary_expr = 61,                /* unary_expr  */
  YYSYMBOL_primary_expr = 62,              /* primary_expr  */
  YYSYMBOL_call_expr = 63,                 /* call_expr  */
  YYSYMBOL_opt_args = 64,                  /* opt_args  */
  YYSYMBOL_arg_list = 65                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   95

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   105,   105,   115,   116,   127,   129,   131,   137,   139,
     141,   147,   156,   162,   164,   170,   172,   174,   180,   187,
     188,   201,   208,   209,   215,   221,   230,   238,   239,   244,
     250,   261,   267,   269,   275,   277,   283,   285,   291,   293,
     295,   297,   299,   301,   303,   309,   311,   313,   319,   321,
     323,   325,   331,   333,   339,   341,   343,   348,   350,   356,
     367,   368,   373,   378
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "KW_IF", "KW_ELIF",
  "KW_ELSE", "KW_WHILE", "KW_DEF", "KW_RETURN", "KW_PRINT", "TOK_AND",
  "TOK_OR", "TOK_NOT", "TOK_EQ", "TOK_NE", "TOK_LT", "TOK_LE", "TOK_GT",
  "TOK_GE", "TOK_PLUS", "TOK_MINUS", "TOK_STAR", "TOK_SLASH", "TOK_MOD",
  "ASSIGN", "LPAREN", "RPAREN", "COLON", "COMMA", "INDENT", "DEDENT",
  "NEWLINE", "INT_LIT", "BOOL_LIT", "IDENT", "UNARY", "$accept", "program",
  "stmt_list", "stmt", "simple_stmt", "assign_stmt", "print_stmt",
  "return_stmt", "compound_stmt", "if_stmt", "elif_list", "elif_clause",
  "opt_else", "while_stmt", "func_def", "block", "opt_params",
  "param_list", "expr", "or_expr", "and_expr", "not_expr",
  "comparison_expr", "add_expr", "mult_expr", "unary_expr", "primary_expr",
  "call_expr", "opt_args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -80,     4,    12,   -80,    30,    30,   -22,    30,   -11,   -80,
       5,   -80,   -15,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
      30,    24,    30,   -80,   -80,    20,    -1,    40,    42,   -80,
      52,   -13,     1,   -80,   -80,   -80,    26,    29,   -80,    30,
      30,   -80,   -80,   -80,    33,    30,    46,    30,    30,    24,
      24,    24,    24,    24,    24,    24,    24,    24,    24,    24,
      47,    27,    34,   -80,   -80,   -80,    53,    54,    51,    42,
     -80,   -13,   -13,   -13,   -13,   -13,   -13,     1,     1,   -80,
     -80,   -80,    51,   -80,    55,    56,   -80,   -80,    30,   -80,
     -80,   -80,    58,    57,   -80,     2,    23,    59,   -80,   -80,
      30,    60,   -80,   -80,    51,    61,    62,   -80,    63,    51,
      51,   -80,   -80
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     0,     0,     0,    14,     0,     7,
       0,     4,     0,     8,     9,    10,     6,    15,    16,    17,
       0,     0,     0,    54,    55,    56,     0,    31,    32,    34,
      36,    38,    45,    48,    52,    57,     0,     0,    13,     0,
       0,     5,    37,    53,     0,    60,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,     0,    11,    58,    62,     0,    61,     0,    33,
      35,    39,    40,    41,    42,    43,    44,    46,    47,    49,
      50,    51,     0,    29,     0,    28,    12,    59,     0,     3,
      19,    24,     0,     0,    63,     0,    22,     0,    30,    26,
       0,     0,    20,    18,     0,     0,     0,    25,     0,     0,
       0,    23,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -80,   -80,    -3,   -80,   -80,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   -80,   -80,   -79,   -80,   -80,    -5,   -80,
      45,    -7,   -80,    22,    -8,   -20,   -80,   -80,   -80,   -80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    11,    12,    13,    14,    15,    16,    17,
      96,   102,   103,    18,    19,    90,    84,    85,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    66,    67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    43,    38,    91,     3,     4,    55,    56,     5,     6,
       7,     8,    37,    42,    39,     4,    41,    44,     5,     6,
       7,     8,    57,    58,    59,   107,    46,   100,   101,    40,
     111,   112,    99,     9,    62,    63,    10,    79,    80,    81,
      65,    70,    20,     9,    21,    45,    10,    77,    78,    22,
      21,    47,    48,    60,    61,    22,    23,    24,    25,    64,
      86,    83,    23,    24,    25,    49,    50,    51,    52,    53,
      54,    71,    72,    73,    74,    75,    76,    68,    82,    87,
      89,    92,    88,    94,    93,    97,    95,   106,   108,     0,
     104,    98,    69,   109,   110,   105
};

static const yytype_int8 yycheck[] =
{
       5,    21,     7,    82,     0,     3,    19,    20,     6,     7,
       8,     9,    34,    20,    25,     3,    31,    22,     6,     7,
       8,     9,    21,    22,    23,   104,    27,     4,     5,    24,
     109,   110,    30,    31,    39,    40,    34,    57,    58,    59,
      45,    48,    12,    31,    20,    25,    34,    55,    56,    25,
      20,    11,    10,    27,    25,    25,    32,    33,    34,    26,
      26,    34,    32,    33,    34,    13,    14,    15,    16,    17,
      18,    49,    50,    51,    52,    53,    54,    31,    31,    26,
      29,    26,    28,    88,    28,    27,    89,    27,    27,    -1,
      31,    34,    47,    31,    31,   100
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    37,    38,     0,     3,     6,     7,     8,     9,    31,
      34,    39,    40,    41,    42,    43,    44,    45,    49,    50,
      12,    20,    25,    32,    33,    34,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    54,    34,    54,    25,
      24,    31,    57,    61,    54,    25,    27,    11,    10,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      27,    25,    54,    54,    26,    54,    64,    65,    31,    56,
      57,    59,    59,    59,    59,    59,    59,    60,    60,    61,
      61,    61,    31,    34,    52,    53,    26,    26,    28,    29,
      51,    51,    26,    28,    54,    38,    46,    27,    34,    30,
       4,     5,    47,    48,    31,    54,    27,    51,    27,    31,
      31,    51,    51
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    39,    40,    40,
      40,    41,    42,    43,    43,    44,    44,    44,    45,    46,
      46,    47,    48,    48,    49,    50,    51,    52,    52,    53,
      53,    54,    55,    55,    56,    56,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    59,    60,    60,
      60,    60,    61,    61,    62,    62,    62,    62,    62,    63,
      64,    64,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     1,     1,
       1,     3,     4,     2,     1,     1,     1,     1,     7,     0,
       2,     5,     0,     4,     5,     8,     3,     0,     1,     1,
       3,     1,     1,     3,     1,     3,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     2,     1,     1,     1,     1,     3,     4,
       0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: stmt_list  */
#line 106 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_program((yyvsp[0].ast_node), LOC);
            parse_result = (yyval.ast_node);
        }
#line 1619 "parser.tab.c"
    break;

  case 3: /* stmt_list: %empty  */
#line 115 "src/parser.y"
        { (yyval.ast_node) = ast_new_stmt_list(LOC); }
#line 1625 "parser.tab.c"
    break;

  case 4: /* stmt_list: stmt_list stmt  */
#line 117 "src/parser.y"
        { 
            (yyval.ast_node) = (yyvsp[-1].ast_node);
            if ((yyvsp[0].ast_node) != NULL) {  /* ignorar líneas vacías */
                ast_stmt_list_add((yyval.ast_node), (yyvsp[0].ast_node));
            }
        }
#line 1636 "parser.tab.c"
    break;

  case 5: /* stmt: simple_stmt NEWLINE  */
#line 128 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1642 "parser.tab.c"
    break;

  case 6: /* stmt: compound_stmt  */
#line 130 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1648 "parser.tab.c"
    break;

  case 7: /* stmt: NEWLINE  */
#line 132 "src/parser.y"
        { (yyval.ast_node) = NULL; /* línea vacía, ignorar */ }
#line 1654 "parser.tab.c"
    break;

  case 8: /* simple_stmt: assign_stmt  */
#line 138 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1660 "parser.tab.c"
    break;

  case 9: /* simple_stmt: print_stmt  */
#line 140 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1666 "parser.tab.c"
    break;

  case 10: /* simple_stmt: return_stmt  */
#line 142 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1672 "parser.tab.c"
    break;

  case 11: /* assign_stmt: IDENT ASSIGN expr  */
#line 148 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_assign((yyvsp[-2].str_val), (yyvsp[0].ast_node), LOC);
            free((yyvsp[-2].str_val));
        }
#line 1681 "parser.tab.c"
    break;

  case 12: /* print_stmt: KW_PRINT LPAREN expr RPAREN  */
#line 157 "src/parser.y"
        { (yyval.ast_node) = ast_new_print((yyvsp[-1].ast_node), LOC); }
#line 1687 "parser.tab.c"
    break;

  case 13: /* return_stmt: KW_RETURN expr  */
#line 163 "src/parser.y"
        { (yyval.ast_node) = ast_new_return((yyvsp[0].ast_node), LOC); }
#line 1693 "parser.tab.c"
    break;

  case 14: /* return_stmt: KW_RETURN  */
#line 165 "src/parser.y"
        { (yyval.ast_node) = ast_new_return(NULL, LOC); }
#line 1699 "parser.tab.c"
    break;

  case 15: /* compound_stmt: if_stmt  */
#line 171 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1705 "parser.tab.c"
    break;

  case 16: /* compound_stmt: while_stmt  */
#line 173 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1711 "parser.tab.c"
    break;

  case 17: /* compound_stmt: func_def  */
#line 175 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1717 "parser.tab.c"
    break;

  case 18: /* if_stmt: KW_IF expr COLON NEWLINE block elif_list opt_else  */
#line 181 "src/parser.y"
        { (yyval.ast_node) = ast_new_if((yyvsp[-5].ast_node), (yyvsp[-2].ast_node), (yyvsp[-1].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1723 "parser.tab.c"
    break;

  case 19: /* elif_list: %empty  */
#line 187 "src/parser.y"
        { (yyval.ast_node) = NULL; }
#line 1729 "parser.tab.c"
    break;

  case 20: /* elif_list: elif_list elif_clause  */
#line 189 "src/parser.y"
        { 
            if ((yyvsp[-1].ast_node) == NULL) {
                (yyval.ast_node) = ast_new_elif_list(LOC);
            } else {
                (yyval.ast_node) = (yyvsp[-1].ast_node);
            }
            ast_elif_list_add((yyval.ast_node), (yyvsp[0].ast_node));
        }
#line 1742 "parser.tab.c"
    break;

  case 21: /* elif_clause: KW_ELIF expr COLON NEWLINE block  */
#line 202 "src/parser.y"
        { (yyval.ast_node) = ast_new_elif((yyvsp[-3].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1748 "parser.tab.c"
    break;

  case 22: /* opt_else: %empty  */
#line 208 "src/parser.y"
        { (yyval.ast_node) = NULL; }
#line 1754 "parser.tab.c"
    break;

  case 23: /* opt_else: KW_ELSE COLON NEWLINE block  */
#line 210 "src/parser.y"
        { (yyval.ast_node) = ast_new_else((yyvsp[0].ast_node), LOC); }
#line 1760 "parser.tab.c"
    break;

  case 24: /* while_stmt: KW_WHILE expr COLON NEWLINE block  */
#line 216 "src/parser.y"
        { (yyval.ast_node) = ast_new_while((yyvsp[-3].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1766 "parser.tab.c"
    break;

  case 25: /* func_def: KW_DEF IDENT LPAREN opt_params RPAREN COLON NEWLINE block  */
#line 222 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_func_def((yyvsp[-6].str_val), (yyvsp[-4].ast_node), (yyvsp[0].ast_node), LOC);
            free((yyvsp[-6].str_val));
        }
#line 1775 "parser.tab.c"
    break;

  case 26: /* block: INDENT stmt_list DEDENT  */
#line 231 "src/parser.y"
        { (yyval.ast_node) = ast_new_block((yyvsp[-1].ast_node), LOC); }
#line 1781 "parser.tab.c"
    break;

  case 27: /* opt_params: %empty  */
#line 238 "src/parser.y"
        { (yyval.ast_node) = NULL; }
#line 1787 "parser.tab.c"
    break;

  case 28: /* opt_params: param_list  */
#line 240 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1793 "parser.tab.c"
    break;

  case 29: /* param_list: IDENT  */
#line 245 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_param_list(LOC);
            ast_param_list_add((yyval.ast_node), (yyvsp[0].str_val));
            free((yyvsp[0].str_val));
        }
#line 1803 "parser.tab.c"
    break;

  case 30: /* param_list: param_list COMMA IDENT  */
#line 251 "src/parser.y"
        { 
            (yyval.ast_node) = (yyvsp[-2].ast_node);
            ast_param_list_add((yyval.ast_node), (yyvsp[0].str_val));
            free((yyvsp[0].str_val));
        }
#line 1813 "parser.tab.c"
    break;

  case 31: /* expr: or_expr  */
#line 262 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1819 "parser.tab.c"
    break;

  case 32: /* or_expr: and_expr  */
#line 268 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1825 "parser.tab.c"
    break;

  case 33: /* or_expr: or_expr TOK_OR and_expr  */
#line 270 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_OR, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1831 "parser.tab.c"
    break;

  case 34: /* and_expr: not_expr  */
#line 276 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1837 "parser.tab.c"
    break;

  case 35: /* and_expr: and_expr TOK_AND not_expr  */
#line 278 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_AND, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1843 "parser.tab.c"
    break;

  case 36: /* not_expr: comparison_expr  */
#line 284 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1849 "parser.tab.c"
    break;

  case 37: /* not_expr: TOK_NOT not_expr  */
#line 286 "src/parser.y"
        { (yyval.ast_node) = ast_new_un_op(OP_NOT, (yyvsp[0].ast_node), LOC); }
#line 1855 "parser.tab.c"
    break;

  case 38: /* comparison_expr: add_expr  */
#line 292 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1861 "parser.tab.c"
    break;

  case 39: /* comparison_expr: comparison_expr TOK_EQ add_expr  */
#line 294 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_EQ, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1867 "parser.tab.c"
    break;

  case 40: /* comparison_expr: comparison_expr TOK_NE add_expr  */
#line 296 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_NE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1873 "parser.tab.c"
    break;

  case 41: /* comparison_expr: comparison_expr TOK_LT add_expr  */
#line 298 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_LT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1879 "parser.tab.c"
    break;

  case 42: /* comparison_expr: comparison_expr TOK_LE add_expr  */
#line 300 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_LE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1885 "parser.tab.c"
    break;

  case 43: /* comparison_expr: comparison_expr TOK_GT add_expr  */
#line 302 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_GT, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1891 "parser.tab.c"
    break;

  case 44: /* comparison_expr: comparison_expr TOK_GE add_expr  */
#line 304 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_GE, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1897 "parser.tab.c"
    break;

  case 45: /* add_expr: mult_expr  */
#line 310 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1903 "parser.tab.c"
    break;

  case 46: /* add_expr: add_expr TOK_PLUS mult_expr  */
#line 312 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_ADD, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1909 "parser.tab.c"
    break;

  case 47: /* add_expr: add_expr TOK_MINUS mult_expr  */
#line 314 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_SUB, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1915 "parser.tab.c"
    break;

  case 48: /* mult_expr: unary_expr  */
#line 320 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1921 "parser.tab.c"
    break;

  case 49: /* mult_expr: mult_expr TOK_STAR unary_expr  */
#line 322 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_MUL, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1927 "parser.tab.c"
    break;

  case 50: /* mult_expr: mult_expr TOK_SLASH unary_expr  */
#line 324 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_DIV, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1933 "parser.tab.c"
    break;

  case 51: /* mult_expr: mult_expr TOK_MOD unary_expr  */
#line 326 "src/parser.y"
        { (yyval.ast_node) = ast_new_bin_op(OP_MOD, (yyvsp[-2].ast_node), (yyvsp[0].ast_node), LOC); }
#line 1939 "parser.tab.c"
    break;

  case 52: /* unary_expr: primary_expr  */
#line 332 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1945 "parser.tab.c"
    break;

  case 53: /* unary_expr: TOK_MINUS unary_expr  */
#line 334 "src/parser.y"
        { (yyval.ast_node) = ast_new_un_op(OP_NEG, (yyvsp[0].ast_node), LOC); }
#line 1951 "parser.tab.c"
    break;

  case 54: /* primary_expr: INT_LIT  */
#line 340 "src/parser.y"
        { (yyval.ast_node) = ast_new_int_lit((yyvsp[0].int_val), LOC); }
#line 1957 "parser.tab.c"
    break;

  case 55: /* primary_expr: BOOL_LIT  */
#line 342 "src/parser.y"
        { (yyval.ast_node) = ast_new_bool_lit((yyvsp[0].bool_val), LOC); }
#line 1963 "parser.tab.c"
    break;

  case 56: /* primary_expr: IDENT  */
#line 344 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_name((yyvsp[0].str_val), LOC);
            free((yyvsp[0].str_val));
        }
#line 1972 "parser.tab.c"
    break;

  case 57: /* primary_expr: call_expr  */
#line 349 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 1978 "parser.tab.c"
    break;

  case 58: /* primary_expr: LPAREN expr RPAREN  */
#line 351 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[-1].ast_node); }
#line 1984 "parser.tab.c"
    break;

  case 59: /* call_expr: IDENT LPAREN opt_args RPAREN  */
#line 357 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_call((yyvsp[-3].str_val), (yyvsp[-1].ast_node), LOC);
            free((yyvsp[-3].str_val));
        }
#line 1993 "parser.tab.c"
    break;

  case 60: /* opt_args: %empty  */
#line 367 "src/parser.y"
        { (yyval.ast_node) = NULL; }
#line 1999 "parser.tab.c"
    break;

  case 61: /* opt_args: arg_list  */
#line 369 "src/parser.y"
        { (yyval.ast_node) = (yyvsp[0].ast_node); }
#line 2005 "parser.tab.c"
    break;

  case 62: /* arg_list: expr  */
#line 374 "src/parser.y"
        { 
            (yyval.ast_node) = ast_new_arg_list(LOC);
            ast_arg_list_add((yyval.ast_node), (yyvsp[0].ast_node));
        }
#line 2014 "parser.tab.c"
    break;

  case 63: /* arg_list: arg_list COMMA expr  */
#line 379 "src/parser.y"
        { 
            (yyval.ast_node) = (yyvsp[-2].ast_node);
            ast_arg_list_add((yyval.ast_node), (yyvsp[0].ast_node));
        }
#line 2023 "parser.tab.c"
    break;


#line 2027 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 385 "src/parser.y"


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
