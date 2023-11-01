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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}


#line 115 "yacc_sql.cpp"

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

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_AS = 4,                         /* AS  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_TABLE = 7,                      /* TABLE  */
  YYSYMBOL_TABLES = 8,                     /* TABLES  */
  YYSYMBOL_INDEX = 9,                      /* INDEX  */
  YYSYMBOL_CALC = 10,                      /* CALC  */
  YYSYMBOL_LENGTH = 11,                    /* LENGTH  */
  YYSYMBOL_ROUND = 12,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 13,               /* DATE_FORMAT  */
  YYSYMBOL_INNER = 14,                     /* INNER  */
  YYSYMBOL_JOIN = 15,                      /* JOIN  */
  YYSYMBOL_SELECT = 16,                    /* SELECT  */
  YYSYMBOL_DESC = 17,                      /* DESC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_DELETE = 21,                    /* DELETE  */
  YYSYMBOL_UPDATE = 22,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 23,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 24,                    /* RBRACE  */
  YYSYMBOL_COMMA = 25,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 26,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 27,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 28,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 29,                     /* INT_T  */
  YYSYMBOL_DATE_T = 30,                    /* DATE_T  */
  YYSYMBOL_MIN = 31,                       /* MIN  */
  YYSYMBOL_MAX = 32,                       /* MAX  */
  YYSYMBOL_AVG = 33,                       /* AVG  */
  YYSYMBOL_COUNT = 34,                     /* COUNT  */
  YYSYMBOL_SUM = 35,                       /* SUM  */
  YYSYMBOL_STRING_T = 36,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 37,                   /* FLOAT_T  */
  YYSYMBOL_TEXT_T = 38,                    /* TEXT_T  */
  YYSYMBOL_HELP = 39,                      /* HELP  */
  YYSYMBOL_EXIT = 40,                      /* EXIT  */
  YYSYMBOL_DOT = 41,                       /* DOT  */
  YYSYMBOL_INTO = 42,                      /* INTO  */
  YYSYMBOL_VALUES = 43,                    /* VALUES  */
  YYSYMBOL_FROM = 44,                      /* FROM  */
  YYSYMBOL_WHERE = 45,                     /* WHERE  */
  YYSYMBOL_AND = 46,                       /* AND  */
  YYSYMBOL_SET = 47,                       /* SET  */
  YYSYMBOL_ON = 48,                        /* ON  */
  YYSYMBOL_LOAD = 49,                      /* LOAD  */
  YYSYMBOL_DATA = 50,                      /* DATA  */
  YYSYMBOL_INFILE = 51,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 52,                   /* EXPLAIN  */
  YYSYMBOL_LIKE = 53,                      /* LIKE  */
  YYSYMBOL_NOT_LIKE = 54,                  /* NOT_LIKE  */
  YYSYMBOL_IS = 55,                        /* IS  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_NULLABLE = 57,                  /* NULLABLE  */
  YYSYMBOL_NULL_T = 58,                    /* NULL_T  */
  YYSYMBOL_UNIQUE = 59,                    /* UNIQUE  */
  YYSYMBOL_ORDER = 60,                     /* ORDER  */
  YYSYMBOL_BY = 61,                        /* BY  */
  YYSYMBOL_ASC = 62,                       /* ASC  */
  YYSYMBOL_EQ = 63,                        /* EQ  */
  YYSYMBOL_LT = 64,                        /* LT  */
  YYSYMBOL_GT = 65,                        /* GT  */
  YYSYMBOL_LE = 66,                        /* LE  */
  YYSYMBOL_GE = 67,                        /* GE  */
  YYSYMBOL_NE = 68,                        /* NE  */
  YYSYMBOL_NUMBER = 69,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 70,                     /* FLOAT  */
  YYSYMBOL_ID = 71,                        /* ID  */
  YYSYMBOL_SSS = 72,                       /* SSS  */
  YYSYMBOL_73_ = 73,                       /* '+'  */
  YYSYMBOL_74_ = 74,                       /* '-'  */
  YYSYMBOL_75_ = 75,                       /* '*'  */
  YYSYMBOL_76_ = 76,                       /* '/'  */
  YYSYMBOL_UMINUS = 77,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_commands = 79,                  /* commands  */
  YYSYMBOL_command_wrapper = 80,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 81,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 82,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 83,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 84,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 85,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 86,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 87,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 88,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 89,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 90,         /* create_index_stmt  */
  YYSYMBOL_attr_name_list = 91,            /* attr_name_list  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_nullable = 96,                  /* nullable  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_value_list = 100,               /* value_list  */
  YYSYMBOL_value = 101,                    /* value  */
  YYSYMBOL_unsigned_value = 102,           /* unsigned_value  */
  YYSYMBOL_delete_stmt = 103,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 104,              /* update_stmt  */
  YYSYMBOL_select_stmt = 105,              /* select_stmt  */
  YYSYMBOL_order_item = 106,               /* order_item  */
  YYSYMBOL_order = 107,                    /* order  */
  YYSYMBOL_order_item_list = 108,          /* order_item_list  */
  YYSYMBOL_agg_func_call_list = 109,       /* agg_func_call_list  */
  YYSYMBOL_agg_func_call = 110,            /* agg_func_call  */
  YYSYMBOL_agg_field_list = 111,           /* agg_field_list  */
  YYSYMBOL_agg_field = 112,                /* agg_field  */
  YYSYMBOL_agg_func = 113,                 /* agg_func  */
  YYSYMBOL_calc_stmt = 114,                /* calc_stmt  */
  YYSYMBOL_expression_list = 115,          /* expression_list  */
  YYSYMBOL_expression = 116,               /* expression  */
  YYSYMBOL_func_expr = 117,                /* func_expr  */
  YYSYMBOL_length_args = 118,              /* length_args  */
  YYSYMBOL_round_args = 119,               /* round_args  */
  YYSYMBOL_date_format_args = 120,         /* date_format_args  */
  YYSYMBOL_select_attr = 121,              /* select_attr  */
  YYSYMBOL_rel_attr = 122,                 /* rel_attr  */
  YYSYMBOL_rel_list = 123,                 /* rel_list  */
  YYSYMBOL_single_table = 124,             /* single_table  */
  YYSYMBOL_general_rel = 125,              /* general_rel  */
  YYSYMBOL_join_condition = 126,           /* join_condition  */
  YYSYMBOL_where = 127,                    /* where  */
  YYSYMBOL_condition_list = 128,           /* condition_list  */
  YYSYMBOL_condition = 129,                /* condition  */
  YYSYMBOL_comp_op = 130,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 131,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 132,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 133,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 134             /* opt_semicolon  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  79
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   267

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  145
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  263

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   328


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
       2,     2,    75,    73,     2,    74,     2,    76,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   226,   226,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   257,   263,   268,   274,   280,   286,   292,
     299,   305,   313,   332,   355,   358,   371,   381,   400,   403,
     416,   425,   437,   438,   439,   443,   446,   447,   448,   449,
     450,   451,   454,   470,   473,   484,   488,   492,   499,   503,
     507,   512,   520,   532,   547,   567,   584,   612,   637,   649,
     658,   661,   664,   671,   674,   690,   693,   707,   713,   730,
     733,   746,   751,   762,   766,   770,   774,   778,   785,   795,
     800,   811,   814,   817,   820,   823,   827,   830,   835,   839,
     843,   847,   851,   855,   862,   865,   868,   874,   882,   892,
     897,   908,   921,   928,   935,   940,   951,   954,   966,   971,
     977,   986,   991,  1001,  1004,  1010,  1013,  1019,  1022,  1026,
    1032,  1041,  1049,  1058,  1059,  1060,  1061,  1062,  1063,  1064,
    1065,  1069,  1082,  1090,  1100,  1101
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "AS",
  "CREATE", "DROP", "TABLE", "TABLES", "INDEX", "CALC", "LENGTH", "ROUND",
  "DATE_FORMAT", "INNER", "JOIN", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "DATE_T", "MIN", "MAX", "AVG",
  "COUNT", "SUM", "STRING_T", "FLOAT_T", "TEXT_T", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "LIKE", "NOT_LIKE", "IS", "NOT", "NULLABLE",
  "NULL_T", "UNIQUE", "ORDER", "BY", "ASC", "EQ", "LT", "GT", "LE", "GE",
  "NE", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'", "'*'", "'/'",
  "UMINUS", "$accept", "commands", "command_wrapper", "exit_stmt",
  "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "attr_name_list", "drop_index_stmt",
  "create_table_stmt", "attr_def_list", "attr_def", "nullable", "number",
  "type", "insert_stmt", "value_list", "value", "unsigned_value",
  "delete_stmt", "update_stmt", "select_stmt", "order_item", "order",
  "order_item_list", "agg_func_call_list", "agg_func_call",
  "agg_field_list", "agg_field", "agg_func", "calc_stmt",
  "expression_list", "expression", "func_expr", "length_args",
  "round_args", "date_format_args", "select_attr", "rel_attr", "rel_list",
  "single_table", "general_rel", "join_condition", "where",
  "condition_list", "condition", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-215)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-123)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     145,     9,    19,    30,    51,   -57,    11,  -215,   -10,     7,
      -2,  -215,  -215,  -215,  -215,  -215,     2,    27,   145,   103,
     112,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,    46,    48,   115,    74,    75,   124,   125,   126,    30,
    -215,  -215,  -215,   113,  -215,    30,  -215,  -215,    54,     1,
       4,  -215,  -215,  -215,  -215,  -215,  -215,   128,   133,   116,
     130,  -215,  -215,    88,    97,   122,   114,   127,  -215,  -215,
    -215,  -215,   152,   131,   105,  -215,   132,   -12,    30,    30,
      32,   110,  -215,    30,    30,    30,    30,    30,   111,  -215,
     117,  -215,    79,   139,    -4,   118,   143,   142,   120,   -36,
     121,   134,   135,   147,   136,  -215,   172,  -215,    62,   174,
      66,   178,  -215,  -215,  -215,    68,    68,  -215,  -215,  -215,
    -215,   128,   137,  -215,  -215,  -215,   179,    -1,   190,   189,
     193,    30,  -215,   154,    25,  -215,  -215,   176,    60,   198,
     201,   155,  -215,  -215,   156,  -215,   157,  -215,  -215,     5,
     190,   -46,   203,   159,  -215,   137,   142,   213,   -36,   146,
    -215,   185,   -36,  -215,  -215,   225,  -215,  -215,  -215,  -215,
    -215,  -215,    -6,   134,   209,   163,   212,  -215,  -215,   142,
     179,  -215,  -215,   190,   177,   165,   214,  -215,  -215,   -21,
    -215,  -215,  -215,  -215,  -215,  -215,    30,    30,   142,   167,
     171,   183,  -215,  -215,   198,  -215,   217,   173,  -215,  -215,
    -215,   182,   197,   -36,   222,   191,  -215,    58,  -215,  -215,
    -215,  -215,   223,  -215,  -215,   180,   224,   217,   181,    30,
      13,   214,  -215,  -215,    22,   217,  -215,   226,   228,    -7,
    -215,  -215,  -215,  -215,  -215,  -215,   181,  -215,  -215,  -215,
    -215,   228,  -215
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     144,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      61,    58,    59,   114,    60,     0,    97,    88,    89,   101,
      98,    84,    83,    85,    86,    87,   112,    75,     0,    68,
       0,    31,    30,     0,     0,     0,     0,     0,   142,     1,
     145,     2,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,    96,     0,     0,     0,     0,     0,     0,   102,
       0,    99,     0,     0,     0,     0,     0,   125,     0,     0,
       0,     0,     0,     0,     0,   107,     0,   108,   109,     0,
       0,     0,    95,   115,    90,    91,    92,    93,    94,   103,
     100,    75,     0,    77,    82,    81,    79,   118,   116,     0,
       0,   127,    62,     0,     0,   143,    55,     0,     0,    38,
       0,     0,    36,   104,     0,   105,     0,   106,    76,   118,
     116,     0,     0,     0,   119,     0,   125,     0,     0,     0,
     126,   128,     0,    56,    57,     0,    46,    47,    48,    49,
      50,    51,    42,     0,     0,     0,     0,   110,   111,   125,
      79,    78,   120,   116,    64,     0,    53,   139,   140,     0,
     133,   134,   135,   136,   137,   138,     0,   127,   125,     0,
       0,     0,    43,    41,    38,    37,    34,     0,    67,    80,
     117,     0,   123,     0,     0,     0,   130,   132,   129,    63,
     141,    45,     0,    44,    39,     0,     0,    34,     0,   127,
     125,    53,    52,   131,    42,    34,    32,     0,    73,    70,
     124,    65,    54,    40,    35,    33,     0,    66,    72,    71,
      69,    73,    74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,   236,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -214,  -215,  -215,    41,    73,    14,  -215,
    -215,  -215,    16,  -157,  -107,  -215,  -215,  -215,     3,  -215,
       6,   129,   160,    71,   102,  -215,  -215,     0,   -49,  -215,
    -215,  -215,  -215,  -215,   -86,  -139,  -108,  -215,  -215,  -159,
    -195,  -215,  -215,  -215,  -215,  -215,  -215
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   236,    31,    32,   184,   149,   213,   232,
     182,    33,   224,   145,    56,    34,    35,    36,   248,   260,
     257,   103,    67,   162,   136,    68,    37,    57,    58,    59,
     116,   119,   121,    70,    60,   166,   138,   139,   240,   142,
     170,   171,   206,    38,    39,    40,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      90,   117,   146,   163,    69,    98,    92,   194,   100,   163,
     258,   196,   228,  -121,    71,   208,    41,   210,    42,    72,
     133,   189,    50,   247,   160,   134,    44,  -122,    45,   135,
     218,   254,    73,    51,    52,   225,    54,   226,   144,   118,
     120,    46,    47,    48,   250,   125,   126,   127,   128,   229,
     211,    74,   212,    49,   220,   259,   122,   193,   141,    53,
     115,   146,    46,    47,    48,   146,   241,   134,    43,    75,
     164,   135,    99,    76,    49,   101,   164,    77,   211,    93,
     212,   251,    61,    62,    63,    64,    65,   154,    50,   176,
     177,   156,   169,   124,   173,   174,   178,   179,   180,    51,
      52,    53,    54,    79,    55,    94,    95,    96,    97,    50,
      61,    62,    63,    64,    65,    80,   146,    82,   181,    83,
      51,    52,    53,    54,    84,    55,    66,    94,    95,    96,
      97,    94,    95,    96,    97,    94,    95,    96,    97,    94,
      95,    96,    97,    96,    97,    85,    86,    87,    88,    89,
       1,     2,   249,   102,    91,     3,   104,   227,   169,   106,
    -113,     4,     5,     6,     7,     8,     9,    10,   107,   108,
     249,    11,    12,    13,   105,   111,   113,   109,   110,   112,
     114,   123,   129,   132,    14,    15,   140,   141,   130,   137,
     169,   143,    16,   147,    17,   151,   153,    18,   155,   197,
     198,   199,   157,   167,   161,   148,   150,   152,   159,   200,
     201,   202,   203,   204,   205,   165,   168,   172,   175,    94,
      95,    96,    97,   183,   185,   187,   186,   191,   195,   188,
     192,   207,   209,   215,   216,   217,   222,   221,   230,   223,
     231,   233,   235,   238,   237,   239,   242,   244,   246,   243,
     255,   245,    53,   256,    78,   234,   214,   252,   253,   261,
     158,   219,   131,   190,     0,     0,     0,   262
};

static const yytype_int16 yycheck[] =
{
      49,    87,   109,     4,     4,     4,    55,   166,     4,     4,
      17,   168,   207,    14,    71,   172,     7,    23,     9,     8,
      24,   160,    58,   237,   132,    71,     7,    14,     9,    75,
     189,   245,    42,    69,    70,    56,    72,    58,    74,    88,
      89,    11,    12,    13,   239,    94,    95,    96,    97,   208,
      56,    44,    58,    23,   193,    62,    24,   165,    45,    71,
      72,   168,    11,    12,    13,   172,   223,    71,    59,    71,
      71,    75,    71,    71,    23,    71,    71,    50,    56,    25,
      58,   240,    31,    32,    33,    34,    35,    25,    58,    29,
      30,    25,   141,    93,    69,    70,    36,    37,    38,    69,
      70,    71,    72,     0,    74,    73,    74,    75,    76,    58,
      31,    32,    33,    34,    35,     3,   223,    71,    58,    71,
      69,    70,    71,    72,     9,    74,    75,    73,    74,    75,
      76,    73,    74,    75,    76,    73,    74,    75,    76,    73,
      74,    75,    76,    75,    76,    71,    71,    23,    23,    23,
       5,     6,   238,    25,    41,    10,    23,   206,   207,    71,
      44,    16,    17,    18,    19,    20,    21,    22,    71,    47,
     256,    26,    27,    28,    44,    23,    71,    63,    51,    48,
      48,    71,    71,    44,    39,    40,    43,    45,    71,    71,
     239,    71,    47,    72,    49,    48,    24,    52,    24,    53,
      54,    55,    24,    14,    25,    71,    71,    71,    71,    63,
      64,    65,    66,    67,    68,    25,    23,    63,    42,    73,
      74,    75,    76,    25,    23,    69,    71,    24,    15,    72,
      71,    46,     7,    24,    71,    23,    71,    60,    71,    25,
      69,    58,    25,    61,    71,    48,    24,    24,    24,    58,
      24,    71,    71,    25,    18,   214,   183,   241,   244,   256,
     131,   190,   102,   161,    -1,    -1,    -1,   261
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    10,    16,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    39,    40,    47,    49,    52,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    92,    93,    99,   103,   104,   105,   114,   131,   132,
     133,     7,     9,    59,     7,     9,    11,    12,    13,    23,
      58,    69,    70,    71,    72,    74,   102,   115,   116,   117,
     122,    31,    32,    33,    34,    35,    75,   110,   113,   115,
     121,    71,     8,    42,    44,    71,    71,    50,    80,     0,
       3,   134,    71,    71,     9,    71,    71,    23,    23,    23,
     116,    41,   116,    25,    73,    74,    75,    76,     4,    71,
       4,    71,    25,   109,    23,    44,    71,    71,    47,    63,
      51,    23,    48,    71,    48,    72,   118,   122,   116,   119,
     116,   120,    24,    71,   115,   116,   116,   116,   116,    71,
      71,   110,    44,    24,    71,    75,   112,    71,   124,   125,
      43,    45,   127,    71,    74,   101,   102,    72,    71,    95,
      71,    48,    71,    24,    25,    24,    25,    24,   109,    71,
     124,    25,   111,     4,    71,    25,   123,    14,    23,   116,
     128,   129,    63,    69,    70,    42,    29,    30,    36,    37,
      38,    58,    98,    25,    94,    23,    71,    69,    72,   123,
     112,    24,    71,   124,   127,    15,   101,    53,    54,    55,
      63,    64,    65,    66,    67,    68,   130,    46,   101,     7,
      23,    56,    58,    96,    95,    24,    71,    23,   127,   111,
     123,    60,    71,    25,   100,    56,    58,   116,   128,   127,
      71,    69,    97,    58,    94,    25,    91,    71,    61,    48,
     126,   101,    24,    58,    24,    71,    24,    91,   106,   122,
     128,   127,   100,    96,    91,    24,    25,   108,    17,    62,
     107,   106,   108
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    90,    91,    91,    92,    93,    94,    94,
      95,    95,    96,    96,    96,    97,    98,    98,    98,    98,
      98,    98,    99,   100,   100,   101,   101,   101,   102,   102,
     102,   102,   103,   104,   105,   105,   105,   105,   105,   106,
     107,   107,   107,   108,   108,   109,   109,   110,   110,   111,
     111,   112,   112,   113,   113,   113,   113,   113,   114,   115,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   117,   118,   118,   119,
     119,   120,   121,   121,   122,   122,   123,   123,   124,   124,
     124,   125,   125,   126,   126,   127,   127,   128,   128,   128,
     129,   129,   129,   130,   130,   130,   130,   130,   130,   130,
     130,   131,   132,   133,   134,   134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     2,     2,     1,     1,
       1,     1,     4,     7,     6,     9,    10,     7,     2,     2,
       0,     1,     1,     0,     3,     0,     3,     3,     5,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     2,
       3,     1,     2,     3,     4,     4,     4,     1,     1,     1,
       3,     3,     1,     1,     1,     3,     0,     3,     1,     2,
       3,     1,     5,     0,     2,     0,     2,     0,     1,     3,
       3,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     7,     2,     4,     0,     1
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
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 227 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1837 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 257 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1846 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 263 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1854 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 268 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1862 "yacc_sql.cpp"
    break;

  case 26: /* begin_stmt: TRX_BEGIN  */
