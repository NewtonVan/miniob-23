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
  YYSYMBOL_STRING_T = 35,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 36,                   /* FLOAT_T  */
  YYSYMBOL_TEXT_T = 37,                    /* TEXT_T  */
  YYSYMBOL_HELP = 38,                      /* HELP  */
  YYSYMBOL_EXIT = 39,                      /* EXIT  */
  YYSYMBOL_DOT = 40,                       /* DOT  */
  YYSYMBOL_INTO = 41,                      /* INTO  */
  YYSYMBOL_VALUES = 42,                    /* VALUES  */
  YYSYMBOL_FROM = 43,                      /* FROM  */
  YYSYMBOL_WHERE = 44,                     /* WHERE  */
  YYSYMBOL_AND = 45,                       /* AND  */
  YYSYMBOL_OR = 46,                        /* OR  */
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
  YYSYMBOL_GROUP = 61,                     /* GROUP  */
  YYSYMBOL_HAVING = 62,                    /* HAVING  */
  YYSYMBOL_BY = 63,                        /* BY  */
  YYSYMBOL_ASC = 64,                       /* ASC  */
  YYSYMBOL_EQ = 65,                        /* EQ  */
  YYSYMBOL_LT = 66,                        /* LT  */
  YYSYMBOL_GT = 67,                        /* GT  */
  YYSYMBOL_LE = 68,                        /* LE  */
  YYSYMBOL_GE = 69,                        /* GE  */
  YYSYMBOL_NE = 70,                        /* NE  */
  YYSYMBOL_IN = 71,                        /* IN  */
  YYSYMBOL_EXISTS = 72,                    /* EXISTS  */
  YYSYMBOL_NUMBER = 73,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 74,                     /* FLOAT  */
  YYSYMBOL_ID = 75,                        /* ID  */
  YYSYMBOL_SSS = 76,                       /* SSS  */
  YYSYMBOL_77_ = 77,                       /* '+'  */
  YYSYMBOL_78_ = 78,                       /* '-'  */
  YYSYMBOL_79_ = 79,                       /* '*'  */
  YYSYMBOL_80_ = 80,                       /* '/'  */
  YYSYMBOL_UMINUS = 81,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 82,                  /* $accept  */
  YYSYMBOL_commands = 83,                  /* commands  */
  YYSYMBOL_command_wrapper = 84,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 85,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 86,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 87,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 88,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 89,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 90,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 91,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 92,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 93,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 94,         /* create_index_stmt  */
  YYSYMBOL_attr_name_list = 95,            /* attr_name_list  */
  YYSYMBOL_drop_index_stmt = 96,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 97,         /* create_table_stmt  */
  YYSYMBOL_create_table_select_stmt = 98,  /* create_table_select_stmt  */
  YYSYMBOL_attr_def_list = 99,             /* attr_def_list  */
  YYSYMBOL_attr_def = 100,                 /* attr_def  */
  YYSYMBOL_nullable = 101,                 /* nullable  */
  YYSYMBOL_number = 102,                   /* number  */
  YYSYMBOL_type = 103,                     /* type  */
  YYSYMBOL_insert_stmt = 104,              /* insert_stmt  */
  YYSYMBOL_value_list = 105,               /* value_list  */
  YYSYMBOL_value = 106,                    /* value  */
  YYSYMBOL_unsigned_value = 107,           /* unsigned_value  */
  YYSYMBOL_delete_stmt = 108,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 109,              /* update_stmt  */
  YYSYMBOL_update_list = 110,              /* update_list  */
  YYSYMBOL_update_unit = 111,              /* update_unit  */
  YYSYMBOL_select_stmt = 112,              /* select_stmt  */
  YYSYMBOL_sub_query_two_expr = 113,       /* sub_query_two_expr  */
  YYSYMBOL_sub_query_expr = 114,           /* sub_query_expr  */
  YYSYMBOL_sub_query_list_expr = 115,      /* sub_query_list_expr  */
  YYSYMBOL_order_item = 116,               /* order_item  */
  YYSYMBOL_order = 117,                    /* order  */
  YYSYMBOL_order_item_list = 118,          /* order_item_list  */
  YYSYMBOL_calc_stmt = 119,                /* calc_stmt  */
  YYSYMBOL_expression_list = 120,          /* expression_list  */
  YYSYMBOL_expression_alias = 121,         /* expression_alias  */
  YYSYMBOL_expression = 122,               /* expression  */
  YYSYMBOL_func_expr = 123,                /* func_expr  */
  YYSYMBOL_agg_expr = 124,                 /* agg_expr  */
  YYSYMBOL_agg_field_list = 125,           /* agg_field_list  */
  YYSYMBOL_agg_field = 126,                /* agg_field  */
  YYSYMBOL_agg_func = 127,                 /* agg_func  */
  YYSYMBOL_length_args = 128,              /* length_args  */
  YYSYMBOL_round_args = 129,               /* round_args  */
  YYSYMBOL_date_format_args = 130,         /* date_format_args  */
  YYSYMBOL_select_attr = 131,              /* select_attr  */
  YYSYMBOL_rel_attr = 132,                 /* rel_attr  */
  YYSYMBOL_rel_list = 133,                 /* rel_list  */
  YYSYMBOL_single_table = 134,             /* single_table  */
  YYSYMBOL_general_rel = 135,              /* general_rel  */
  YYSYMBOL_join_condition = 136,           /* join_condition  */
  YYSYMBOL_group_by = 137,                 /* group_by  */
  YYSYMBOL_having = 138,                   /* having  */
  YYSYMBOL_rel_attr_list = 139,            /* rel_attr_list  */
  YYSYMBOL_where = 140,                    /* where  */
  YYSYMBOL_select_where = 141,             /* select_where  */
  YYSYMBOL_condition_or = 142,             /* condition_or  */
  YYSYMBOL_condition_and = 143,            /* condition_and  */
  YYSYMBOL_condition_list = 144,           /* condition_list  */
  YYSYMBOL_condition = 145,                /* condition  */
  YYSYMBOL_comp_op = 146,                  /* comp_op  */
  YYSYMBOL_load_data_stmt = 147,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 148,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 149,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 150             /* opt_semicolon  */
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
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   365

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  69
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  316

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


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
       2,     2,    79,    77,     2,    78,     2,    80,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    81
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   245,   245,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   277,   283,   288,   294,   300,   306,
     312,   319,   325,   333,   352,   375,   378,   391,   401,   419,
     426,   445,   448,   461,   470,   482,   483,   484,   488,   491,
     492,   493,   494,   495,   496,   499,   515,   518,   529,   533,
     537,   544,   548,   552,   557,   565,   577,   591,   596,   609,
     613,   620,   646,   669,   697,   709,   713,   719,   744,   759,
     768,   771,   774,   781,   784,   797,   807,   812,   821,   825,
     837,   842,   850,   853,   856,   859,   862,   866,   869,   874,
     878,   882,   886,   891,   902,   905,   908,   917,   933,   976,
     979,   994,   999,  1007,  1011,  1015,  1019,  1023,  1037,  1045,
    1055,  1060,  1071,  1084,  1091,  1100,  1109,  1116,  1121,  1132,
    1135,  1147,  1152,  1158,  1167,  1172,  1182,  1185,  1193,  1197,
    1215,  1218,  1236,  1239,  1253,  1256,  1262,  1265,  1271,  1274,
    1281,  1284,  1293,  1296,  1300,  1306,  1315,  1323,  1329,  1335,
    1341,  1347,  1353,  1361,  1362,  1363,  1364,  1365,  1366,  1367,
    1368,  1372,  1385,  1393,  1403,  1404
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
  "COUNT", "STRING_T", "FLOAT_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO",
  "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "LIKE", "NOT_LIKE", "IS", "NOT", "NULLABLE",
  "NULL_T", "UNIQUE", "ORDER", "GROUP", "HAVING", "BY", "ASC", "EQ", "LT",
  "GT", "LE", "GE", "NE", "IN", "EXISTS", "NUMBER", "FLOAT", "ID", "SSS",
  "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "attr_name_list",
  "drop_index_stmt", "create_table_stmt", "create_table_select_stmt",
  "attr_def_list", "attr_def", "nullable", "number", "type", "insert_stmt",
  "value_list", "value", "unsigned_value", "delete_stmt", "update_stmt",
  "update_list", "update_unit", "select_stmt", "sub_query_two_expr",
  "sub_query_expr", "sub_query_list_expr", "order_item", "order",
  "order_item_list", "calc_stmt", "expression_list", "expression_alias",
  "expression", "func_expr", "agg_expr", "agg_field_list", "agg_field",
  "agg_func", "length_args", "round_args", "date_format_args",
  "select_attr", "rel_attr", "rel_list", "single_table", "general_rel",
  "join_condition", "group_by", "having", "rel_attr_list", "where",
  "select_where", "condition_or", "condition_and", "condition_list",
  "condition", "comp_op", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-251)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-136)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     272,    16,    77,   198,    91,   -51,    25,  -251,    21,    26,
     -37,  -251,  -251,  -251,  -251,  -251,    10,    41,   272,    76,
     110,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,    64,    66,   120,    79,    93,   125,   140,   151,
     192,  -251,  -251,  -251,  -251,  -251,  -251,  -251,    -1,  -251,
     198,  -251,  -251,  -251,   156,    31,  -251,  -251,   153,  -251,
       3,   141,   145,  -251,  -251,   121,   126,   136,   130,   155,
    -251,  -251,  -251,  -251,    17,   164,   139,  -251,   168,   -21,
     198,   198,    91,   -13,   -45,  -251,   198,   142,   198,  -251,
     198,   198,   198,   198,    96,   147,  -251,   152,   178,   189,
     159,   -30,   160,   212,   162,   163,   187,   169,   199,  -251,
     219,  -251,    38,   221,    65,   225,  -251,   208,  -251,  -251,
    -251,  -251,  -251,  -251,    80,    80,  -251,  -251,  -251,  -251,
     227,  -251,  -251,     5,   228,   240,   232,   124,  -251,   194,
       1,  -251,    88,  -251,  -251,   220,  -251,   211,   238,   241,
     200,  -251,   204,  -251,   207,  -251,   205,  -251,   209,    59,
     259,   210,  -251,   209,   242,   280,   -30,  -251,  -251,  -251,
    -251,  -251,  -251,  -251,  -251,   260,  -251,   251,   198,   184,
     159,  -251,  -251,  -251,   290,  -251,  -251,  -251,  -251,  -251,
    -251,    -7,   162,   263,   226,   279,  -251,  -251,     4,   228,
     227,  -251,  -251,   228,   124,   112,   229,   278,    63,   108,
     282,   282,   198,   124,    73,   291,  -251,  -251,  -251,   231,
     235,   254,  -251,  -251,   238,   212,   284,   243,   242,  -251,
    -251,   271,   275,  -251,   270,   273,  -251,   274,   -30,   299,
     276,  -251,   282,   282,    54,  -251,  -251,  -251,  -251,    73,
    -251,  -251,  -251,   311,  -251,  -251,  -251,   266,   318,   284,
     319,   124,   124,   269,   269,   124,     6,   278,  -251,  -251,
    -251,  -251,   278,    75,   284,  -251,   321,  -251,   275,  -251,
     322,    -5,   323,  -251,   285,  -251,   325,  -251,  -251,  -251,
     269,  -251,  -251,  -251,  -251,   269,   288,  -251,  -251,   322,
     323,   124,  -251,  -251,  -251,  -251
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     174,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     8,     9,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   113,   115,   116,    64,    61,    62,   127,    63,
       0,    98,   101,    85,    88,    86,   100,   102,     0,    99,
     123,    74,     0,    32,    31,     0,     0,     0,     0,     0,
     172,     1,   175,     2,     0,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,    97,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,   125,     0,     0,   144,
       0,     0,     0,     0,     0,     0,     0,     0,   127,   118,
       0,   119,   120,     0,     0,     0,   126,     0,    96,   128,
     103,    89,    91,    87,    92,    93,    94,    95,   107,   111,
     109,   112,   124,   131,   129,     0,     0,   152,    65,     0,
     144,    67,     0,   173,    58,     0,    39,     0,    41,     0,
       0,    37,     0,   104,     0,   105,     0,   106,     0,     0,
       0,     0,   132,     0,   146,     0,     0,   169,   170,   163,
     164,   165,   166,   167,   168,     0,   145,   153,     0,     0,
       0,    66,    59,    60,     0,    49,    50,    51,    52,    53,
      54,    45,     0,     0,     0,     0,   121,   122,   131,   129,
     109,   108,   133,   129,     0,   138,     0,    56,     0,     0,
       0,     0,     0,   152,   162,     0,    69,    70,    68,     0,
       0,     0,    46,    44,    41,    38,    35,     0,   146,   110,
     130,   147,   148,   150,     0,     0,    71,   136,     0,     0,
       0,   155,     0,     0,     0,   158,    75,    76,   160,   157,
     154,   171,    48,     0,    47,    42,    40,     0,     0,    35,
       0,     0,     0,     0,     0,   152,   146,    56,    55,   156,
     159,   161,    56,    45,    35,    33,     0,    77,   149,   151,
      83,    80,   142,   137,   138,    57,     0,    43,    36,    34,
       0,    73,    82,    81,    79,     0,   140,    72,    78,    83,
     142,   152,   139,    84,   143,   141
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -251,  -251,   333,  -251,  -251,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,  -251,  -232,  -251,  -251,  -251,   118,   154,    70,
    -251,  -251,  -251,  -250,  -171,  -108,  -251,  -251,  -251,   165,
    -109,  -192,  -179,  -251,    57,  -251,    45,  -251,     9,  -251,
      -3,  -251,  -251,   148,   190,  -251,  -251,  -251,  -251,   268,
     -87,  -117,  -137,  -251,  -251,    67,  -251,    52,   213,  -223,
    -251,    94,  -217,  -200,   179,  -251,  -251,  -251,  -251
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   268,    31,    32,    33,   203,   158,   233,
     263,   201,    34,   249,   153,    61,    35,    36,   150,   151,
      37,   255,    62,   257,   290,   304,   301,    38,    63,    64,
     185,    66,    67,   170,   140,    68,   120,   123,   125,    72,
      69,   174,   144,   145,   276,   246,   312,   306,   148,   215,
     241,   242,   186,   187,   188,    39,    40,    41,    83
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,    65,   121,   154,   156,   217,   260,   105,   171,   171,
     227,   128,   302,    71,   243,   270,   230,   141,   226,  -134,
    -135,   113,  -117,    42,    73,    43,   190,   295,    55,   258,
     129,   209,   296,    74,   130,    97,   213,   286,    77,    94,
     114,   256,   256,    56,    57,   147,    59,    93,   152,   231,
     214,   232,   298,   294,   118,   119,    98,    95,   293,   303,
     280,   281,    75,   164,   100,   101,   102,   103,   154,    76,
      92,   243,   289,   256,   256,    44,    81,   277,   106,   172,
     172,   154,   141,   282,    45,    78,    46,   122,   124,    65,
     166,    79,   238,    65,   315,    65,   240,   134,   135,   136,
     137,   126,    47,    48,    49,   131,    99,   133,   100,   101,
     102,   103,    55,    82,    50,   100,   101,   102,   103,   250,
     138,   251,    51,    52,    53,    54,   266,    56,    57,    86,
      59,   231,   152,   232,   118,    47,    48,    49,   139,    84,
     154,    85,   100,   101,   102,   103,   154,    50,    89,    55,
     100,   101,   102,   103,    87,    51,    52,    53,    54,   102,
     103,   192,   193,    90,    56,    57,    58,    59,    88,    60,
      70,   118,   244,   245,    91,   139,   104,   177,   178,   252,
     253,    96,    55,   110,  -126,   224,   291,   292,   107,   179,
     180,   181,   182,   183,   184,   111,   108,    56,    57,    58,
      59,   109,    60,    47,    48,    49,   112,   225,    92,    47,
      48,    49,   115,   291,   116,    50,   117,   132,   310,   259,
     146,    50,   142,    51,    52,    53,    54,   143,     4,    51,
      52,    53,    54,   147,   149,   160,   155,   157,   159,   162,
     195,   196,    55,   163,   161,   165,   197,   198,   199,   167,
      55,   168,   169,   173,   175,   176,    55,    56,    57,   189,
      59,   194,   152,   202,   204,    56,    57,    58,    59,   200,
      60,    56,    57,    58,    59,   205,    60,     1,     2,   129,
     206,   207,     3,   211,   208,   212,   214,   235,     4,     5,
       6,     7,     8,     9,    10,   216,   223,   229,    11,    12,
      13,   236,   237,   248,   247,   254,   261,    92,   262,   267,
      14,    15,   264,   177,   178,   218,   219,   271,   269,    16,
     272,    17,   275,   278,    18,   179,   180,   181,   182,   183,
     184,   220,   221,   273,   279,   283,   274,   100,   101,   102,
     103,   284,   285,   287,   118,   299,   245,   300,   305,   308,
     311,    80,   265,   297,   313,   228,   234,   309,   239,   210,
     127,   307,   314,   191,   222,   288
};

