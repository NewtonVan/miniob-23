/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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


#line 114 "yacc_sql.cpp"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    AS = 259,
    CREATE = 260,
    DROP = 261,
    TABLE = 262,
    TABLES = 263,
    INDEX = 264,
    CALC = 265,
    LENGTH = 266,
    ROUND = 267,
    DATE_FORMAT = 268,
    INNER = 269,
    JOIN = 270,
    SELECT = 271,
    DESC = 272,
    SHOW = 273,
    SYNC = 274,
    INSERT = 275,
    DELETE = 276,
    UPDATE = 277,
    LBRACE = 278,
    RBRACE = 279,
    COMMA = 280,
    TRX_BEGIN = 281,
    TRX_COMMIT = 282,
    TRX_ROLLBACK = 283,
    INT_T = 284,
    DATE_T = 285,
    MIN = 286,
    MAX = 287,
    AVG = 288,
    COUNT = 289,
    SUM = 290,
    STRING_T = 291,
    FLOAT_T = 292,
    TEXT_T = 293,
    HELP = 294,
    EXIT = 295,
    DOT = 296,
    INTO = 297,
    VALUES = 298,
    FROM = 299,
    WHERE = 300,
    AND = 301,
    OR = 302,
    SET = 303,
    ON = 304,
    LOAD = 305,
    DATA = 306,
    INFILE = 307,
    EXPLAIN = 308,
    LIKE = 309,
    NOT_LIKE = 310,
    IS = 311,
    NOT = 312,
    NULLABLE = 313,
    NULL_T = 314,
    UNIQUE = 315,
    ORDER = 316,
    GROUP = 317,
    HAVING = 318,
    BY = 319,
    ASC = 320,
    EQ = 321,
    LT = 322,
    GT = 323,
    LE = 324,
    GE = 325,
    NE = 326,
    IN = 327,
    EXISTS = 328,
    NUMBER = 329,
    FLOAT = 330,
    ID = 331,
    SSS = 332,
    UMINUS = 333
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 130 "yacc_sql.y"

  ParsedSqlNode *                             sql_node;
  ComparisonExpr *                            condition;
  Value *                                     value;
  enum CompOp                                 comp;
  RelAttrSqlNode *                            rel_attr;
  std::vector<std::string> *                  attr_names;
  OrderBy *                                   order_item;
  std::vector<OrderBy> *                      order_item_list;
  std::vector<AttrInfoSqlNode> *              attr_infos;
  AttrInfoSqlNode *                           attr_info;
  Expression *                                expression;
  std::vector<Expression *> *                 expression_list;
  std::vector<Value> *                        value_list;
  std::vector<ComparisonExpr *> *             condition_list;
  std::vector<RelAttrSqlNode> *               rel_attr_list;
  RelationSqlNode *                           single_table;
  std::vector<RelationSqlNode> *              relation_list;
  JoinSqlNode *                               join_relation;
  GeneralRelationSqlNode *                    general_relation_sql_node;
  char *                                      string;
  int                                         number;
  float                                       floats;
  bool                                        bools;
  std::vector<std::unique_ptr<Expression>> *  func_args;
  std::vector<std::string> *        field_list;
  AggField*                         field;
  enum AggFuncType                  agg_func;
  std::vector<AggregationFuncSqlNode> * agg_func_call_list;
  UpdateUnit *                                update_unit;
  std::vector<UpdateUnit> *                   update_unit_list;
  GroupBy*                                    group_by;
  Having*                                      having;

#line 280 "yacc_sql.cpp"

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



int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);

#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  80
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   355

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  171
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  310