#line 274 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1870 "yacc_sql.cpp"
    break;

  case 27: /* commit_stmt: TRX_COMMIT  */
#line 280 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1878 "yacc_sql.cpp"
    break;

  case 28: /* rollback_stmt: TRX_ROLLBACK  */
#line 286 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1886 "yacc_sql.cpp"
    break;

  case 29: /* drop_table_stmt: DROP TABLE ID  */
#line 292 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 30: /* show_tables_stmt: SHOW TABLES  */
#line 299 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 31: /* desc_table_stmt: DESC ID  */
#line 305 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1914 "yacc_sql.cpp"
    break;

  case 32: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID attr_name_list RBRACE  */
#line 314 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);

      std::vector<std::string> *attribute_names = (yyvsp[-1].attr_names);
      if (attribute_names != nullptr) {
         create_index.attribute_names.swap(*attribute_names);
      }
      create_index.attribute_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());

      create_index.unique = false;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1937 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_name_list RBRACE  */
#line 333 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);

      std::vector<std::string> *attribute_names = (yyvsp[-1].attr_names);
      if (attribute_names != nullptr) {
          create_index.attribute_names.swap(*attribute_names);
      }
      create_index.attribute_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());

      create_index.unique = true;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 1960 "yacc_sql.cpp"
    break;

  case 34: /* attr_name_list: %empty  */