static const yytype_int16 yycheck[] =
{
       3,     4,    89,   111,   113,   176,   223,     4,     4,     4,
     189,    24,    17,     4,   214,   238,    23,   104,   189,    14,
      14,     4,    23,     7,    75,     9,    25,   277,    58,   221,
      75,   168,   282,     8,    79,     4,   173,   269,    75,    40,
      23,   220,   221,    73,    74,    44,    76,    50,    78,    56,
      44,    58,   284,   276,    75,    76,    25,    60,   275,    64,
     252,   253,    41,    25,    77,    78,    79,    80,   176,    43,
      16,   271,   272,   252,   253,    59,     0,   248,    75,    75,
      75,   189,   169,   254,     7,    75,     9,    90,    91,    92,
      25,    50,   209,    96,   311,    98,   213,   100,   101,   102,
     103,    92,    11,    12,    13,    96,    75,    98,    77,    78,
      79,    80,    58,     3,    23,    77,    78,    79,    80,    56,
      24,    58,    31,    32,    33,    34,   235,    73,    74,     9,
      76,    56,    78,    58,    75,    11,    12,    13,    79,    75,
     248,    75,    77,    78,    79,    80,   254,    23,    23,    58,
      77,    78,    79,    80,    75,    31,    32,    33,    34,    79,
      80,    73,    74,    23,    73,    74,    75,    76,    75,    78,
      79,    75,    60,    61,    23,    79,    23,    53,    54,    71,
      72,    25,    58,    47,    43,   188,   273,   274,    43,    65,
      66,    67,    68,    69,    70,    65,    75,    73,    74,    75,
      76,    75,    78,    11,    12,    13,    51,    23,    16,    11,
      12,    13,    48,   300,    75,    23,    48,    75,   305,   222,
      42,    23,    75,    31,    32,    33,    34,    75,    16,    31,
      32,    33,    34,    44,    75,    48,    76,    75,    75,    40,
      29,    30,    58,    24,    75,    24,    35,    36,    37,    24,
      58,    43,    25,    25,    14,    23,    58,    73,    74,    65,
      76,    41,    78,    25,    23,    73,    74,    75,    76,    58,
      78,    73,    74,    75,    76,    75,    78,     5,     6,    75,
      73,    76,    10,    24,    75,    75,    44,    24,    16,    17,
      18,    19,    20,    21,    22,    15,    45,     7,    26,    27,
      28,    75,    23,    25,    75,    23,    75,    16,    73,    25,
      38,    39,    58,    53,    54,    55,    56,    46,    75,    47,
      45,    49,    48,    24,    52,    65,    66,    67,    68,    69,
      70,    71,    72,    63,    58,    24,    63,    77,    78,    79,
      80,    75,    24,    24,    75,    24,    61,    25,    25,    24,
      62,    18,   234,   283,   309,   190,   202,   300,   210,   169,
      92,   294,   310,   150,   185,   271
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    10,    16,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    38,    39,    47,    49,    52,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    96,    97,    98,   104,   108,   109,   112,   119,   147,
     148,   149,     7,     9,    59,     7,     9,    11,    12,    13,
      23,    31,    32,    33,    34,    58,    73,    74,    75,    76,
      78,   107,   114,   120,   121,   122,   123,   124,   127,   132,
      79,   120,   131,    75,     8,    41,    43,    75,    75,    50,
      84,     0,     3,   150,    75,    75,     9,    75,    75,    23,
      23,    23,    16,   122,    40,   122,    25,     4,    25,    75,
      77,    78,    79,    80,    23,     4,    75,    43,    75,    75,
      47,    65,    51,     4,    23,    48,    75,    48,    75,    76,
     128,   132,   122,   129,   122,   130,   120,   131,    24,    75,
      79,   120,    75,   120,   122,   122,   122,   122,    24,    79,
     126,   132,    75,    75,   134,   135,    42,    44,   140,    75,
     110,   111,    78,   106,   107,    76,   112,    75,   100,    75,
      48,    75,    40,    24,    25,    24,    25,    24,    43,    25,
     125,     4,    75,    25,   133,    14,    23,    53,    54,    65,
      66,    67,    68,    69,    70,   122,   144,   145,   146,    65,
      25,   140,    73,    74,    41,    29,    30,    35,    36,    37,
      58,   103,    25,    99,    23,    75,    73,    76,    75,   134,
     126,    24,    75,   134,    44,   141,    15,   106,    55,    56,
      71,    72,   146,    45,   122,    23,   106,   114,   111,     7,
      23,    56,    58,   101,   100,    24,    75,    23,   133,   125,
     133,   142,   143,   145,    60,    61,   137,    75,    25,   105,
      56,    58,    71,    72,    23,   113,   114,   115,   113,   122,
     144,    75,    73,   102,    58,    99,   112,    25,    95,    75,
     141,    46,    45,    63,    63,    48,   136,   106,    24,    58,
     113,   113,   106,    24,    75,    24,    95,    24,   143,   145,
     116,   132,   132,   144,   141,   105,   105,   101,    95,    24,
      25,   118,    17,    64,   117,    25,   139,   137,    24,   116,
     132,    62,   138,   118,   139,   144
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    84,    84,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    94,    95,    95,    96,    97,    98,
      97,    99,    99,   100,   100,   101,   101,   101,   102,   103,
     103,   103,   103,   103,   103,   104,   105,   105,   106,   106,
     106,   107,   107,   107,   107,   108,   109,   110,   110,   111,
     111,   112,   112,   112,   112,   113,   113,   114,   115,   116,
     117,   117,   117,   118,   118,   119,   120,   120,   120,   120,
     121,   121,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   123,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   127,   127,   127,   128,   128,
     129,   129,   130,   131,   131,   131,   131,   132,   132,   133,
     133,   134,   134,   134,   135,   135,   136,   136,   137,   137,
     138,   138,   139,   139,   140,   140,   141,   141,   142,   142,
     143,   143,   144,   144,   144,   145,   145,   145,   145,   145,
     145,   145,   145,   146,   146,   146,   146,   146,   146,   146,
     146,   147,   148,   149,   150,   150
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     0,     3,     5,     7,     5,
       8,     0,     3,     6,     3,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     8,     0,     3,     1,     2,
       2,     1,     1,     1,     1,     4,     5,     1,     3,     3,
       3,     7,    10,    10,     2,     1,     1,     8,     4,     2,
       0,     1,     1,     0,     3,     2,     1,     3,     1,     3,
       2,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     3,     4,     4,     4,     3,     5,     0,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     2,     1,     1,     3,     0,
       3,     1,     2,     3,     1,     5,     0,     2,     0,     5,
       0,     2,     0,     3,     0,     2,     0,     2,     1,     3,
       1,     3,     0,     1,     3,     3,     4,     3,     3,     4,
       3,     4,     2,     1,     1,     1,     1,     1,     1,     1,
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
#line 246 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1903 "yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 277 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 283 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1920 "yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 288 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1928 "yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 294 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1936 "yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 300 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1944 "yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 306 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1952 "yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 312 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 319 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 325 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1980 "yacc_sql.cpp"
    break;

  case 33: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE ID attr_name_list RBRACE  */
#line 334 "yacc_sql.y"
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
#line 2003 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_name_list RBRACE  */
#line 353 "yacc_sql.y"
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
#line 2026 "yacc_sql.cpp"
    break;

  case 35: /* attr_name_list: %empty  */
#line 375 "yacc_sql.y"
    {
      (yyval.attr_names) = nullptr;
    }
#line 2034 "yacc_sql.cpp"
    break;

  case 36: /* attr_name_list: COMMA ID attr_name_list  */
#line 379 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_names) != nullptr) {
        (yyval.attr_names) = (yyvsp[0].attr_names);
      } else {
        (yyval.attr_names) = new std::vector<std::string>;
      }
      (yyval.attr_names)->emplace_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 2048 "yacc_sql.cpp"
    break;

  case 37: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 392 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2060 "yacc_sql.cpp"
    break;

  case 38: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 402 "yacc_sql.y"
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
#line 2080 "yacc_sql.cpp"
    break;

  case 39: /* create_table_select_stmt: CREATE TABLE ID AS select_stmt  */