#define YYUNDEFTOK  2
#define YYMAXUTOK   333


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    80,    78,     2,    79,     2,    81,     2,     2,
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
      75,    76,    77,    82
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   244,   244,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   275,   281,   286,   292,   298,   304,   310,
     317,   323,   331,   350,   373,   376,   389,   399,   418,   421,
     434,   443,   455,   456,   457,   461,   464,   465,   466,   467,
     468,   469,   472,   488,   491,   502,   506,   510,   517,   521,
     525,   530,   538,   550,   564,   569,   582,   589,   615,   638,
     666,   678,   682,   688,   713,   728,   737,   740,   743,   750,
     753,   766,   776,   781,   792,   795,   798,   801,   804,   808,
     811,   816,   820,   824,   828,   832,   836,   840,   844,   848,
     853,   858,   866,   869,   872,   881,   897,   940,   943,   958,
     963,   971,   975,   979,   983,   987,   995,  1003,  1013,  1018,
    1029,  1042,  1049,  1056,  1061,  1072,  1075,  1087,  1092,  1098,
    1107,  1112,  1122,  1125,  1133,  1137,  1155,  1158,  1176,  1179,
    1193,  1196,  1202,  1205,  1211,  1214,  1221,  1224,  1233,  1236,
    1240,  1246,  1255,  1263,  1269,  1275,  1281,  1287,  1293,  1301,
    1302,  1303,  1304,  1305,  1306,  1307,  1308,  1312,  1325,  1333,
    1343,  1344
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "AS", "CREATE", "DROP",
  "TABLE", "TABLES", "INDEX", "CALC", "LENGTH", "ROUND", "DATE_FORMAT",
  "INNER", "JOIN", "SELECT", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "DATE_T", "MIN", "MAX", "AVG", "COUNT", "SUM",
  "STRING_T", "FLOAT_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "OR", "SET", "ON", "LOAD", "DATA", "INFILE",
  "EXPLAIN", "LIKE", "NOT_LIKE", "IS", "NOT", "NULLABLE", "NULL_T",
  "UNIQUE", "ORDER", "GROUP", "HAVING", "BY", "ASC", "EQ", "LT", "GT",
  "LE", "GE", "NE", "IN", "EXISTS", "NUMBER", "FLOAT", "ID", "SSS", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "attr_name_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list", "value",
  "unsigned_value", "delete_stmt", "update_stmt", "update_list",
  "update_unit", "select_stmt", "sub_query_two_expr", "sub_query_expr",
  "sub_query_list_expr", "order_item", "order", "order_item_list",
  "calc_stmt", "expression_list", "expression", "func_expr", "agg_expr",
  "agg_field_list", "agg_field", "agg_func", "length_args", "round_args",
  "date_format_args", "select_attr", "rel_attr", "rel_list",
  "single_table", "general_rel", "join_condition", "group_by", "having",
  "rel_attr_list", "where", "select_where", "condition_or",
  "condition_and", "condition_list", "condition", "comp_op",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,    43,    45,
      42,    47,   333
};
# endif