#line 355 "yacc_sql.y"
    {
      (yyval.attr_names) = nullptr;
    }
#line 1968 "yacc_sql.cpp"
    break;

  case 35: /* attr_name_list: COMMA ID attr_name_list  */
#line 359 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_names) != nullptr) {
        (yyval.attr_names) = (yyvsp[0].attr_names);
      } else {
        (yyval.attr_names) = new std::vector<std::string>;
      }
      (yyval.attr_names)->emplace_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 1982 "yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 372 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 37: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 382 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 2014 "yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 400 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2022 "yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 404 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 417 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2049 "yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 426 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2062 "yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 437 "yacc_sql.y"
    { (yyval.bools) = true; }
#line 2068 "yacc_sql.cpp"
    break;

  case 43: /* nullable: NULL_T  */
#line 438 "yacc_sql.y"
             { (yyval.bools) = true; }
#line 2074 "yacc_sql.cpp"
    break;

  case 44: /* nullable: NOT NULL_T  */
#line 439 "yacc_sql.y"
                 { (yyval.bools) = false; }
#line 2080 "yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 443 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2086 "yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 446 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2092 "yacc_sql.cpp"
    break;

  case 47: /* type: DATE_T  */
#line 447 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2098 "yacc_sql.cpp"
    break;

  case 48: /* type: STRING_T  */