#line 420 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->selection.is_create_table_select_stmt = true;
      (yyval.sql_node)->selection.create_table_select_table_name = (yyvsp[-2].string);
    }
#line 2090 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE select_stmt  */
#line 427 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->selection.is_create_table_select_stmt = true;
      (yyval.sql_node)->selection.create_table_select_table_name = (yyvsp[-5].string);

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);
      if (src_attrs != nullptr) {
        (yyval.sql_node)->selection.table_select_attr_infos.swap(*src_attrs);
      }
      (yyval.sql_node)->selection.table_select_attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse((yyval.sql_node)->selection.table_select_attr_infos.begin(), (yyval.sql_node)->selection.table_select_attr_infos.end());

      delete (yyvsp[-3].attr_info);
    }
#line 2109 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 445 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2117 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 449 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2131 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 462 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2144 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type nullable  */
#line 471 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2157 "yacc_sql.cpp"
    break;

  case 45: /* nullable: %empty  */
#line 482 "yacc_sql.y"
    { (yyval.bools) = true; }
#line 2163 "yacc_sql.cpp"
    break;

  case 46: /* nullable: NULL_T  */
#line 483 "yacc_sql.y"
             { (yyval.bools) = true; }
#line 2169 "yacc_sql.cpp"
    break;

  case 47: /* nullable: NOT NULL_T  */