#define YYPACT_NINF (-250)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-132)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     269,    17,    60,   194,    88,   -51,    20,  -250,    14,    -2,
     -27,  -250,  -250,  -250,  -250,  -250,   -12,    21,   269,    83,
     101,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,    41,    53,   129,    73,    84,   143,   154,   156,   188,
    -250,  -250,  -250,  -250,  -250,  -250,  -250,  -250,   139,  -250,
     194,  -250,   177,  -250,    34,     2,     5,   168,     8,  -250,
     148,   153,  -250,  -250,   126,   127,   160,   146,   157,  -250,
    -250,  -250,  -250,   190,   165,   142,  -250,   175,   -41,   194,
     194,    88,    27,   155,  -250,   158,   194,   194,   194,   194,
     194,   159,  -250,   161,  -250,    65,   162,  -250,   163,   187,
     191,   164,    69,   166,   169,   170,   183,   172,  -250,   209,
    -250,    46,   217,    77,   218,  -250,   200,  -250,  -250,  -250,
    -250,    11,    11,  -250,  -250,  -250,  -250,  -250,  -250,   224,
    -250,  -250,     4,   225,   237,   229,   119,  -250,   189,    -8,
    -250,    35,  -250,  -250,   212,     3,   231,   234,   182,  -250,
    -250,   185,  -250,   184,  -250,   196,   -33,   236,   201,  -250,
     196,   221,   261,    69,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,   257,  -250,   232,   194,    69,   164,  -250,  -250,
    -250,   273,  -250,  -250,  -250,  -250,  -250,  -250,    -4,   169,
     258,   205,   260,  -250,  -250,     9,   225,   224,  -250,  -250,
     225,   119,   110,   208,   267,    59,   103,   270,   270,   194,
     119,    56,  -250,  -250,   222,   220,   240,  -250,  -250,   231,
    -250,   275,   226,   221,  -250,  -250,   254,   259,  -250,   239,
     242,  -250,   255,    69,   283,   251,  -250,   270,   270,    -9,
    -250,  -250,  -250,  -250,    56,  -250,  -250,  -250,   291,  -250,
    -250,   244,   292,   275,   294,   119,   119,   245,   245,   119,
       0,   267,  -250,  -250,  -250,  -250,   267,   102,   275,  -250,
     307,  -250,   259,  -250,   308,    -7,   309,  -250,   277,  -250,
     316,  -250,  -250,  -250,   245,  -250,  -250,  -250,  -250,   245,
     278,  -250,  -250,   308,   309,   119,  -250,  -250,  -250,  -250
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     170,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     112,   111,   113,   114,   115,    61,    58,    59,   123,    60,
       0,    90,    97,    81,    82,    94,    99,     0,    91,   121,
      70,     0,    31,    30,     0,     0,     0,     0,     0,   168,
       1,   171,     2,     0,     0,     0,    29,     0,     0,     0,
       0,     0,     0,     0,    89,     0,     0,     0,     0,     0,
       0,     0,    95,     0,   100,     0,     0,    92,     0,     0,
     140,     0,     0,     0,     0,     0,     0,     0,   116,     0,
     117,   118,     0,     0,     0,   122,     0,    88,   124,    98,
      83,    84,    85,    86,    87,    96,   101,   105,   109,   107,
     110,    93,   127,   125,     0,     0,   148,    62,     0,   140,
      64,     0,   169,    55,     0,     0,    38,     0,     0,    36,
     102,     0,   103,     0,   104,     0,     0,     0,     0,   128,
       0,   142,     0,     0,   165,   166,   159,   160,   161,   162,
     163,   164,     0,   141,   149,     0,     0,     0,    63,    56,
      57,     0,    46,    47,    48,    49,    50,    51,    42,     0,
       0,     0,     0,   119,   120,   127,   125,   107,   106,   129,
     125,     0,   134,     0,    53,     0,     0,     0,     0,     0,
     148,   158,    66,    65,     0,     0,     0,    43,    41,    38,
      37,    34,     0,   142,   108,   126,   143,   144,   146,     0,
       0,    67,   132,     0,     0,     0,   151,     0,     0,     0,
     154,    71,    72,   156,   153,   150,   167,    45,     0,    44,
      39,     0,     0,    34,     0,     0,     0,     0,     0,   148,
     142,    53,    52,   152,   155,   157,    53,    42,    34,    32,
       0,    73,   145,   147,    79,    76,   138,   133,   134,    54,
       0,    40,    35,    33,     0,    69,    78,    77,    75,     0,
     136,    68,    74,    79,   138,   148,   135,    80,   139,   137
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -250,  -250,   314,  -250,  -250,  -250,  -250,  -250,  -250,  -250,
    -250,  -250,  -250,  -240,  -250,  -250,   113,   144,    67,  -250,
    -250,  -250,  -249,  -170,  -110,  -250,  -250,  -250,   167,  -250,
     -78,  -187,  -250,    51,  -250,    43,  -250,     7,    -3,  -250,
    -250,   140,   186,  -250,  -250,  -250,  -250,   262,   -84,  -162,
    -136,  -250,  -250,    61,  -250,    44,   202,  -218,  -250,    85,
    -215,  -191,   173,  -250,  -250,  -250,  -250
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   262,    31,    32,   200,   156,   228,   258,
     198,    33,   244,   152,    61,    34,    35,   149,   150,    36,
     250,    62,   252,   284,   298,   295,    37,    63,   182,    65,
      66,   167,   139,    67,   119,   122,   124,    71,    68,   171,
     143,   144,   270,   241,   306,   300,   147,   212,   236,   237,
     183,   184,   185,    38,    39,    40,    82
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    64,   153,   214,   120,   255,   101,    91,   168,   103,
     296,    70,   106,   168,  -131,   264,   222,   187,  -130,   225,
     238,   140,   289,   280,    41,    72,    42,   290,    73,   206,
     251,   251,   192,   193,   210,    58,   118,   146,   292,   194,
     195,   196,    75,    58,   233,   211,    92,   138,   235,    76,
      55,   127,   288,   226,   287,   227,    74,    94,   297,    96,
     251,   251,   197,   153,    77,    56,    57,    44,    59,    45,
     151,   161,    78,   271,   238,   283,   153,    43,   102,   276,
     169,   104,   140,    80,   107,   169,   121,   123,    64,   137,
     309,    99,   100,    64,   131,   132,   133,   134,   125,    46,
      47,    48,   163,   130,    81,    97,    98,    99,   100,   189,
     190,    49,    97,    98,    99,   100,   245,    83,   246,    50,
      51,    52,    53,    54,    97,    98,    99,   100,    55,    84,
      46,    47,    48,   153,    97,    98,    99,   100,    85,   153,
     253,    58,    49,    56,    57,   138,    59,    55,   151,    86,
      50,    51,    52,    53,    54,    97,    98,    99,   100,   226,
      87,   227,    56,    57,    58,    59,    88,    60,    69,   274,
     275,   239,   240,   174,   175,   247,   248,    89,    55,    90,
      93,    95,   221,   285,   286,   176,   177,   178,   179,   180,
     181,   105,  -122,    56,    57,    58,    59,   108,    60,    46,
      47,    48,   109,   110,    91,    46,    47,    48,   111,   113,
     285,    49,   112,   114,   115,   304,   254,    49,   116,    50,
      51,    52,    53,    54,   117,    50,    51,    52,    53,    54,
     145,   128,   158,   160,   129,   135,   146,   136,   141,   142,
     148,   162,   164,   154,   165,   155,   157,    55,   159,   166,
     170,   172,   173,    55,   191,   186,   199,   201,   202,   203,
     208,   204,    56,    57,    58,    59,   211,    60,    56,    57,
      58,    59,   205,    60,     1,     2,   213,   209,   220,     3,
     224,   231,   230,   232,   242,     4,     5,     6,     7,     8,
       9,    10,   243,   249,   257,    11,    12,    13,   256,   259,
     261,   265,   263,   267,   269,   266,   268,   272,    14,    15,
     273,   174,   175,   215,   216,   277,   279,    16,   281,    17,
     278,    58,    18,   176,   177,   178,   179,   180,   181,   217,
     218,   293,    79,   294,   299,    97,    98,    99,   100,   240,
     302,   305,   260,   229,   291,   303,   307,   234,   308,   301,
     282,   188,   207,   126,   223,   219
};