#line 448 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2104 "yacc_sql.cpp"
    break;

  case 49: /* type: FLOAT_T  */
#line 449 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2110 "yacc_sql.cpp"
    break;

  case 50: /* type: TEXT_T  */
#line 450 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2116 "yacc_sql.cpp"
    break;

  case 51: /* type: NULL_T  */
#line 451 "yacc_sql.y"
               { (yyval.number)=NULLS; }
#line 2122 "yacc_sql.cpp"
    break;

  case 52: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 455 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2138 "yacc_sql.cpp"
    break;

  case 53: /* value_list: %empty  */
#line 470 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2146 "yacc_sql.cpp"
    break;

  case 54: /* value_list: COMMA value value_list  */
#line 473 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2160 "yacc_sql.cpp"
    break;

  case 55: /* value: unsigned_value  */
#line 484 "yacc_sql.y"
                   {
      (yyval.value) = (yyvsp[0].value);
      (yyloc) = (yylsp[0]);
    }
#line 2169 "yacc_sql.cpp"
    break;

  case 56: /* value: '-' NUMBER  */
#line 488 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2178 "yacc_sql.cpp"
    break;

  case 57: /* value: '-' FLOAT  */
#line 492 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 58: /* unsigned_value: NUMBER  */
#line 499 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2196 "yacc_sql.cpp"
    break;

  case 59: /* unsigned_value: FLOAT  */