#line 484 "yacc_sql.y"
                 { (yyval.bools) = false; }
#line 2175 "yacc_sql.cpp"
    break;

  case 48: /* number: NUMBER  */
#line 488 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2181 "yacc_sql.cpp"
    break;

  case 49: /* type: INT_T  */
#line 491 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2187 "yacc_sql.cpp"
    break;

  case 50: /* type: DATE_T  */
#line 492 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2193 "yacc_sql.cpp"
    break;

  case 51: /* type: STRING_T  */
#line 493 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2199 "yacc_sql.cpp"
    break;

  case 52: /* type: FLOAT_T  */
#line 494 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2205 "yacc_sql.cpp"
    break;

  case 53: /* type: TEXT_T  */
#line 495 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2211 "yacc_sql.cpp"
    break;

  case 54: /* type: NULL_T  */
#line 496 "yacc_sql.y"
               { (yyval.number)=NULLS; }
#line 2217 "yacc_sql.cpp"
    break;

  case 55: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 500 "yacc_sql.y"
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
#line 2233 "yacc_sql.cpp"
    break;

  case 56: /* value_list: %empty  */
#line 515 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 57: /* value_list: COMMA value value_list  */
#line 518 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2255 "yacc_sql.cpp"
    break;

  case 58: /* value: unsigned_value  */