static const yytype_int16 yycheck[] =
{
       3,     4,   112,   173,    88,   220,     4,    16,     4,     4,
      17,     4,     4,     4,    14,   233,   186,    25,    14,    23,
     211,   105,   271,   263,     7,    76,     9,   276,     8,   165,
     217,   218,    29,    30,   170,    76,    77,    45,   278,    36,
      37,    38,    44,    76,   206,    45,    49,    80,   210,    76,
      59,    24,   270,    57,   269,    59,    42,    60,    65,    25,
     247,   248,    59,   173,    76,    74,    75,     7,    77,     9,
      79,    25,    51,   243,   265,   266,   186,    60,    76,   249,
      76,    76,   166,     0,    76,    76,    89,    90,    91,    24,
     305,    80,    81,    96,    97,    98,    99,   100,    91,    11,
      12,    13,    25,    96,     3,    78,    79,    80,    81,    74,
      75,    23,    78,    79,    80,    81,    57,    76,    59,    31,
      32,    33,    34,    35,    78,    79,    80,    81,    59,    76,
      11,    12,    13,   243,    78,    79,    80,    81,     9,   249,
     218,    76,    23,    74,    75,    80,    77,    59,    79,    76,
      31,    32,    33,    34,    35,    78,    79,    80,    81,    57,
      76,    59,    74,    75,    76,    77,    23,    79,    80,   247,
     248,    61,    62,    54,    55,    72,    73,    23,    59,    23,
      41,     4,   185,   267,   268,    66,    67,    68,    69,    70,
      71,    23,    44,    74,    75,    76,    77,    44,    79,    11,
      12,    13,    76,    76,    16,    11,    12,    13,    48,    52,
     294,    23,    66,    23,    49,   299,   219,    23,    76,    31,
      32,    33,    34,    35,    49,    31,    32,    33,    34,    35,
      43,    76,    49,    24,    76,    76,    45,    76,    76,    76,
      76,    24,    24,    77,    44,    76,    76,    59,    76,    25,
      25,    14,    23,    59,    42,    66,    25,    23,    76,    74,
      24,    77,    74,    75,    76,    77,    45,    79,    74,    75,
      76,    77,    76,    79,     5,     6,    15,    76,    46,    10,
       7,    76,    24,    23,    76,    16,    17,    18,    19,    20,
      21,    22,    25,    23,    74,    26,    27,    28,    76,    59,
      25,    47,    76,    64,    49,    46,    64,    24,    39,    40,
      59,    54,    55,    56,    57,    24,    24,    48,    24,    50,
      76,    76,    53,    66,    67,    68,    69,    70,    71,    72,
      73,    24,    18,    25,    25,    78,    79,    80,    81,    62,
      24,    63,   229,   199,   277,   294,   303,   207,   304,   288,
     265,   149,   166,    91,   187,   182
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    10,    16,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    39,    40,    48,    50,    53,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    97,    98,   104,   108,   109,   112,   119,   146,   147,
     148,     7,     9,    60,     7,     9,    11,    12,    13,    23,
      31,    32,    33,    34,    35,    59,    74,    75,    76,    77,
      79,   107,   114,   120,   121,   122,   123,   126,   131,    80,
     120,   130,    76,     8,    42,    44,    76,    76,    51,    85,
       0,     3,   149,    76,    76,     9,    76,    76,    23,    23,
      23,    16,   121,    41,   121,     4,    25,    78,    79,    80,
      81,     4,    76,     4,    76,    23,     4,    76,    44,    76,
      76,    48,    66,    52,    23,    49,    76,    49,    77,   127,
     131,   121,   128,   121,   129,   120,   130,    24,    76,    76,
     120,   121,   121,   121,   121,    76,    76,    24,    80,   125,
     131,    76,    76,   133,   134,    43,    45,   139,    76,   110,
     111,    79,   106,   107,    77,    76,   100,    76,    49,    76,
      24,    25,    24,    25,    24,    44,    25,   124,     4,    76,
      25,   132,    14,    23,    54,    55,    66,    67,    68,    69,
      70,    71,   121,   143,   144,   145,    66,    25,   139,    74,
      75,    42,    29,    30,    36,    37,    38,    59,   103,    25,
      99,    23,    76,    74,    77,    76,   133,   125,    24,    76,
     133,    45,   140,    15,   106,    56,    57,    72,    73,   145,
      46,   121,   106,   111,     7,    23,    57,    59,   101,   100,
      24,    76,    23,   132,   124,   132,   141,   142,   144,    61,
      62,   136,    76,    25,   105,    57,    59,    72,    73,    23,
     113,   114,   115,   113,   121,   143,    76,    74,   102,    59,
      99,    25,    96,    76,   140,    47,    46,    64,    64,    49,
     135,   106,    24,    59,   113,   113,   106,    24,    76,    24,
      96,    24,   142,   144,   116,   131,   131,   143,   140,   105,
     105,   101,    96,    24,    25,   118,    17,    65,   117,    25,
     138,   136,    24,   116,   131,    63,   137,   118,   138,   143
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    95,    96,    96,    97,    98,    99,    99,
     100,   100,   101,   101,   101,   102,   103,   103,   103,   103,
     103,   103,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   107,   108,   109,   110,   110,   111,   112,   112,   112,
     112,   113,   113,   114,   115,   116,   117,   117,   117,   118,
     118,   119,   120,   120,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   126,   126,   126,   127,   127,   128,   128,
     129,   130,   130,   131,   131,   132,   132,   133,   133,   133,
     134,   134,   135,   135,   136,   136,   137,   137,   138,   138,
     139,   139,   140,   140,   141,   141,   142,   142,   143,   143,
     143,   144,   144,   144,   144,   144,   144,   144,   144,   145,
     145,   145,   145,   145,   145,   145,   145,   146,   147,   148,
     149,   149
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     2,     2,     1,     1,
       1,     1,     4,     5,     1,     3,     3,     7,    10,    10,
       2,     1,     1,     8,     4,     2,     0,     1,     1,     0,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     2,     3,     1,     2,     3,     1,     3,     1,
       2,     3,     4,     4,     4,     3,     5,     0,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     1,     1,     3,     0,     3,     1,     2,     3,
       1,     5,     0,     2,     0,     5,     0,     2,     0,     3,
       0,     2,     0,     2,     1,     3,     1,     3,     0,     1,
       3,     3,     4,     3,     3,     4,     3,     4,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     7,     2,     4,
       0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp, sql_string, sql_result, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , sql_string, sql_result, scanner);
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (sql_string);
  YYUSE (sql_result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* The lookahead symbol.  */
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
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 245 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1831 "yacc_sql.cpp"
    break;

  case 23:
#line 275 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1840 "yacc_sql.cpp"
    break;

  case 24:
#line 281 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1848 "yacc_sql.cpp"
    break;

  case 25:
#line 286 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1856 "yacc_sql.cpp"
    break;

  case 26:
#line 292 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 27:
#line 298 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 28:
#line 304 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1880 "yacc_sql.cpp"
    break;

  case 29:
#line 310 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1890 "yacc_sql.cpp"
    break;

  case 30:
#line 317 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1898 "yacc_sql.cpp"
    break;

  case 31:
#line 323 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1908 "yacc_sql.cpp"
    break;

  case 32:
#line 332 "yacc_sql.y"
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
#line 1931 "yacc_sql.cpp"
    break;

  case 33:
#line 351 "yacc_sql.y"
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
#line 1954 "yacc_sql.cpp"
    break;

  case 34:
#line 373 "yacc_sql.y"
    {
      (yyval.attr_names) = nullptr;
    }
#line 1962 "yacc_sql.cpp"
    break;

  case 35:
#line 377 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_names) != nullptr) {
        (yyval.attr_names) = (yyvsp[0].attr_names);
      } else {
        (yyval.attr_names) = new std::vector<std::string>;
      }
      (yyval.attr_names)->emplace_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 36:
#line 390 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1988 "yacc_sql.cpp"
    break;

  case 37:
#line 400 "yacc_sql.y"
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
#line 2008 "yacc_sql.cpp"
    break;

  case 38:
#line 418 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2016 "yacc_sql.cpp"
    break;

  case 39:
#line 422 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 40:
#line 435 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2043 "yacc_sql.cpp"
    break;

  case 41:
#line 444 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2056 "yacc_sql.cpp"
    break;

  case 42:
#line 455 "yacc_sql.y"
    { (yyval.bools) = true; }
#line 2062 "yacc_sql.cpp"
    break;

  case 43:
#line 456 "yacc_sql.y"
             { (yyval.bools) = true; }
#line 2068 "yacc_sql.cpp"
    break;

  case 44:
#line 457 "yacc_sql.y"
                 { (yyval.bools) = false; }
#line 2074 "yacc_sql.cpp"
    break;

  case 45:
#line 461 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2080 "yacc_sql.cpp"
    break;

  case 46:
#line 464 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2086 "yacc_sql.cpp"
    break;

  case 47:
#line 465 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2092 "yacc_sql.cpp"
    break;

  case 48:
#line 466 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2098 "yacc_sql.cpp"
    break;

  case 49:
#line 467 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2104 "yacc_sql.cpp"
    break;

  case 50:
#line 468 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2110 "yacc_sql.cpp"
    break;

  case 51:
#line 469 "yacc_sql.y"
               { (yyval.number)=NULLS; }
#line 2116 "yacc_sql.cpp"
    break;

  case 52:
#line 473 "yacc_sql.y"
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
#line 2132 "yacc_sql.cpp"
    break;

  case 53:
#line 488 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2140 "yacc_sql.cpp"
    break;

  case 54:
#line 491 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2154 "yacc_sql.cpp"
    break;

  case 55:
#line 502 "yacc_sql.y"
                   {
      (yyval.value) = (yyvsp[0].value);
      (yyloc) = (yylsp[0]);
    }
#line 2163 "yacc_sql.cpp"
    break;

  case 56:
#line 506 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 57:
#line 510 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2181 "yacc_sql.cpp"
    break;

  case 58:
#line 517 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2190 "yacc_sql.cpp"
    break;

  case 59:
#line 521 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2199 "yacc_sql.cpp"
    break;

  case 60:
#line 525 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2209 "yacc_sql.cpp"
    break;

  case 61:
#line 530 "yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_type(NULLS);
      (yyloc) = (yylsp[0]);
    }
#line 2219 "yacc_sql.cpp"
    break;

  case 62:
#line 539 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2233 "yacc_sql.cpp"
    break;

  case 63:
#line 551 "yacc_sql.y"
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
#line 2248 "yacc_sql.cpp"
    break;

  case 64:
#line 565 "yacc_sql.y"
    {
      (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2257 "yacc_sql.cpp"
    break;

  case 65:
#line 570 "yacc_sql.y"
    {
      if ((yyvsp[-2].update_unit_list) == nullptr) {
        (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      } else {
        (yyval.update_unit_list) = (yyvsp[-2].update_unit_list);
      }

      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2271 "yacc_sql.cpp"
    break;

  case 66:
#line 583 "yacc_sql.y"
    {
      (yyval.update_unit) = new UpdateUnit((yyvsp[-2].string), (yyvsp[0].value));
    }
#line 2279 "yacc_sql.cpp"
    break;

  case 67:
#line 590 "yacc_sql.y"
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
#line 2309 "yacc_sql.cpp"
    break;

  case 68:
#line 616 "yacc_sql.y"
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
#line 2336 "yacc_sql.cpp"
    break;

  case 69:
#line 639 "yacc_sql.y"
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
#line 2368 "yacc_sql.cpp"
    break;

  case 70:
#line 667 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2381 "yacc_sql.cpp"
    break;

  case 71:
#line 679 "yacc_sql.y"
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2389 "yacc_sql.cpp"
    break;

  case 72:
#line 683 "yacc_sql.y"
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 73:
#line 689 "yacc_sql.y"
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
#line 2424 "yacc_sql.cpp"
    break;

  case 74:
#line 714 "yacc_sql.y"
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
#line 2440 "yacc_sql.cpp"
    break;

  case 75:
#line 728 "yacc_sql.y"
                       {
        (yyval.order_item) = new OrderBy;
        (yyval.order_item)->order_by_attribute = *(yyvsp[-1].rel_attr);
        (yyval.order_item)->order = (yyvsp[0].bools);
        delete (yyvsp[-1].rel_attr);
	}
#line 2451 "yacc_sql.cpp"
    break;

  case 76:
#line 737 "yacc_sql.y"
                    {
		(yyval.bools) = 0;
	}
#line 2459 "yacc_sql.cpp"
    break;

  case 77:
#line 740 "yacc_sql.y"
              {
		(yyval.bools) = 0;
	}
#line 2467 "yacc_sql.cpp"
    break;

  case 78:
#line 743 "yacc_sql.y"
               {
		(yyval.bools) = 1;
	}
#line 2475 "yacc_sql.cpp"
    break;

  case 79:
#line 750 "yacc_sql.y"
        {
	    (yyval.order_item_list) = nullptr;
	}
#line 2483 "yacc_sql.cpp"
    break;

  case 80:
#line 754 "yacc_sql.y"
        {
        if((yyvsp[0].order_item_list) != nullptr) {
            (yyval.order_item_list) = (yyvsp[0].order_item_list);
        } else {
            (yyval.order_item_list) = new std::vector<OrderBy>;
        }
        (yyval.order_item_list)->emplace_back(*(yyvsp[-1].order_item));
        delete (yyvsp[-1].order_item);
	}
#line 2497 "yacc_sql.cpp"
    break;

  case 81:
#line 767 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2508 "yacc_sql.cpp"
    break;

  case 82:
#line 777 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2517 "yacc_sql.cpp"
    break;

  case 83:
#line 782 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2530 "yacc_sql.cpp"
    break;

  case 84:
#line 792 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 85:
#line 795 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2546 "yacc_sql.cpp"
    break;

  case 86:
#line 798 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2554 "yacc_sql.cpp"
    break;

  case 87:
#line 801 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2562 "yacc_sql.cpp"
    break;

  case 88:
#line 804 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2571 "yacc_sql.cpp"
    break;

  case 89:
#line 808 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2579 "yacc_sql.cpp"
    break;

  case 90:
#line 811 "yacc_sql.y"
                     {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2589 "yacc_sql.cpp"
    break;

  case 91:
#line 816 "yacc_sql.y"
               {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      (yyval.expression)->set_name((yyvsp[0].rel_attr)->name());
    }
#line 2598 "yacc_sql.cpp"
    break;

  case 92:
#line 820 "yacc_sql.y"
                  {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-1].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 93:
#line 824 "yacc_sql.y"
                     {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-2].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2616 "yacc_sql.cpp"
    break;

  case 94:
#line 828 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2625 "yacc_sql.cpp"
    break;

  case 95:
#line 832 "yacc_sql.y"
                   {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2634 "yacc_sql.cpp"
    break;

  case 96:
#line 836 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 97:
#line 840 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2652 "yacc_sql.cpp"
    break;

  case 98:
#line 844 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2661 "yacc_sql.cpp"
    break;

  case 99:
#line 849 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2670 "yacc_sql.cpp"
    break;

  case 100:
#line 854 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2679 "yacc_sql.cpp"
    break;

  case 101:
#line 859 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2688 "yacc_sql.cpp"
    break;

  case 102:
#line 866 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, *(yyvsp[-1].func_args));
    }
#line 2696 "yacc_sql.cpp"
    break;

  case 103:
#line 869 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, *(yyvsp[-1].func_args));
    }
#line 2704 "yacc_sql.cpp"
    break;

  case 104:
#line 872 "yacc_sql.y"
                                                 {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, *(yyvsp[-1].func_args));
    }
#line 2712 "yacc_sql.cpp"
    break;

  case 105:
#line 882 "yacc_sql.y"
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
#line 2732 "yacc_sql.cpp"
    break;

  case 106:
#line 898 "yacc_sql.y"
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
#line 2775 "yacc_sql.cpp"
    break;

  case 107:
#line 940 "yacc_sql.y"
  {
    (yyval.rel_attr_list)=nullptr;
  }
#line 2783 "yacc_sql.cpp"
    break;

  case 108:
#line 944 "yacc_sql.y"
  {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    delete (yyvsp[-1].rel_attr);
  }
#line 2797 "yacc_sql.cpp"
    break;

  case 109:
#line 959 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = "*";
  }
#line 2806 "yacc_sql.cpp"
    break;

  case 110:
#line 964 "yacc_sql.y"
  {
    (yyval.rel_attr)=(yyvsp[0].rel_attr);
  }
#line 2814 "yacc_sql.cpp"
    break;

  case 111:
#line 972 "yacc_sql.y"
    {
       (yyval.agg_func)=MAX_FUNC;
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 112:
#line 976 "yacc_sql.y"
    {
       (yyval.agg_func)=MIN_FUNC;
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 113:
#line 980 "yacc_sql.y"
    {
       (yyval.agg_func)=AVG_FUNC;
    }
#line 2838 "yacc_sql.cpp"
    break;

  case 114:
#line 984 "yacc_sql.y"
    {
       (yyval.agg_func)=COUNT_FUNC;
    }
#line 2846 "yacc_sql.cpp"
    break;

  case 115:
#line 988 "yacc_sql.y"
    {
       (yyval.agg_func)=SUM_FUNC;
    }
#line 2854 "yacc_sql.cpp"
    break;

  case 116:
#line 995 "yacc_sql.y"
        {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *value_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      free(tmp);
    }
#line 2867 "yacc_sql.cpp"
    break;

  case 117:
#line 1003 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      RelAttrExprSqlNode *attr_expr = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      attr_expr->set_name((yyvsp[0].rel_attr)->name());
      std::unique_ptr<Expression> target(attr_expr);
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2879 "yacc_sql.cpp"
    break;

  case 118:
#line 1013 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[0].expression));
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 119:
#line 1018 "yacc_sql.y"
                              {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      ValueExpr *value_expr = new ValueExpr(Value((int)(yyvsp[0].number)));
      std::unique_ptr<Expression> precise(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(precise));
    }
#line 2902 "yacc_sql.cpp"
    break;

  case 120:
#line 1029 "yacc_sql.y"
                         {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *format_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      std::unique_ptr<Expression> format(format_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(format));
    }
#line 2916 "yacc_sql.cpp"
    break;

  case 121:
#line 1042 "yacc_sql.y"
        {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      (yyval.expression_list)->emplace_back(new RelAttrExprSqlNode(attr));
    }
#line 2928 "yacc_sql.cpp"
    break;

  case 122:
#line 1049 "yacc_sql.y"
                      {
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2937 "yacc_sql.cpp"
    break;

  case 123:
#line 1056 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2947 "yacc_sql.cpp"
    break;

  case 124:
#line 1061 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2959 "yacc_sql.cpp"
    break;

  case 125:
#line 1072 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 126:
#line 1075 "yacc_sql.y"
                                  {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->push_back(std::move(*(yyvsp[-1].single_table)));
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 127:
#line 1088 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2990 "yacc_sql.cpp"
    break;

  case 128:
#line 1093 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-1].string), (yyvsp[0].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3000 "yacc_sql.cpp"
    break;

  case 129:
#line 1099 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-2].string), (yyvsp[0].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3010 "yacc_sql.cpp"
    break;

  case 130:
#line 1108 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode((yyvsp[0].string));
       free((yyvsp[0].string));
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 131:
#line 1113 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode(
        new JoinSqlNode(JT_INNER, (yyvsp[-4].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-1].string)), std::move(*(yyvsp[0].condition_list)))
       );
       free((yyvsp[-1].string));
    }
#line 3030 "yacc_sql.cpp"
    break;

  case 132:
#line 1122 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3038 "yacc_sql.cpp"
    break;

  case 133:
#line 1125 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3046 "yacc_sql.cpp"
    break;

  case 134:
#line 1133 "yacc_sql.y"
  {
    (yyval.group_by)=nullptr;
  }
#line 3054 "yacc_sql.cpp"
    break;

  case 135:
#line 1138 "yacc_sql.y"
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
#line 3073 "yacc_sql.cpp"
    break;

  case 136:
#line 1155 "yacc_sql.y"
  {
    (yyval.having)=nullptr;
  }
#line 3081 "yacc_sql.cpp"
    break;

  case 137:
#line 1159 "yacc_sql.y"
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
#line 3098 "yacc_sql.cpp"
    break;

  case 138:
#line 1176 "yacc_sql.y"
  {
    (yyval.rel_attr_list)=nullptr;
  }
#line 3106 "yacc_sql.cpp"
    break;

  case 139:
#line 1180 "yacc_sql.y"
  {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(std::move(*(yyvsp[-1].rel_attr)));
  }
#line 3119 "yacc_sql.cpp"
    break;

  case 140:
#line 1193 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3127 "yacc_sql.cpp"
    break;

  case 141:
#line 1196 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3135 "yacc_sql.cpp"
    break;

  case 142:
#line 1202 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3143 "yacc_sql.cpp"
    break;

  case 143:
#line 1205 "yacc_sql.y"
                         {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3152 "yacc_sql.cpp"
    break;

  case 144:
#line 1211 "yacc_sql.y"
                  {
     (yyval.condition) = (yyvsp[0].condition);
    }
#line 3160 "yacc_sql.cpp"
    break;

  case 145:
#line 1214 "yacc_sql.y"
                                    {
        std::unique_ptr<Expression> left((yyvsp[-2].condition));
        std::unique_ptr<Expression> right((yyvsp[0].condition));
        (yyval.condition) = new ComparisonExpr(OR_OP, std::move(left), std::move(right));
    }
#line 3170 "yacc_sql.cpp"
    break;

  case 146:
#line 1221 "yacc_sql.y"
               {
        (yyval.condition) = (yyvsp[0].condition);
     }
#line 3178 "yacc_sql.cpp"
    break;

  case 147:
#line 1224 "yacc_sql.y"
                                   {
        std::unique_ptr<Expression> left((yyvsp[-2].condition));
        std::unique_ptr<Expression> right((yyvsp[0].condition));
        (yyval.condition) = new ComparisonExpr(AND_OP, std::move(left), std::move(right));
     }
#line 3188 "yacc_sql.cpp"
    break;

  case 148:
#line 1233 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3196 "yacc_sql.cpp"
    break;

  case 149:
#line 1236 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 150:
#line 1240 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3214 "yacc_sql.cpp"
    break;

  case 151:
#line 1247 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value value = Value();
      value.set_type(NULLS);
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NULL, std::move(left), std::move(right));
    }
#line 3227 "yacc_sql.cpp"
    break;

  case 152:
#line 1256 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      Value value = Value();
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NOT_NULL, std::move(left), std::move(right));
    }