#line 503 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2205 "yacc_sql.cpp"
    break;

  case 60: /* unsigned_value: SSS  */
#line 507 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2215 "yacc_sql.cpp"
    break;

  case 61: /* unsigned_value: NULL_T  */
#line 512 "yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_type(NULLS);
      (yyloc) = (yylsp[0]);
    }
#line 2225 "yacc_sql.cpp"
    break;

  case 62: /* delete_stmt: DELETE FROM ID where  */
#line 521 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 63: /* update_stmt: UPDATE ID SET ID EQ value where  */
#line 533 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->update.attribute_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.value = *(yyvsp[-1].value);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2256 "yacc_sql.cpp"
    break;

  case 64: /* select_stmt: SELECT select_attr FROM single_table rel_list where  */
#line 548 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-4].expression_list) != nullptr) {
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[-4].expression_list));
        delete (yyvsp[-4].expression_list);
      }
      if ((yyvsp[-1].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back(std::move(*(yyvsp[-2].single_table)));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-2].single_table));
    }
#line 2280 "yacc_sql.cpp"
    break;

  case 65: /* select_stmt: SELECT select_attr FROM general_rel INNER JOIN ID join_condition where  */
#line 568 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-7].expression_list) != nullptr) {
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[-7].expression_list));
        delete (yyvsp[-7].expression_list);
      }

      (yyval.sql_node)->selection.join_relation = new JoinSqlNode(JT_INNER, (yyvsp[-5].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-2].string)), std::move(*(yyvsp[-1].condition_list)));
      delete (yyvsp[-1].condition_list);

      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-2].string));
    }