#line 529 "yacc_sql.y"
                   {
      (yyval.value) = (yyvsp[0].value);
      (yyloc) = (yylsp[0]);
    }
#line 2264 "yacc_sql.cpp"
    break;

  case 59: /* value: '-' NUMBER  */
#line 533 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2273 "yacc_sql.cpp"
    break;

  case 60: /* value: '-' FLOAT  */
#line 537 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2282 "yacc_sql.cpp"
    break;

  case 61: /* unsigned_value: NUMBER  */
#line 544 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2291 "yacc_sql.cpp"
    break;

  case 62: /* unsigned_value: FLOAT  */
#line 548 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2300 "yacc_sql.cpp"
    break;

  case 63: /* unsigned_value: SSS  */
#line 552 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2310 "yacc_sql.cpp"
    break;

  case 64: /* unsigned_value: NULL_T  */
#line 557 "yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_type(NULLS);
      (yyloc) = (yylsp[0]);
    }
#line 2320 "yacc_sql.cpp"
    break;

  case 65: /* delete_stmt: DELETE FROM ID where  */
#line 566 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2334 "yacc_sql.cpp"
    break;

  case 66: /* update_stmt: UPDATE ID SET update_list where  */
#line 578 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_units.swap(*(yyvsp[-1].update_unit_list));
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
    }
#line 2349 "yacc_sql.cpp"
    break;

  case 67: /* update_list: update_unit  */
#line 592 "yacc_sql.y"
    {
      (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2358 "yacc_sql.cpp"
    break;

  case 68: /* update_list: update_list COMMA update_unit  */
#line 597 "yacc_sql.y"
    {
      if ((yyvsp[-2].update_unit_list) == nullptr) {
        (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      } else {
        (yyval.update_unit_list) = (yyvsp[-2].update_unit_list);
      }

      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2372 "yacc_sql.cpp"
    break;

  case 69: /* update_unit: ID EQ value  */
#line 610 "yacc_sql.y"
    {
      (yyval.update_unit) = new UpdateUnit((yyvsp[-2].string), new ValueExpr(*(yyvsp[0].value)));
    }
#line 2380 "yacc_sql.cpp"
    break;

  case 70: /* update_unit: ID EQ sub_query_expr  */
#line 614 "yacc_sql.y"
    {
      (yyval.update_unit) = new UpdateUnit((yyvsp[-2].string), (yyvsp[0].expression));
    }
#line 2388 "yacc_sql.cpp"
    break;

  case 71: /* select_stmt: SELECT select_attr FROM single_table rel_list select_where group_by  */
#line 621 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].expression_list) != nullptr) {
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }
      if ((yyvsp[-2].relation_list) != nullptr) {
        (yyval.sql_node)->selection.relations.swap(*(yyvsp[-2].relation_list));
        delete (yyvsp[-2].relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back(std::move(*(yyvsp[-3].single_table)));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      free((yyvsp[-3].single_table));

      if((yyvsp[0].group_by) != nullptr) {
        (yyval.sql_node)->selection.group_by = *(yyvsp[0].group_by);
        delete (yyvsp[0].group_by);
      }

    }
#line 2418 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT select_attr FROM general_rel INNER JOIN ID join_condition select_where group_by  */
#line 647 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-8].expression_list) != nullptr) {
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }

      (yyval.sql_node)->selection.join_relation = new JoinSqlNode(JT_INNER, (yyvsp[-6].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-3].string)), std::move(*(yyvsp[-2].condition_list)));
      delete (yyvsp[-2].condition_list);

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }
      free((yyvsp[-3].string));

      if((yyvsp[0].group_by) != nullptr) {
        (yyval.sql_node)->selection.group_by=*(yyvsp[0].group_by);
        delete (yyvsp[0].group_by);
      }

    }
#line 2445 "yacc_sql.cpp"
    break;

  case 73: /* select_stmt: SELECT select_attr FROM single_table rel_list select_where ORDER BY order_item order_item_list  */
#line 670 "yacc_sql.y"
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
#line 2477 "yacc_sql.cpp"
    break;

  case 74: /* select_stmt: SELECT expression_list  */
#line 698 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2490 "yacc_sql.cpp"
    break;

  case 75: /* sub_query_two_expr: sub_query_expr  */
#line 710 "yacc_sql.y"
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2498 "yacc_sql.cpp"
    break;

  case 76: /* sub_query_two_expr: sub_query_list_expr  */
#line 714 "yacc_sql.y"
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2506 "yacc_sql.cpp"
    break;

  case 77: /* sub_query_expr: LBRACE SELECT select_attr FROM single_table rel_list select_where RBRACE  */
#line 720 "yacc_sql.y"
    {
      SelectSqlNode* select_sql_node = new SelectSqlNode();
      if ((yyvsp[-5].expression_list) != nullptr) {
        select_sql_node->select_expressions.swap(*(yyvsp[-5].expression_list));
        delete (yyvsp[-5].expression_list);
      }
      if ((yyvsp[-2].relation_list) != nullptr) {
        select_sql_node->relations.swap(*(yyvsp[-2].relation_list));
        delete (yyvsp[-2].relation_list);
      }
      select_sql_node->relations.push_back(std::move(*(yyvsp[-3].single_table)));
      std::reverse(select_sql_node->relations.begin(), select_sql_node->relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        select_sql_node->have_sub_query_condition_expr = true;
        select_sql_node->conditions.swap(*(yyvsp[-1].condition_list));
        delete (yyvsp[-1].condition_list);
      }

      (yyval.expression) = new SubQueryExpression(select_sql_node);
      free((yyvsp[-3].single_table));
    }
#line 2533 "yacc_sql.cpp"
    break;

  case 78: /* sub_query_list_expr: LBRACE value value_list RBRACE  */
#line 745 "yacc_sql.y"
    {
      std::vector<Value> values;
      if ((yyvsp[-1].value_list) != nullptr) {
        values.swap(*(yyvsp[-1].value_list));
      }
      values.emplace_back(*(yyvsp[-2].value));
      std::reverse(values.begin(), values.end());

      (yyval.expression) = new ListExpression(values);
      delete (yyvsp[-2].value);
    }