#line 3239 "yacc_sql.cpp"
    break;

  case 153:
#line 1264 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3249 "yacc_sql.cpp"
    break;

  case 154:
#line 1270 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_IN_OP, std::move(left), std::move(right));
    }
#line 3259 "yacc_sql.cpp"
    break;

  case 155:
#line 1276 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_NOT_IN, std::move(left), std::move(right));
    }
#line 3269 "yacc_sql.cpp"
    break;

  case 156:
#line 1282 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_EXISTS_OP, std::move(left), std::move(right));
    }
#line 3279 "yacc_sql.cpp"
    break;

  case 157:
#line 1288 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_NOT_EXISTS, std::move(left), std::move(right));
    }
#line 3289 "yacc_sql.cpp"
    break;

  case 158:
#line 1294 "yacc_sql.y"
    {
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), nullptr, std::move(right));
    }
#line 3298 "yacc_sql.cpp"
    break;

  case 159:
#line 1301 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3304 "yacc_sql.cpp"
    break;

  case 160:
#line 1302 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3310 "yacc_sql.cpp"
    break;

  case 161:
#line 1303 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3316 "yacc_sql.cpp"
    break;

  case 162:
#line 1304 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3322 "yacc_sql.cpp"
    break;

  case 163:
#line 1305 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3328 "yacc_sql.cpp"
    break;

  case 164:
#line 1306 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3334 "yacc_sql.cpp"
    break;

  case 165:
#line 1307 "yacc_sql.y"
           { (yyval.comp) = LIKES; }
#line 3340 "yacc_sql.cpp"
    break;

  case 166:
#line 1308 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKES; }
#line 3346 "yacc_sql.cpp"
    break;

  case 167:
#line 1313 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3360 "yacc_sql.cpp"
    break;

  case 168:
#line 1326 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3369 "yacc_sql.cpp"
    break;

  case 169:
#line 1334 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3381 "yacc_sql.cpp"
    break;


#line 3385 "yacc_sql.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1346 "yacc_sql.y"

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