#line 2301 "yacc_sql.cpp"
    break;

  case 66: /* select_stmt: SELECT select_attr FROM single_table rel_list where ORDER BY order_item order_item_list  */
#line 585 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }
      if ((yyvsp[-5].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-5].relation_list));
        delete (yyvsp[-5].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back(std::move(*(yyvsp[-6].single_table)));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      std::vector<OrderBy> *order_by_attrs = (yyvsp[0].order_item_list);
      if(order_by_attrs != nullptr) {
        (yyval.sql_node)->selection.order_by.swap(*order_by_attrs);
      }
      (yyval.sql_node)->selection.order_by.emplace_back(*(yyvsp[-1].order_item));
      std::reverse((yyval.sql_node)->selection.order_by.begin(), (yyval.sql_node)->selection.order_by.end());
      delete (yyvsp[-1].order_item);

      if ((yyvsp[-4].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-4].condition_list));
        delete (yyvsp[-4].condition_list);
      }
      free((yyvsp[-6].single_table));
    }
#line 2333 "yacc_sql.cpp"
    break;

  case 67: /* select_stmt: SELECT agg_func_call agg_func_call_list FROM single_table rel_list where  */
#line 613 "yacc_sql.y"
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);

        if((yyvsp[-4].agg_func_call_list) != nullptr) {
            (yyval.sql_node)->selection.agg_funcs.swap(*(yyvsp[-4].agg_func_call_list));
            delete (yyvsp[-4].agg_func_call_list);
        }

        (yyval.sql_node)->selection.agg_funcs.push_back(*(yyvsp[-5].agg_func_call));
        delete (yyvsp[-5].agg_func_call);

        if ((yyvsp[-1].relation_list) != nullptr) {
            (yyval.sql_node)->selection.relations.swap(*(yyvsp[-1].relation_list));
            delete (yyvsp[-1].relation_list);
        }
        (yyval.sql_node)->selection.relations.push_back(*(yyvsp[-2].single_table));
        std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

         if ((yyvsp[0].condition_list) != nullptr) {
            (yyval.sql_node)->selection.conditions.swap(*(yyvsp[0].condition_list));
            delete (yyvsp[0].condition_list);
         }
         free((yyvsp[-2].single_table));
    }
#line 2362 "yacc_sql.cpp"
    break;

  case 68: /* select_stmt: SELECT expression_list  */
#line 638 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2375 "yacc_sql.cpp"
    break;

  case 69: /* order_item: rel_attr order  */
#line 649 "yacc_sql.y"
                       {
        (yyval.order_item) = new OrderBy;
        (yyval.order_item)->order_by_attribute = *(yyvsp[-1].rel_attr);
        (yyval.order_item)->order = (yyvsp[0].bools);
        delete (yyvsp[-1].rel_attr);
	}
#line 2386 "yacc_sql.cpp"
    break;

  case 70: /* order: %empty  */
#line 658 "yacc_sql.y"
                    {
		(yyval.bools) = 0;
	}
#line 2394 "yacc_sql.cpp"
    break;

  case 71: /* order: ASC  */
#line 661 "yacc_sql.y"
              {
		(yyval.bools) = 0;
	}
#line 2402 "yacc_sql.cpp"
    break;

  case 72: /* order: DESC  */
#line 664 "yacc_sql.y"
               {
		(yyval.bools) = 1;
	}
#line 2410 "yacc_sql.cpp"
    break;

  case 73: /* order_item_list: %empty  */
#line 671 "yacc_sql.y"
        {
	    (yyval.order_item_list) = nullptr;
	}
#line 2418 "yacc_sql.cpp"
    break;

  case 74: /* order_item_list: COMMA order_item order_item_list  */
#line 675 "yacc_sql.y"
        {
        if((yyvsp[0].order_item_list) != nullptr) {
            (yyval.order_item_list) = (yyvsp[0].order_item_list);
        } else {
            (yyval.order_item_list) = new std::vector<OrderBy>;
        }
        (yyval.order_item_list)->emplace_back(*(yyvsp[-1].order_item));
        delete (yyvsp[-1].order_item);
	}
#line 2432 "yacc_sql.cpp"
    break;

  case 75: /* agg_func_call_list: %empty  */
#line 690 "yacc_sql.y"
        {
          (yyval.agg_func_call_list) = nullptr;
        }
#line 2440 "yacc_sql.cpp"
    break;

  case 76: /* agg_func_call_list: COMMA agg_func_call agg_func_call_list  */
#line 693 "yacc_sql.y"
                                                 {
          if ((yyvsp[0].agg_func_call_list) != nullptr) {
            (yyval.agg_func_call_list) = (yyvsp[0].agg_func_call_list);
          } else {
            (yyval.agg_func_call_list) = new std::vector<AggregationFuncSqlNode>;
          }

          (yyval.agg_func_call_list)->push_back(*(yyvsp[-1].agg_func_call));

          delete (yyvsp[-1].agg_func_call);
        }
#line 2456 "yacc_sql.cpp"
    break;

  case 77: /* agg_func_call: agg_func LBRACE RBRACE  */