#line 2549 "yacc_sql.cpp"
    break;

  case 79: /* order_item: rel_attr order  */
#line 759 "yacc_sql.y"
                       {
        (yyval.order_item) = new OrderBy;
        (yyval.order_item)->order_by_attribute = *(yyvsp[-1].rel_attr);
        (yyval.order_item)->order = (yyvsp[0].bools);
        delete (yyvsp[-1].rel_attr);
	}
#line 2560 "yacc_sql.cpp"
    break;

  case 80: /* order: %empty  */
#line 768 "yacc_sql.y"
                    {
		(yyval.bools) = 0;
	}
#line 2568 "yacc_sql.cpp"
    break;

  case 81: /* order: ASC  */
#line 771 "yacc_sql.y"
              {
		(yyval.bools) = 0;
	}
#line 2576 "yacc_sql.cpp"
    break;

  case 82: /* order: DESC  */
#line 774 "yacc_sql.y"
               {
		(yyval.bools) = 1;
	}
#line 2584 "yacc_sql.cpp"
    break;

  case 83: /* order_item_list: %empty  */
#line 781 "yacc_sql.y"
        {
	    (yyval.order_item_list) = nullptr;
	}
#line 2592 "yacc_sql.cpp"
    break;

  case 84: /* order_item_list: COMMA order_item order_item_list  */
#line 785 "yacc_sql.y"
        {
        if((yyvsp[0].order_item_list) != nullptr) {
            (yyval.order_item_list) = (yyvsp[0].order_item_list);
        } else {
            (yyval.order_item_list) = new std::vector<OrderBy>;
        }
        (yyval.order_item_list)->emplace_back(*(yyvsp[-1].order_item));
        delete (yyvsp[-1].order_item);
	}
#line 2606 "yacc_sql.cpp"
    break;

  case 85: /* calc_stmt: CALC expression_list  */
#line 798 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2617 "yacc_sql.cpp"
    break;

  case 86: /* expression_list: expression  */
#line 808 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2626 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression COMMA expression_list  */
#line 813 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2639 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression_alias  */
#line 821 "yacc_sql.y"
                       {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2648 "yacc_sql.cpp"
    break;

  case 89: /* expression_list: expression_alias COMMA expression_list  */
#line 826 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 90: /* expression_alias: expression ID  */
#line 838 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 91: /* expression_alias: expression AS ID  */
#line 843 "yacc_sql.y"
    {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '+' expression  */
#line 850 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2687 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '-' expression  */
#line 853 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2695 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '*' expression  */
#line 856 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2703 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '/' expression  */
#line 859 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2711 "yacc_sql.cpp"
    break;

  case 96: /* expression: LBRACE expression RBRACE  */
#line 862 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2720 "yacc_sql.cpp"
    break;

  case 97: /* expression: '-' expression  */
#line 866 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2728 "yacc_sql.cpp"
    break;

  case 98: /* expression: unsigned_value  */
#line 869 "yacc_sql.y"
                     {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2738 "yacc_sql.cpp"
    break;

  case 99: /* expression: rel_attr  */
#line 874 "yacc_sql.y"
               {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      (yyval.expression)->set_name((yyvsp[0].rel_attr)->name());
    }
#line 2747 "yacc_sql.cpp"
    break;

  case 100: /* expression: func_expr  */
#line 878 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 101: /* expression: sub_query_expr  */
#line 882 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2765 "yacc_sql.cpp"
    break;

  case 102: /* expression: agg_expr  */
#line 887 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2774 "yacc_sql.cpp"
    break;

  case 103: /* expression: ID DOT '*'  */
#line 892 "yacc_sql.y"
    {
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = (yyvsp[-2].string);
      attr->attribute_name = "*";
      (yyval.expression) = new StarExprSqlNode(attr);
      free((yyvsp[-2].string));
    }
#line 2786 "yacc_sql.cpp"
    break;

  case 104: /* func_expr: LENGTH LBRACE length_args RBRACE  */
#line 902 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, *(yyvsp[-1].func_args));
    }
#line 2794 "yacc_sql.cpp"
    break;

  case 105: /* func_expr: ROUND LBRACE round_args RBRACE  */
#line 905 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, *(yyvsp[-1].func_args));
    }
#line 2802 "yacc_sql.cpp"
    break;

  case 106: /* func_expr: DATE_FORMAT LBRACE date_format_args RBRACE  */
#line 908 "yacc_sql.y"
                                                 {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, *(yyvsp[-1].func_args));
    }
#line 2810 "yacc_sql.cpp"
    break;

  case 107: /* agg_expr: agg_func LBRACE RBRACE  */