#line 708 "yacc_sql.y"
    {
      (yyval.agg_func_call) = new AggregationFuncSqlNode;
      (yyval.agg_func_call)->func = (yyvsp[-2].agg_func);
      (yyval.agg_func_call)->attr.attribute_name = "";
    }
#line 2466 "yacc_sql.cpp"
    break;

  case 78: /* agg_func_call: agg_func LBRACE agg_field agg_field_list RBRACE  */
#line 714 "yacc_sql.y"
    {
        (yyval.agg_func_call) = new AggregationFuncSqlNode;
        (yyval.agg_func_call)->func = (yyvsp[-4].agg_func);
        if((yyvsp[-1].field_list) == nullptr) {
          (yyval.agg_func_call)->attr.attribute_name = (yyvsp[-2].field)->name;
        }else {
          (yyval.agg_func_call)->attr.attribute_name = "";
          delete((yyvsp[-1].field_list));
        }
        delete((yyvsp[-2].field));
    }
#line 2482 "yacc_sql.cpp"
    break;

  case 79: /* agg_field_list: %empty  */
#line 730 "yacc_sql.y"
  {
    (yyval.field_list)=nullptr;
  }
#line 2490 "yacc_sql.cpp"
    break;

  case 80: /* agg_field_list: COMMA agg_field agg_field_list  */
#line 734 "yacc_sql.y"
  {
    if ((yyvsp[0].field_list) != nullptr) {
      (yyval.field_list) = (yyvsp[0].field_list);
    } else {
      (yyval.field_list) = new std::vector<std::string>;
    }
    (yyval.field_list)->push_back((yyvsp[-1].field)->name);
    delete((yyvsp[-1].field));
  }
#line 2504 "yacc_sql.cpp"
    break;

  case 81: /* agg_field: '*'  */
#line 747 "yacc_sql.y"
  {
    (yyval.field) = new AggField;
    (yyval.field)->name = "*";
  }
#line 2513 "yacc_sql.cpp"
    break;

  case 82: /* agg_field: ID  */
#line 752 "yacc_sql.y"
  {
    (yyval.field) = new AggField;
    (yyval.field)->name = (yyvsp[0].string);
    free((yyvsp[0].string));
  }
#line 2523 "yacc_sql.cpp"
    break;

  case 83: /* agg_func: MAX  */
#line 763 "yacc_sql.y"
    {
       (yyval.agg_func)=MAX_FUNC;
    }
#line 2531 "yacc_sql.cpp"
    break;

  case 84: /* agg_func: MIN  */
#line 767 "yacc_sql.y"
    {
       (yyval.agg_func)=MIN_FUNC;
    }
#line 2539 "yacc_sql.cpp"
    break;

  case 85: /* agg_func: AVG  */
#line 771 "yacc_sql.y"
    {
       (yyval.agg_func)=AVG_FUNC;
    }
#line 2547 "yacc_sql.cpp"
    break;

  case 86: /* agg_func: COUNT  */
#line 775 "yacc_sql.y"
    {
       (yyval.agg_func)=COUNT_FUNC;
    }
#line 2555 "yacc_sql.cpp"
    break;

  case 87: /* agg_func: SUM  */
#line 779 "yacc_sql.y"
    {
       (yyval.agg_func)=SUM_FUNC;
    }
#line 2563 "yacc_sql.cpp"
    break;

  case 88: /* calc_stmt: CALC expression_list  */
#line 786 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2574 "yacc_sql.cpp"
    break;

  case 89: /* expression_list: expression  */
#line 796 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2583 "yacc_sql.cpp"
    break;

  case 90: /* expression_list: expression COMMA expression_list  */
#line 801 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2596 "yacc_sql.cpp"
    break;

  case 91: /* expression: expression '+' expression  */
#line 811 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2604 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '-' expression  */
#line 814 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '*' expression  */
#line 817 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '/' expression  */
#line 820 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 95: /* expression: LBRACE expression RBRACE  */
#line 823 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2637 "yacc_sql.cpp"
    break;

  case 96: /* expression: '-' expression  */
#line 827 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2645 "yacc_sql.cpp"
    break;

  case 97: /* expression: unsigned_value  */
#line 830 "yacc_sql.y"
                     {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 98: /* expression: rel_attr  */
#line 835 "yacc_sql.y"
               {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      (yyval.expression)->set_name((yyvsp[0].rel_attr)->name());
    }
#line 2664 "yacc_sql.cpp"
    break;

  case 99: /* expression: rel_attr ID  */
#line 839 "yacc_sql.y"
                  {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-1].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 100: /* expression: rel_attr AS ID  */
#line 843 "yacc_sql.y"
                     {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-2].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2682 "yacc_sql.cpp"
    break;

  case 101: /* expression: func_expr  */
#line 847 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2691 "yacc_sql.cpp"
    break;

  case 102: /* expression: func_expr ID  */
#line 851 "yacc_sql.y"
                   {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2700 "yacc_sql.cpp"
    break;

  case 103: /* expression: func_expr AS ID  */
#line 855 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 104: /* func_expr: LENGTH LBRACE length_args RBRACE  */
#line 862 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, *(yyvsp[-1].func_args));
    }
#line 2717 "yacc_sql.cpp"
    break;

  case 105: /* func_expr: ROUND LBRACE round_args RBRACE  */
#line 865 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, *(yyvsp[-1].func_args));
    }