#line 918 "yacc_sql.y"
    {
      if((yyvsp[-2].agg_func) == AggFuncType::COUNT_FUNC) {
        (yyval.expression) = new AggExpr(AggType::COUNT_STAR);
      } else if((yyvsp[-2].agg_func) == AggFuncType::SUM_FUNC) {
        (yyval.expression) = new AggExpr(AggType::SUM_AGG);
      } else if((yyvsp[-2].agg_func) == AggFuncType::AVG_FUNC) {
        (yyval.expression) = new AggExpr(AggType::AVG_AGG);
      } else if((yyvsp[-2].agg_func) == AggFuncType::MAX_FUNC) {
        (yyval.expression) = new AggExpr(AggType::MAX_AGG);
      } else {
        (yyval.expression) = new AggExpr(AggType::MIN_AGG);
      }
      // bad agg
      // $$->rel_attr_node = nullptr
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 108: /* agg_expr: agg_func LBRACE agg_field agg_field_list RBRACE  */
#line 934 "yacc_sql.y"
    {
      if((yyvsp[-4].agg_func) == AggFuncType::COUNT_FUNC) {
        if((yyvsp[-1].rel_attr_list) == nullptr && strcmp((yyvsp[-2].rel_attr)->attribute_name.c_str(), "*") == 0) {
          (yyval.expression) = new AggExpr(AggType::COUNT_STAR);
        } else {
          (yyval.expression) = new AggExpr(AggType::COUNT_AGG);
        }
      } else if((yyvsp[-4].agg_func) == AggFuncType::SUM_FUNC) {
        (yyval.expression) = new AggExpr(AggType::SUM_AGG);
      } else if((yyvsp[-4].agg_func) == AggFuncType::AVG_FUNC) {
        (yyval.expression) = new AggExpr(AggType::AVG_AGG);
      } else if((yyvsp[-4].agg_func) == AggFuncType::MAX_FUNC) {
        (yyval.expression) = new AggExpr(AggType::MAX_AGG);
      } else {
        (yyval.expression) = new AggExpr(AggType::MIN_AGG);
      }


      AggExpr* tmp_expr = static_cast<AggExpr*>((yyval.expression));

      if((yyvsp[-1].rel_attr_list) == nullptr) {

        tmp_expr->set_rel_attr_node((yyvsp[-2].rel_attr));

        if((yyvsp[-2].rel_attr)->attribute_name == "*") {
          if(tmp_expr->agg_type() != AggType::COUNT_STAR) {
            delete (yyvsp[-2].rel_attr);
            tmp_expr->set_rel_attr_node(nullptr);
          }
        }

      } else {
        delete (yyvsp[-1].rel_attr_list);
        delete (yyvsp[-2].rel_attr);
      }
      // bad agg
      // $$->rel_attr_node = nullptr
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 109: /* agg_field_list: %empty  */
#line 976 "yacc_sql.y"
  {
    (yyval.rel_attr_list)=nullptr;
  }
#line 2881 "yacc_sql.cpp"
    break;

  case 110: /* agg_field_list: COMMA agg_field agg_field_list  */
#line 980 "yacc_sql.y"
  {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    delete (yyvsp[-1].rel_attr);
  }
#line 2895 "yacc_sql.cpp"
    break;

  case 111: /* agg_field: '*'  */
#line 995 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = "*";
  }
#line 2904 "yacc_sql.cpp"
    break;

  case 112: /* agg_field: rel_attr  */
#line 1000 "yacc_sql.y"
  {
    (yyval.rel_attr)=(yyvsp[0].rel_attr);
  }
#line 2912 "yacc_sql.cpp"
    break;

  case 113: /* agg_func: MAX  */
#line 1008 "yacc_sql.y"
    {
       (yyval.agg_func)=MAX_FUNC;
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 114: /* agg_func: MIN  */
#line 1012 "yacc_sql.y"
    {
       (yyval.agg_func)=MIN_FUNC;
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 115: /* agg_func: AVG  */
#line 1016 "yacc_sql.y"
    {
       (yyval.agg_func)=AVG_FUNC;
    }
#line 2936 "yacc_sql.cpp"
    break;

  case 116: /* agg_func: COUNT  */
#line 1020 "yacc_sql.y"
    {
       (yyval.agg_func)=COUNT_FUNC;
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 117: /* agg_func: ID  */
#line 1024 "yacc_sql.y"
    {
       std::string func_name((yyvsp[0].string));
       if (common::str_to_lower(func_name) == "sum") {
        (yyval.agg_func)=SUM_FUNC;
       } else {
        (yyval.agg_func)=INVALID_AGG_FUNC;
       }
       free((yyvsp[0].string));
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 118: /* length_args: SSS  */
#line 1037 "yacc_sql.y"
        {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *value_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      free(tmp);
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 119: /* length_args: rel_attr  */
#line 1045 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      RelAttrExprSqlNode *attr_expr = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      attr_expr->set_name((yyvsp[0].rel_attr)->name());
      std::unique_ptr<Expression> target(attr_expr);
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2983 "yacc_sql.cpp"
    break;

  case 120: /* round_args: expression  */
#line 1055 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[0].expression));
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2993 "yacc_sql.cpp"
    break;

  case 121: /* round_args: expression COMMA NUMBER  */
#line 1060 "yacc_sql.y"
                              {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      ValueExpr *value_expr = new ValueExpr(Value((int)(yyvsp[0].number)));
      std::unique_ptr<Expression> precise(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(precise));
    }
#line 3006 "yacc_sql.cpp"
    break;

  case 122: /* date_format_args: expression COMMA SSS  */
#line 1071 "yacc_sql.y"
                         {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *format_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      std::unique_ptr<Expression> format(format_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(format));
    }
#line 3020 "yacc_sql.cpp"
    break;

  case 123: /* select_attr: '*'  */
#line 1084 "yacc_sql.y"
        {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      (yyval.expression_list)->emplace_back(new StarExprSqlNode(attr));
    }
#line 3032 "yacc_sql.cpp"
    break;

  case 124: /* select_attr: '*' AS ID  */
#line 1091 "yacc_sql.y"
                {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      StarExprSqlNode *star = new StarExprSqlNode(attr);
      star->set_name((yyvsp[0].string));
      (yyval.expression_list)->emplace_back(star);
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 125: /* select_attr: '*' ID  */
#line 1100 "yacc_sql.y"
             {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      StarExprSqlNode *star = new StarExprSqlNode(attr);
      star->set_name((yyvsp[0].string));
      (yyval.expression_list)->emplace_back(star);
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 126: /* select_attr: expression_list  */
#line 1109 "yacc_sql.y"
                      {
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3069 "yacc_sql.cpp"
    break;

  case 127: /* rel_attr: ID  */
#line 1116 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3079 "yacc_sql.cpp"
    break;

  case 128: /* rel_attr: ID DOT ID  */
#line 1121 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3091 "yacc_sql.cpp"
    break;

  case 129: /* rel_list: %empty  */
#line 1132 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3099 "yacc_sql.cpp"
    break;

  case 130: /* rel_list: COMMA single_table rel_list  */
#line 1135 "yacc_sql.y"
                                  {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->push_back(std::move(*(yyvsp[-1].single_table)));
    }
#line 3113 "yacc_sql.cpp"
    break;

  case 131: /* single_table: ID  */
#line 1148 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 3122 "yacc_sql.cpp"
    break;

  case 132: /* single_table: ID ID  */
#line 1153 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-1].string), (yyvsp[0].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3132 "yacc_sql.cpp"
    break;

  case 133: /* single_table: ID AS ID  */
#line 1159 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-2].string), (yyvsp[0].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3142 "yacc_sql.cpp"
    break;

  case 134: /* general_rel: ID  */
#line 1168 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode((yyvsp[0].string));
       free((yyvsp[0].string));
    }
#line 3151 "yacc_sql.cpp"
    break;

  case 135: /* general_rel: general_rel INNER JOIN ID join_condition  */
#line 1173 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode(
        new JoinSqlNode(JT_INNER, (yyvsp[-4].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-1].string)), std::move(*(yyvsp[0].condition_list)))
       );
       free((yyvsp[-1].string));
    }
#line 3162 "yacc_sql.cpp"
    break;

  case 136: /* join_condition: %empty  */
#line 1182 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3170 "yacc_sql.cpp"
    break;

  case 137: /* join_condition: ON condition_list  */
#line 1185 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3178 "yacc_sql.cpp"
    break;

  case 138: /* group_by: %empty  */
#line 1193 "yacc_sql.y"
  {
    (yyval.group_by)=nullptr;
  }
#line 3186 "yacc_sql.cpp"
    break;

  case 139: /* group_by: GROUP BY rel_attr rel_attr_list having  */
#line 1198 "yacc_sql.y"
  {
    (yyval.group_by) = new GroupBy;
    if((yyvsp[-1].rel_attr_list) != nullptr) {
      (yyval.group_by)->attrs.swap(*(yyvsp[-1].rel_attr_list));
      delete (yyvsp[-1].rel_attr_list);
    }
    (yyval.group_by)->attrs.emplace_back(*(yyvsp[-2].rel_attr));
    std::reverse((yyval.group_by)->attrs.begin(), (yyval.group_by)->attrs.end());
    delete (yyvsp[-2].rel_attr);
    if((yyvsp[0].having) != nullptr) {
      (yyval.group_by)->having = *(yyvsp[0].having);
      delete (yyvsp[0].having);
    }
  }
#line 3205 "yacc_sql.cpp"
    break;

  case 140: /* having: %empty  */
#line 1215 "yacc_sql.y"
  {
    (yyval.having)=nullptr;
  }
#line 3213 "yacc_sql.cpp"
    break;

  case 141: /* having: HAVING condition_list  */
#line 1219 "yacc_sql.y"
  {
    (yyval.having) = new Having;
    if((yyvsp[0].condition_list) != nullptr) {
      (yyval.having)->conds.swap(*(yyvsp[0].condition_list));
      delete (yyvsp[0].condition_list);
    } else {
      // if cond is empty, which means we have select .... from ... group by xxx having
      // should return BAG_AGG on resolve_stage, but we just suppress this
      //
    }
    std::reverse((yyval.having)->conds.begin(), (yyval.having)->conds.end());
  }
#line 3230 "yacc_sql.cpp"
    break;

  case 142: /* rel_attr_list: %empty  */
#line 1236 "yacc_sql.y"
  {
    (yyval.rel_attr_list)=nullptr;
  }
#line 3238 "yacc_sql.cpp"
    break;

  case 143: /* rel_attr_list: COMMA rel_attr rel_attr_list  */
#line 1240 "yacc_sql.y"
  {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(std::move(*(yyvsp[-1].rel_attr)));
  }
#line 3251 "yacc_sql.cpp"
    break;

  case 144: /* where: %empty  */
#line 1253 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3259 "yacc_sql.cpp"
    break;

  case 145: /* where: WHERE condition_list  */
#line 1256 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3267 "yacc_sql.cpp"
    break;

  case 146: /* select_where: %empty  */
#line 1262 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3275 "yacc_sql.cpp"
    break;

  case 147: /* select_where: WHERE condition_or  */
#line 1265 "yacc_sql.y"
                         {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3284 "yacc_sql.cpp"
    break;

  case 148: /* condition_or: condition_and  */
#line 1271 "yacc_sql.y"
                  {
     (yyval.condition) = (yyvsp[0].condition);
    }
#line 3292 "yacc_sql.cpp"
    break;

  case 149: /* condition_or: condition_or OR condition_and  */
#line 1274 "yacc_sql.y"
                                    {
        std::unique_ptr<Expression> left((yyvsp[-2].condition));
        std::unique_ptr<Expression> right((yyvsp[0].condition));
        (yyval.condition) = new ComparisonExpr(OR_OP, std::move(left), std::move(right));
    }
#line 3302 "yacc_sql.cpp"
    break;

  case 150: /* condition_and: condition  */
#line 1281 "yacc_sql.y"
               {
        (yyval.condition) = (yyvsp[0].condition);
     }
#line 3310 "yacc_sql.cpp"
    break;

  case 151: /* condition_and: condition_and AND condition  */
#line 1284 "yacc_sql.y"
                                   {
        std::unique_ptr<Expression> left((yyvsp[-2].condition));
        std::unique_ptr<Expression> right((yyvsp[0].condition));
        (yyval.condition) = new ComparisonExpr(AND_OP, std::move(left), std::move(right));
     }
#line 3320 "yacc_sql.cpp"
    break;

  case 152: /* condition_list: %empty  */
#line 1293 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3328 "yacc_sql.cpp"
    break;

  case 153: /* condition_list: condition  */
#line 1296 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3337 "yacc_sql.cpp"
    break;

  case 154: /* condition_list: condition AND condition_list  */
#line 1300 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3346 "yacc_sql.cpp"
    break;

  case 155: /* condition: expression IS NULL_T  */
#line 1307 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value value = Value();
      value.set_type(NULLS);
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NULL, std::move(left), std::move(right));
    }
#line 3359 "yacc_sql.cpp"
    break;

  case 156: /* condition: expression IS NOT NULL_T  */
#line 1316 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      Value value = Value();
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NOT_NULL, std::move(left), std::move(right));
    }
#line 3371 "yacc_sql.cpp"
    break;

  case 157: /* condition: expression comp_op expression  */
#line 1324 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3381 "yacc_sql.cpp"
    break;

  case 158: /* condition: expression IN sub_query_two_expr  */
#line 1330 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_IN_OP, std::move(left), std::move(right));
    }
#line 3391 "yacc_sql.cpp"
    break;

  case 159: /* condition: expression NOT IN sub_query_two_expr  */
#line 1336 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_NOT_IN, std::move(left), std::move(right));
    }
#line 3401 "yacc_sql.cpp"
    break;

  case 160: /* condition: expression EXISTS sub_query_two_expr  */
#line 1342 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_EXISTS_OP, std::move(left), std::move(right));
    }
#line 3411 "yacc_sql.cpp"
    break;

  case 161: /* condition: expression NOT EXISTS sub_query_two_expr  */
#line 1348 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_NOT_EXISTS, std::move(left), std::move(right));
    }
#line 3421 "yacc_sql.cpp"
    break;

  case 162: /* condition: comp_op expression  */
#line 1354 "yacc_sql.y"
    {
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), nullptr, std::move(right));
    }
#line 3430 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: EQ  */
#line 1361 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3436 "yacc_sql.cpp"
    break;

  case 164: /* comp_op: LT  */
#line 1362 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3442 "yacc_sql.cpp"
    break;

  case 165: /* comp_op: GT  */
#line 1363 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3448 "yacc_sql.cpp"
    break;

  case 166: /* comp_op: LE  */
#line 1364 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3454 "yacc_sql.cpp"
    break;

  case 167: /* comp_op: GE  */
#line 1365 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3460 "yacc_sql.cpp"
    break;

  case 168: /* comp_op: NE  */
#line 1366 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3466 "yacc_sql.cpp"
    break;

  case 169: /* comp_op: LIKE  */
#line 1367 "yacc_sql.y"
           { (yyval.comp) = LIKES; }
#line 3472 "yacc_sql.cpp"
    break;

  case 170: /* comp_op: NOT_LIKE  */
#line 1368 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKES; }
#line 3478 "yacc_sql.cpp"
    break;

  case 171: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1373 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3492 "yacc_sql.cpp"
    break;

  case 172: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1386 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3501 "yacc_sql.cpp"
    break;

  case 173: /* set_variable_stmt: SET ID EQ value  */
#line 1394 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3513 "yacc_sql.cpp"
    break;


#line 3517 "yacc_sql.cpp"

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

#line 1406 "yacc_sql.y"

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