#line 2725 "yacc_sql.cpp"
    break;

  case 106: /* func_expr: DATE_FORMAT LBRACE date_format_args RBRACE  */
#line 868 "yacc_sql.y"
                                                 {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, *(yyvsp[-1].func_args));
    }
#line 2733 "yacc_sql.cpp"
    break;

  case 107: /* length_args: SSS  */
#line 874 "yacc_sql.y"
        {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *value_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      free(tmp);
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 108: /* length_args: rel_attr  */
#line 882 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      RelAttrExprSqlNode *attr_expr = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      attr_expr->set_name((yyvsp[0].rel_attr)->name());
      std::unique_ptr<Expression> target(attr_expr);
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2758 "yacc_sql.cpp"
    break;

  case 109: /* round_args: expression  */
#line 892 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[0].expression));
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2768 "yacc_sql.cpp"
    break;

  case 110: /* round_args: expression COMMA NUMBER  */
#line 897 "yacc_sql.y"
                              {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      ValueExpr *value_expr = new ValueExpr(Value((int)(yyvsp[0].number)));
      std::unique_ptr<Expression> precise(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(precise));
    }
#line 2781 "yacc_sql.cpp"
    break;

  case 111: /* date_format_args: expression COMMA SSS  */
#line 908 "yacc_sql.y"
                         {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *format_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      std::unique_ptr<Expression> format(format_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(format));
    }
#line 2795 "yacc_sql.cpp"
    break;

  case 112: /* select_attr: '*'  */
#line 921 "yacc_sql.y"
        {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      (yyval.expression_list)->emplace_back(new RelAttrExprSqlNode(attr));
    }
#line 2807 "yacc_sql.cpp"
    break;

  case 113: /* select_attr: expression_list  */
#line 928 "yacc_sql.y"
                      {
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2816 "yacc_sql.cpp"
    break;

  case 114: /* rel_attr: ID  */
#line 935 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2826 "yacc_sql.cpp"
    break;

  case 115: /* rel_attr: ID DOT ID  */
#line 940 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 116: /* rel_list: %empty  */
#line 951 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 117: /* rel_list: COMMA single_table rel_list  */
#line 954 "yacc_sql.y"
                                  {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->push_back(std::move(*(yyvsp[-1].single_table)));
    }
#line 2860 "yacc_sql.cpp"
    break;

  case 118: /* single_table: ID  */
#line 967 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2869 "yacc_sql.cpp"
    break;

  case 119: /* single_table: ID ID  */
#line 972 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-1].string), (yyvsp[0].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 120: /* single_table: ID AS ID  */
#line 978 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-2].string), (yyvsp[0].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 121: /* general_rel: ID  */
#line 987 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode((yyvsp[0].string));
       free((yyvsp[0].string));
    }
#line 2898 "yacc_sql.cpp"
    break;

  case 122: /* general_rel: general_rel INNER JOIN ID join_condition  */
#line 992 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode(
        new JoinSqlNode(JT_INNER, (yyvsp[-4].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-1].string)), std::move(*(yyvsp[0].condition_list)))
       );
       free((yyvsp[-1].string));
    }
#line 2909 "yacc_sql.cpp"
    break;

  case 123: /* join_condition: %empty  */
#line 1001 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2917 "yacc_sql.cpp"
    break;

  case 124: /* join_condition: ON condition_list  */
#line 1004 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2925 "yacc_sql.cpp"
    break;

  case 125: /* where: %empty  */
#line 1010 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2933 "yacc_sql.cpp"
    break;

  case 126: /* where: WHERE condition_list  */
#line 1013 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2941 "yacc_sql.cpp"
    break;

  case 127: /* condition_list: %empty  */
#line 1019 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2949 "yacc_sql.cpp"
    break;

  case 128: /* condition_list: condition  */
#line 1022 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: condition AND condition_list  */
#line 1026 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 130: /* condition: expression IS NULL_T  */
#line 1033 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value value = Value();
      value.set_type(NULLS);
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NULL, std::move(left), std::move(right));
    }
#line 2980 "yacc_sql.cpp"
    break;

  case 131: /* condition: expression IS NOT NULL_T  */
#line 1042 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      Value value = Value();
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NOT_NULL, std::move(left), std::move(right));
    }
#line 2992 "yacc_sql.cpp"
    break;

  case 132: /* condition: expression comp_op expression  */
#line 1050 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3002 "yacc_sql.cpp"
    break;

  case 133: /* comp_op: EQ  */
#line 1058 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3008 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: LT  */
#line 1059 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3014 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: GT  */
#line 1060 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3020 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: LE  */
#line 1061 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3026 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: GE  */
#line 1062 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3032 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: NE  */
#line 1063 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3038 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: LIKE  */
#line 1064 "yacc_sql.y"
           { (yyval.comp) = LIKES; }
#line 3044 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: NOT_LIKE  */
#line 1065 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKES; }
#line 3050 "yacc_sql.cpp"
    break;

  case 141: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1070 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3064 "yacc_sql.cpp"
    break;

  case 142: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1083 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3073 "yacc_sql.cpp"
    break;

  case 143: /* set_variable_stmt: SET ID EQ value  */
#line 1091 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3085 "yacc_sql.cpp"
    break;


#line 3089 "yacc_sql.cpp"

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
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
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
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
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
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
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

#line 1103 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
