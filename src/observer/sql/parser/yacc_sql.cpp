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
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   372

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  83
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  177
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

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
       0,   245,   245,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   277,   283,   288,   294,   300,   306,
     312,   319,   325,   333,   352,   375,   378,   391,   401,   419,
     429,   432,   445,   454,   466,   467,   468,   472,   475,   476,
     477,   478,   479,   480,   483,   499,   502,   513,   517,   521,
     528,   532,   536,   541,   549,   561,   575,   580,   593,   597,
     604,   630,   653,   681,   693,   697,   703,   728,   743,   752,
     755,   758,   765,   768,   781,   791,   796,   807,   810,   813,
     816,   819,   823,   826,   831,   835,   839,   843,   847,   851,
     855,   859,   863,   868,   873,   878,   889,   892,   895,   904,
     920,   963,   966,   981,   986,   994,   998,  1002,  1006,  1010,
    1018,  1026,  1036,  1041,  1052,  1065,  1072,  1081,  1090,  1097,
    1102,  1113,  1116,  1128,  1133,  1139,  1148,  1153,  1163,  1166,
    1174,  1178,  1196,  1199,  1217,  1220,  1234,  1237,  1243,  1246,
    1252,  1255,  1262,  1265,  1274,  1277,  1281,  1287,  1296,  1304,
    1310,  1316,  1322,  1328,  1334,  1342,  1343,  1344,  1345,  1346,
    1347,  1348,  1349,  1353,  1366,  1374,  1384,  1385
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
  "drop_index_stmt", "create_table_stmt", "create_table_select_stmt",
  "attr_def_list", "attr_def", "nullable", "number", "type", "insert_stmt",
  "value_list", "value", "unsigned_value", "delete_stmt", "update_stmt",
  "update_list", "update_unit", "select_stmt", "sub_query_two_expr",
  "sub_query_expr", "sub_query_list_expr", "order_item", "order",
  "order_item_list", "calc_stmt", "expression_list", "expression",
  "func_expr", "agg_expr", "agg_field_list", "agg_field", "agg_func",
  "length_args", "round_args", "date_format_args", "select_attr",
  "rel_attr", "rel_list", "single_table", "general_rel", "join_condition",
  "group_by", "having", "rel_attr_list", "where", "select_where",
  "condition_or", "condition_and", "condition_list", "condition",
  "comp_op", "load_data_stmt", "explain_stmt", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
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

#define YYPACT_NINF (-254)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-138)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     240,    17,    37,    96,    89,   -53,    59,  -254,    28,    39,
      49,  -254,  -254,  -254,  -254,  -254,    61,    60,   240,    86,
     141,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,    91,   114,   126,   116,   117,   130,   164,   182,
     127,  -254,  -254,  -254,  -254,  -254,  -254,  -254,  -254,   166,
    -254,    96,  -254,   204,  -254,   101,     3,     4,   186,     5,
       9,   174,   178,  -254,  -254,   147,   161,   190,   177,   196,
    -254,  -254,  -254,  -254,    13,   198,   173,  -254,   202,   -44,
      96,    96,    89,    35,    30,  -254,   176,    96,    96,    96,
      96,    96,   179,  -254,   187,  -254,   109,   188,  -254,   189,
    -254,   197,   210,   226,   199,   195,   200,   260,   205,   211,
     229,   213,   245,  -254,   267,  -254,   132,   268,   149,   278,
    -254,   259,  -254,  -254,  -254,  -254,  -254,   -29,   -29,  -254,
    -254,  -254,  -254,  -254,  -254,   279,  -254,  -254,  -254,     0,
     280,   296,   288,   165,  -254,   246,    20,  -254,   -13,  -254,
    -254,   271,  -254,     1,   289,   292,   241,  -254,   242,  -254,
     247,  -254,   239,  -254,   243,    66,   298,   244,  -254,   243,
     281,   308,   195,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,   228,  -254,   282,    96,   -11,   199,  -254,  -254,  -254,
     317,  -254,  -254,  -254,  -254,  -254,  -254,    -2,   205,   301,
     251,   306,  -254,  -254,    16,   280,   279,  -254,  -254,   280,
     165,    56,   254,   307,    46,   111,   310,   310,    96,   165,
     136,   315,  -254,  -254,  -254,   258,   261,   277,  -254,  -254,
     289,  -254,   312,   262,   281,  -254,  -254,   293,   295,  -254,
     275,   283,  -254,   294,   195,   318,   285,  -254,   310,   310,
      77,  -254,  -254,  -254,  -254,   136,  -254,  -254,  -254,   321,
    -254,  -254,   270,   324,   312,   325,   165,   165,   274,   274,
     165,    11,   307,  -254,  -254,  -254,  -254,   307,    75,   312,
    -254,   327,  -254,   295,  -254,   328,    10,   329,  -254,   290,
    -254,   331,  -254,  -254,  -254,   274,  -254,  -254,  -254,  -254,
     274,   297,  -254,  -254,   328,   329,   165,  -254,  -254,  -254,
    -254
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     176,    23,    22,    15,    16,    17,    18,    10,    11,    12,
      13,    14,     8,     9,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   116,   115,   117,   118,   119,    63,    60,    61,   129,
      62,     0,    93,   100,    84,    85,    97,   102,     0,    94,
     125,    73,     0,    32,    31,     0,     0,     0,     0,     0,
     174,     1,   177,     2,     0,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,    92,     0,     0,     0,     0,
       0,     0,     0,    98,     0,   103,     0,     0,    95,     0,
     127,     0,     0,   146,     0,     0,     0,     0,     0,     0,
       0,     0,   129,   120,     0,   121,   122,     0,     0,     0,
     128,     0,    91,   130,   105,   101,    86,    87,    88,    89,
      90,    99,   104,   109,   113,   111,   114,    96,   126,   133,
     131,     0,     0,   154,    64,     0,   146,    66,     0,   175,
      57,     0,    39,     0,    40,     0,     0,    37,     0,   106,
       0,   107,     0,   108,     0,     0,     0,     0,   134,     0,
     148,     0,     0,   171,   172,   165,   166,   167,   168,   169,
     170,     0,   147,   155,     0,     0,     0,    65,    58,    59,
       0,    48,    49,    50,    51,    52,    53,    44,     0,     0,
       0,     0,   123,   124,   133,   131,   111,   110,   135,   131,
       0,   140,     0,    55,     0,     0,     0,     0,     0,   154,
     164,     0,    68,    69,    67,     0,     0,     0,    45,    43,
      40,    38,    35,     0,   148,   112,   132,   149,   150,   152,
       0,     0,    70,   138,     0,     0,     0,   157,     0,     0,
       0,   160,    74,    75,   162,   159,   156,   173,    47,     0,
      46,    41,     0,     0,    35,     0,     0,     0,     0,     0,
     154,   148,    55,    54,   158,   161,   163,    55,    44,    35,
      33,     0,    76,   151,   153,    82,    79,   144,   139,   140,
      56,     0,    42,    36,    34,     0,    72,    81,    80,    78,
       0,   142,    71,    77,    82,   144,   154,   141,    83,   145,
     143
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -254,  -254,   338,  -254,  -254,  -254,  -254,  -254,  -254,  -254,
    -254,  -254,  -254,  -246,  -254,  -254,  -254,   118,   151,    69,
    -254,  -254,  -254,  -253,  -176,  -113,  -254,  -254,  -254,   167,
     248,  -209,  -185,  -254,    57,  -254,    47,  -254,     7,    -3,
    -254,  -254,   148,   191,  -254,  -254,  -254,  -254,   276,   -84,
     -70,  -139,  -254,  -254,    68,  -254,    54,   214,  -228,  -254,
      95,  -226,  -205,   181,  -254,  -254,  -254,  -254
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   273,    31,    32,    33,   209,   164,   239,
     269,   207,    34,   255,   159,    62,    35,    36,   156,   157,
      37,   261,    63,   263,   295,   309,   306,    38,    64,   191,
      66,    67,   176,   145,    68,   124,   127,   129,    72,    69,
     180,   150,   151,   281,   252,   317,   311,   154,   221,   247,
     248,   192,   193,   194,    39,    40,    41,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,    65,   160,   266,   177,   125,   223,   102,   104,   107,
     233,    71,   231,   109,  -136,   249,   275,   117,   264,   232,
     177,   236,   146,    73,    42,  -137,    43,   307,   291,   300,
     201,   202,   122,   123,   301,   215,   118,   203,   204,   205,
     219,   262,   262,   303,    45,   196,    46,    93,    56,   285,
     286,   100,   101,   299,   298,   237,   220,   238,    95,   132,
     206,   198,   199,    57,    58,   153,    60,    74,   158,   160,
      75,   249,   294,   262,   262,   308,   178,    44,   282,   103,
     105,   108,   160,    76,   287,   110,    81,   126,   128,    65,
     320,   146,   178,    92,    65,   137,   138,   139,   140,   130,
      47,    48,    49,   256,   136,   257,   133,    47,    48,    49,
     134,    79,    50,    98,    99,   100,   101,   250,   251,    50,
      51,    52,    53,    54,    55,    77,    97,    51,    52,    53,
      54,    55,   237,   143,   238,    86,    56,    78,    47,    48,
      49,   160,   122,    92,    82,   244,   144,   160,    56,   246,
      50,    57,    58,    89,    60,    56,   158,   170,    51,    52,
      53,    54,    55,    57,    58,    59,    60,    84,    61,    70,
      57,    58,    59,    60,   172,    61,    47,    48,    49,    98,
      99,   100,   101,   258,   259,   122,    56,    90,    50,   144,
      85,   230,    87,    88,   296,   297,    51,    52,    53,    54,
      55,    57,    58,    59,    60,    91,    61,    94,    96,   106,
      98,    99,   100,   101,    98,    99,   100,   101,  -128,   183,
     184,   296,   111,   112,    56,   265,   315,    98,    99,   100,
     101,   185,   186,   187,   188,   189,   190,   113,   114,    57,
      58,    59,    60,   115,    61,     1,     2,   119,   116,   120,
       3,   121,   135,   152,    56,   141,     4,     5,     6,     7,
       8,     9,    10,   142,   147,   148,    11,    12,    13,    57,
      58,   153,    60,   149,   158,   155,     4,   161,   166,    14,
      15,   163,   183,   184,   224,   225,   168,   165,    16,   167,
      17,   169,   171,    18,   185,   186,   187,   188,   189,   190,
     226,   227,   173,   174,   175,   179,    98,    99,   100,   101,
     181,   182,   195,   200,   208,   210,   213,   211,   133,   214,
     218,   212,   217,   222,   235,   241,   220,   242,   229,   243,
     253,    92,   254,   260,   267,   268,   270,   272,   274,   278,
     276,   277,   283,   280,   284,   288,   289,   279,   290,   292,
     122,   304,   251,   305,   310,   313,    80,   302,   271,   240,
     316,   318,   314,   234,   245,   162,   216,   312,   131,   319,
     197,   293,   228
};

static const yytype_int16 yycheck[] =
{
       3,     4,   115,   229,     4,    89,   182,     4,     4,     4,
     195,     4,    23,     4,    14,   220,   244,     4,   227,   195,
       4,    23,   106,    76,     7,    14,     9,    17,   274,   282,
      29,    30,    76,    77,   287,   174,    23,    36,    37,    38,
     179,   226,   227,   289,     7,    25,     9,    50,    59,   258,
     259,    80,    81,   281,   280,    57,    45,    59,    61,    24,
      59,    74,    75,    74,    75,    45,    77,     8,    79,   182,
      42,   276,   277,   258,   259,    65,    76,    60,   254,    76,
      76,    76,   195,    44,   260,    76,     0,    90,    91,    92,
     316,   175,    76,    16,    97,    98,    99,   100,   101,    92,
      11,    12,    13,    57,    97,    59,    76,    11,    12,    13,
      80,    51,    23,    78,    79,    80,    81,    61,    62,    23,
      31,    32,    33,    34,    35,    76,    25,    31,    32,    33,
      34,    35,    57,    24,    59,     9,    59,    76,    11,    12,
      13,   254,    76,    16,     3,   215,    80,   260,    59,   219,
      23,    74,    75,    23,    77,    59,    79,    25,    31,    32,
      33,    34,    35,    74,    75,    76,    77,    76,    79,    80,
      74,    75,    76,    77,    25,    79,    11,    12,    13,    78,
      79,    80,    81,    72,    73,    76,    59,    23,    23,    80,
      76,   194,    76,    76,   278,   279,    31,    32,    33,    34,
      35,    74,    75,    76,    77,    23,    79,    41,     4,    23,
      78,    79,    80,    81,    78,    79,    80,    81,    44,    54,
      55,   305,    44,    76,    59,   228,   310,    78,    79,    80,
      81,    66,    67,    68,    69,    70,    71,    76,    48,    74,
      75,    76,    77,    66,    79,     5,     6,    49,    52,    76,
      10,    49,    76,    43,    59,    76,    16,    17,    18,    19,
      20,    21,    22,    76,    76,    76,    26,    27,    28,    74,
      75,    45,    77,    76,    79,    76,    16,    77,    49,    39,
      40,    76,    54,    55,    56,    57,    41,    76,    48,    76,
      50,    24,    24,    53,    66,    67,    68,    69,    70,    71,
      72,    73,    24,    44,    25,    25,    78,    79,    80,    81,
      14,    23,    66,    42,    25,    23,    77,    76,    76,    76,
      76,    74,    24,    15,     7,    24,    45,    76,    46,    23,
      76,    16,    25,    23,    76,    74,    59,    25,    76,    64,
      47,    46,    24,    49,    59,    24,    76,    64,    24,    24,
      76,    24,    62,    25,    25,    24,    18,   288,   240,   208,
      63,   314,   305,   196,   216,   117,   175,   299,    92,   315,
     156,   276,   191
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    10,    16,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    39,    40,    48,    50,    53,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    97,    98,    99,   105,   109,   110,   113,   120,   147,
     148,   149,     7,     9,    60,     7,     9,    11,    12,    13,
      23,    31,    32,    33,    34,    35,    59,    74,    75,    76,
      77,    79,   108,   115,   121,   122,   123,   124,   127,   132,
      80,   121,   131,    76,     8,    42,    44,    76,    76,    51,
      85,     0,     3,   150,    76,    76,     9,    76,    76,    23,
      23,    23,    16,   122,    41,   122,     4,    25,    78,    79,
      80,    81,     4,    76,     4,    76,    23,     4,    76,     4,
      76,    44,    76,    76,    48,    66,    52,     4,    23,    49,
      76,    49,    76,    77,   128,   132,   122,   129,   122,   130,
     121,   131,    24,    76,    80,    76,   121,   122,   122,   122,
     122,    76,    76,    24,    80,   126,   132,    76,    76,    76,
     134,   135,    43,    45,   140,    76,   111,   112,    79,   107,
     108,    77,   113,    76,   101,    76,    49,    76,    41,    24,
      25,    24,    25,    24,    44,    25,   125,     4,    76,    25,
     133,    14,    23,    54,    55,    66,    67,    68,    69,    70,
      71,   122,   144,   145,   146,    66,    25,   140,    74,    75,
      42,    29,    30,    36,    37,    38,    59,   104,    25,   100,
      23,    76,    74,    77,    76,   134,   126,    24,    76,   134,
      45,   141,    15,   107,    56,    57,    72,    73,   146,    46,
     122,    23,   107,   115,   112,     7,    23,    57,    59,   102,
     101,    24,    76,    23,   133,   125,   133,   142,   143,   145,
      61,    62,   137,    76,    25,   106,    57,    59,    72,    73,
      23,   114,   115,   116,   114,   122,   144,    76,    74,   103,
      59,   100,    25,    96,    76,   141,    47,    46,    64,    64,
      49,   136,   107,    24,    59,   114,   114,   107,    24,    76,
      24,    96,    24,   143,   145,   117,   132,   132,   144,   141,
     106,   106,   102,    96,    24,    25,   119,    17,    65,   118,
      25,   139,   137,    24,   117,   132,    63,   138,   119,   139,
     144
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    83,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    95,    96,    96,    97,    98,    99,
     100,   100,   101,   101,   102,   102,   102,   103,   104,   104,
     104,   104,   104,   104,   105,   106,   106,   107,   107,   107,
     108,   108,   108,   108,   109,   110,   111,   111,   112,   112,
     113,   113,   113,   113,   114,   114,   115,   116,   117,   118,
     118,   118,   119,   119,   120,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   123,   123,   123,   124,
     124,   125,   125,   126,   126,   127,   127,   127,   127,   127,
     128,   128,   129,   129,   130,   131,   131,   131,   131,   132,
     132,   133,   133,   134,   134,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   139,   139,   140,   140,   141,   141,
     142,   142,   143,   143,   144,   144,   144,   145,   145,   145,
     145,   145,   145,   145,   145,   146,   146,   146,   146,   146,
     146,   146,   146,   147,   148,   149,   150,   150
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     9,    10,     0,     3,     5,     7,     5,
       0,     3,     6,     3,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     8,     0,     3,     1,     2,     2,
       1,     1,     1,     1,     4,     5,     1,     3,     3,     3,
       7,    10,    10,     2,     1,     1,     8,     4,     2,     0,
       1,     1,     0,     3,     2,     1,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     2,     3,     1,     2,     3,
       1,     3,     1,     2,     3,     3,     4,     4,     4,     3,
       5,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     3,     2,     1,     1,
       3,     0,     3,     1,     2,     3,     1,     5,     0,     2,
       0,     5,     0,     2,     0,     3,     0,     2,     0,     2,
       1,     3,     1,     3,     0,     1,     3,     3,     4,     3,
       3,     4,     3,     4,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     7,     2,     4,     0,     1
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
#line 246 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1842 "yacc_sql.cpp"
    break;

  case 24:
#line 277 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1851 "yacc_sql.cpp"
    break;

  case 25:
#line 283 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1859 "yacc_sql.cpp"
    break;

  case 26:
#line 288 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1867 "yacc_sql.cpp"
    break;

  case 27:
#line 294 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1875 "yacc_sql.cpp"
    break;

  case 28:
#line 300 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1883 "yacc_sql.cpp"
    break;

  case 29:
#line 306 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1891 "yacc_sql.cpp"
    break;

  case 30:
#line 312 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1901 "yacc_sql.cpp"
    break;

  case 31:
#line 319 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1909 "yacc_sql.cpp"
    break;

  case 32:
#line 325 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1919 "yacc_sql.cpp"
    break;

  case 33:
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
#line 1942 "yacc_sql.cpp"
    break;

  case 34:
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
#line 1965 "yacc_sql.cpp"
    break;

  case 35:
#line 375 "yacc_sql.y"
    {
      (yyval.attr_names) = nullptr;
    }
#line 1973 "yacc_sql.cpp"
    break;

  case 36:
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
#line 1987 "yacc_sql.cpp"
    break;

  case 37:
#line 392 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1999 "yacc_sql.cpp"
    break;

  case 38:
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
#line 2019 "yacc_sql.cpp"
    break;

  case 39:
#line 420 "yacc_sql.y"
    {
      (yyval.sql_node) = (yyvsp[0].sql_node);
      (yyval.sql_node)->selection.is_create_table_select_stmt = true;
      (yyval.sql_node)->selection.create_table_select_table_name = (yyvsp[-2].string);
      delete (yyvsp[-2].string);
    }
#line 2030 "yacc_sql.cpp"
    break;

  case 40:
#line 429 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2038 "yacc_sql.cpp"
    break;

  case 41:
#line 433 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2052 "yacc_sql.cpp"
    break;

  case 42:
#line 446 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2065 "yacc_sql.cpp"
    break;

  case 43:
#line 455 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2078 "yacc_sql.cpp"
    break;

  case 44:
#line 466 "yacc_sql.y"
    { (yyval.bools) = true; }
#line 2084 "yacc_sql.cpp"
    break;

  case 45:
#line 467 "yacc_sql.y"
             { (yyval.bools) = true; }
#line 2090 "yacc_sql.cpp"
    break;

  case 46:
#line 468 "yacc_sql.y"
                 { (yyval.bools) = false; }
#line 2096 "yacc_sql.cpp"
    break;

  case 47:
#line 472 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2102 "yacc_sql.cpp"
    break;

  case 48:
#line 475 "yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2108 "yacc_sql.cpp"
    break;

  case 49:
#line 476 "yacc_sql.y"
               { (yyval.number)=DATES; }
#line 2114 "yacc_sql.cpp"
    break;

  case 50:
#line 477 "yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2120 "yacc_sql.cpp"
    break;

  case 51:
#line 478 "yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2126 "yacc_sql.cpp"
    break;

  case 52:
#line 479 "yacc_sql.y"
               { (yyval.number)=TEXTS; }
#line 2132 "yacc_sql.cpp"
    break;

  case 53:
#line 480 "yacc_sql.y"
               { (yyval.number)=NULLS; }
#line 2138 "yacc_sql.cpp"
    break;

  case 54:
#line 484 "yacc_sql.y"
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
#line 2154 "yacc_sql.cpp"
    break;

  case 55:
#line 499 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2162 "yacc_sql.cpp"
    break;

  case 56:
#line 502 "yacc_sql.y"
                              { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2176 "yacc_sql.cpp"
    break;

  case 57:
#line 513 "yacc_sql.y"
                   {
      (yyval.value) = (yyvsp[0].value);
      (yyloc) = (yylsp[0]);
    }
#line 2185 "yacc_sql.cpp"
    break;

  case 58:
#line 517 "yacc_sql.y"
                 {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2194 "yacc_sql.cpp"
    break;

  case 59:
#line 521 "yacc_sql.y"
                {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2203 "yacc_sql.cpp"
    break;

  case 60:
#line 528 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2212 "yacc_sql.cpp"
    break;

  case 61:
#line 532 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2221 "yacc_sql.cpp"
    break;

  case 62:
#line 536 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2231 "yacc_sql.cpp"
    break;

  case 63:
#line 541 "yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_type(NULLS);
      (yyloc) = (yylsp[0]);
    }
#line 2241 "yacc_sql.cpp"
    break;

  case 64:
#line 550 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2255 "yacc_sql.cpp"
    break;

  case 65:
#line 562 "yacc_sql.y"
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
#line 2270 "yacc_sql.cpp"
    break;

  case 66:
#line 576 "yacc_sql.y"
    {
      (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2279 "yacc_sql.cpp"
    break;

  case 67:
#line 581 "yacc_sql.y"
    {
      if ((yyvsp[-2].update_unit_list) == nullptr) {
        (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      } else {
        (yyval.update_unit_list) = (yyvsp[-2].update_unit_list);
      }

      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2293 "yacc_sql.cpp"
    break;

  case 68:
#line 594 "yacc_sql.y"
    {
      (yyval.update_unit) = new UpdateUnit((yyvsp[-2].string), new ValueExpr(*(yyvsp[0].value)));
    }
#line 2301 "yacc_sql.cpp"
    break;

  case 69:
#line 598 "yacc_sql.y"
    {
      (yyval.update_unit) = new UpdateUnit((yyvsp[-2].string), (yyvsp[0].expression));
    }
#line 2309 "yacc_sql.cpp"
    break;

  case 70:
#line 605 "yacc_sql.y"
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
#line 2339 "yacc_sql.cpp"
    break;

  case 71:
#line 631 "yacc_sql.y"
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
#line 2366 "yacc_sql.cpp"
    break;

  case 72:
#line 654 "yacc_sql.y"
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
#line 2398 "yacc_sql.cpp"
    break;

  case 73:
#line 682 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2411 "yacc_sql.cpp"
    break;

  case 74:
#line 694 "yacc_sql.y"
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2419 "yacc_sql.cpp"
    break;

  case 75:
#line 698 "yacc_sql.y"
    {
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2427 "yacc_sql.cpp"
    break;

  case 76:
#line 704 "yacc_sql.y"
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
#line 2454 "yacc_sql.cpp"
    break;

  case 77:
#line 729 "yacc_sql.y"
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
#line 2470 "yacc_sql.cpp"
    break;

  case 78:
#line 743 "yacc_sql.y"
                       {
        (yyval.order_item) = new OrderBy;
        (yyval.order_item)->order_by_attribute = *(yyvsp[-1].rel_attr);
        (yyval.order_item)->order = (yyvsp[0].bools);
        delete (yyvsp[-1].rel_attr);
	}
#line 2481 "yacc_sql.cpp"
    break;

  case 79:
#line 752 "yacc_sql.y"
                    {
		(yyval.bools) = 0;
	}
#line 2489 "yacc_sql.cpp"
    break;

  case 80:
#line 755 "yacc_sql.y"
              {
		(yyval.bools) = 0;
	}
#line 2497 "yacc_sql.cpp"
    break;

  case 81:
#line 758 "yacc_sql.y"
               {
		(yyval.bools) = 1;
	}
#line 2505 "yacc_sql.cpp"
    break;

  case 82:
#line 765 "yacc_sql.y"
        {
	    (yyval.order_item_list) = nullptr;
	}
#line 2513 "yacc_sql.cpp"
    break;

  case 83:
#line 769 "yacc_sql.y"
        {
        if((yyvsp[0].order_item_list) != nullptr) {
            (yyval.order_item_list) = (yyvsp[0].order_item_list);
        } else {
            (yyval.order_item_list) = new std::vector<OrderBy>;
        }
        (yyval.order_item_list)->emplace_back(*(yyvsp[-1].order_item));
        delete (yyvsp[-1].order_item);
	}
#line 2527 "yacc_sql.cpp"
    break;

  case 84:
#line 782 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2538 "yacc_sql.cpp"
    break;

  case 85:
#line 792 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2547 "yacc_sql.cpp"
    break;

  case 86:
#line 797 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2560 "yacc_sql.cpp"
    break;

  case 87:
#line 807 "yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2568 "yacc_sql.cpp"
    break;

  case 88:
#line 810 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2576 "yacc_sql.cpp"
    break;

  case 89:
#line 813 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2584 "yacc_sql.cpp"
    break;

  case 90:
#line 816 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2592 "yacc_sql.cpp"
    break;

  case 91:
#line 819 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2601 "yacc_sql.cpp"
    break;

  case 92:
#line 823 "yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2609 "yacc_sql.cpp"
    break;

  case 93:
#line 826 "yacc_sql.y"
                     {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2619 "yacc_sql.cpp"
    break;

  case 94:
#line 831 "yacc_sql.y"
               {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      (yyval.expression)->set_name((yyvsp[0].rel_attr)->name());
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 95:
#line 835 "yacc_sql.y"
                  {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-1].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2637 "yacc_sql.cpp"
    break;

  case 96:
#line 839 "yacc_sql.y"
                     {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-2].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2646 "yacc_sql.cpp"
    break;

  case 97:
#line 843 "yacc_sql.y"
                {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2655 "yacc_sql.cpp"
    break;

  case 98:
#line 847 "yacc_sql.y"
                   {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2664 "yacc_sql.cpp"
    break;

  case 99:
#line 851 "yacc_sql.y"
                      {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2673 "yacc_sql.cpp"
    break;

  case 100:
#line 855 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2682 "yacc_sql.cpp"
    break;

  case 101:
#line 859 "yacc_sql.y"
                           {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2691 "yacc_sql.cpp"
    break;

  case 102:
#line 864 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2700 "yacc_sql.cpp"
    break;

  case 103:
#line 869 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2709 "yacc_sql.cpp"
    break;

  case 104:
#line 874 "yacc_sql.y"
    {
      (yyval.expression)=(yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 105:
#line 879 "yacc_sql.y"
    {
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = (yyvsp[-2].string);
      attr->attribute_name = "*";
      (yyval.expression) = new StarExprSqlNode(attr);
      free((yyvsp[-2].string));
    }
#line 2730 "yacc_sql.cpp"
    break;

  case 106:
#line 889 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, *(yyvsp[-1].func_args));
    }
#line 2738 "yacc_sql.cpp"
    break;

  case 107:
#line 892 "yacc_sql.y"
                                     {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, *(yyvsp[-1].func_args));
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 108:
#line 895 "yacc_sql.y"
                                                 {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, *(yyvsp[-1].func_args));
    }
#line 2754 "yacc_sql.cpp"
    break;

  case 109:
#line 905 "yacc_sql.y"
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
#line 2774 "yacc_sql.cpp"
    break;

  case 110:
#line 921 "yacc_sql.y"
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
#line 2817 "yacc_sql.cpp"
    break;

  case 111:
#line 963 "yacc_sql.y"
  {
    (yyval.rel_attr_list)=nullptr;
  }
#line 2825 "yacc_sql.cpp"
    break;

  case 112:
#line 967 "yacc_sql.y"
  {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    delete (yyvsp[-1].rel_attr);
  }
#line 2839 "yacc_sql.cpp"
    break;

  case 113:
#line 982 "yacc_sql.y"
  {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = "*";
  }
#line 2848 "yacc_sql.cpp"
    break;

  case 114:
#line 987 "yacc_sql.y"
  {
    (yyval.rel_attr)=(yyvsp[0].rel_attr);
  }
#line 2856 "yacc_sql.cpp"
    break;

  case 115:
#line 995 "yacc_sql.y"
    {
       (yyval.agg_func)=MAX_FUNC;
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 116:
#line 999 "yacc_sql.y"
    {
       (yyval.agg_func)=MIN_FUNC;
    }
#line 2872 "yacc_sql.cpp"
    break;

  case 117:
#line 1003 "yacc_sql.y"
    {
       (yyval.agg_func)=AVG_FUNC;
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 118:
#line 1007 "yacc_sql.y"
    {
       (yyval.agg_func)=COUNT_FUNC;
    }
#line 2888 "yacc_sql.cpp"
    break;

  case 119:
#line 1011 "yacc_sql.y"
    {
       (yyval.agg_func)=SUM_FUNC;
    }
#line 2896 "yacc_sql.cpp"
    break;

  case 120:
#line 1018 "yacc_sql.y"
        {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *value_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      free(tmp);
    }
#line 2909 "yacc_sql.cpp"
    break;

  case 121:
#line 1026 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      RelAttrExprSqlNode *attr_expr = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      attr_expr->set_name((yyvsp[0].rel_attr)->name());
      std::unique_ptr<Expression> target(attr_expr);
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2921 "yacc_sql.cpp"
    break;

  case 122:
#line 1036 "yacc_sql.y"
               {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[0].expression));
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2931 "yacc_sql.cpp"
    break;

  case 123:
#line 1041 "yacc_sql.y"
                              {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      ValueExpr *value_expr = new ValueExpr(Value((int)(yyvsp[0].number)));
      std::unique_ptr<Expression> precise(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(precise));
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 124:
#line 1052 "yacc_sql.y"
                         {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *format_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      std::unique_ptr<Expression> format(format_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(format));
    }
#line 2958 "yacc_sql.cpp"
    break;

  case 125:
#line 1065 "yacc_sql.y"
        {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      (yyval.expression_list)->emplace_back(new StarExprSqlNode(attr));
    }
#line 2970 "yacc_sql.cpp"
    break;

  case 126:
#line 1072 "yacc_sql.y"
                {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      StarExprSqlNode *star = new StarExprSqlNode(attr);
      star->set_name((yyvsp[0].string));
      (yyval.expression_list)->emplace_back(star);
    }
#line 2984 "yacc_sql.cpp"
    break;

  case 127:
#line 1081 "yacc_sql.y"
             {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      StarExprSqlNode *star = new StarExprSqlNode(attr);
      star->set_name((yyvsp[0].string));
      (yyval.expression_list)->emplace_back(star);
    }
#line 2998 "yacc_sql.cpp"
    break;

  case 128:
#line 1090 "yacc_sql.y"
                      {
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3007 "yacc_sql.cpp"
    break;

  case 129:
#line 1097 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 3017 "yacc_sql.cpp"
    break;

  case 130:
#line 1102 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3029 "yacc_sql.cpp"
    break;

  case 131:
#line 1113 "yacc_sql.y"
    {
      (yyval.relation_list) = nullptr;
    }
#line 3037 "yacc_sql.cpp"
    break;

  case 132:
#line 1116 "yacc_sql.y"
                                  {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->push_back(std::move(*(yyvsp[-1].single_table)));
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 133:
#line 1129 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 3060 "yacc_sql.cpp"
    break;

  case 134:
#line 1134 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-1].string), (yyvsp[0].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 3070 "yacc_sql.cpp"
    break;

  case 135:
#line 1140 "yacc_sql.y"
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-2].string), (yyvsp[0].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 3080 "yacc_sql.cpp"
    break;

  case 136:
#line 1149 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode((yyvsp[0].string));
       free((yyvsp[0].string));
    }
#line 3089 "yacc_sql.cpp"
    break;

  case 137:
#line 1154 "yacc_sql.y"
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode(
        new JoinSqlNode(JT_INNER, (yyvsp[-4].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-1].string)), std::move(*(yyvsp[0].condition_list)))
       );
       free((yyvsp[-1].string));
    }
#line 3100 "yacc_sql.cpp"
    break;

  case 138:
#line 1163 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3108 "yacc_sql.cpp"
    break;

  case 139:
#line 1166 "yacc_sql.y"
                        {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3116 "yacc_sql.cpp"
    break;

  case 140:
#line 1174 "yacc_sql.y"
  {
    (yyval.group_by)=nullptr;
  }
#line 3124 "yacc_sql.cpp"
    break;

  case 141:
#line 1179 "yacc_sql.y"
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
#line 3143 "yacc_sql.cpp"
    break;

  case 142:
#line 1196 "yacc_sql.y"
  {
    (yyval.having)=nullptr;
  }
#line 3151 "yacc_sql.cpp"
    break;

  case 143:
#line 1200 "yacc_sql.y"
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
#line 3168 "yacc_sql.cpp"
    break;

  case 144:
#line 1217 "yacc_sql.y"
  {
    (yyval.rel_attr_list)=nullptr;
  }
#line 3176 "yacc_sql.cpp"
    break;

  case 145:
#line 1221 "yacc_sql.y"
  {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(std::move(*(yyvsp[-1].rel_attr)));
  }
#line 3189 "yacc_sql.cpp"
    break;

  case 146:
#line 1234 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3197 "yacc_sql.cpp"
    break;

  case 147:
#line 1237 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 148:
#line 1243 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3213 "yacc_sql.cpp"
    break;

  case 149:
#line 1246 "yacc_sql.y"
                         {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3222 "yacc_sql.cpp"
    break;

  case 150:
#line 1252 "yacc_sql.y"
                  {
     (yyval.condition) = (yyvsp[0].condition);
    }
#line 3230 "yacc_sql.cpp"
    break;

  case 151:
#line 1255 "yacc_sql.y"
                                    {
        std::unique_ptr<Expression> left((yyvsp[-2].condition));
        std::unique_ptr<Expression> right((yyvsp[0].condition));
        (yyval.condition) = new ComparisonExpr(OR_OP, std::move(left), std::move(right));
    }
#line 3240 "yacc_sql.cpp"
    break;

  case 152:
#line 1262 "yacc_sql.y"
               {
        (yyval.condition) = (yyvsp[0].condition);
     }
#line 3248 "yacc_sql.cpp"
    break;

  case 153:
#line 1265 "yacc_sql.y"
                                   {
        std::unique_ptr<Expression> left((yyvsp[-2].condition));
        std::unique_ptr<Expression> right((yyvsp[0].condition));
        (yyval.condition) = new ComparisonExpr(AND_OP, std::move(left), std::move(right));
     }
#line 3258 "yacc_sql.cpp"
    break;

  case 154:
#line 1274 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3266 "yacc_sql.cpp"
    break;

  case 155:
#line 1277 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 3275 "yacc_sql.cpp"
    break;

  case 156:
#line 1281 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 3284 "yacc_sql.cpp"
    break;

  case 157:
#line 1288 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value value = Value();
      value.set_type(NULLS);
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NULL, std::move(left), std::move(right));
    }
#line 3297 "yacc_sql.cpp"
    break;

  case 158:
#line 1297 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      Value value = Value();
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NOT_NULL, std::move(left), std::move(right));
    }
#line 3309 "yacc_sql.cpp"
    break;

  case 159:
#line 1305 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3319 "yacc_sql.cpp"
    break;

  case 160:
#line 1311 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_IN_OP, std::move(left), std::move(right));
    }
#line 3329 "yacc_sql.cpp"
    break;

  case 161:
#line 1317 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_NOT_IN, std::move(left), std::move(right));
    }
#line 3339 "yacc_sql.cpp"
    break;

  case 162:
#line 1323 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_EXISTS_OP, std::move(left), std::move(right));
    }
#line 3349 "yacc_sql.cpp"
    break;

  case 163:
#line 1329 "yacc_sql.y"
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr(SUB_NOT_EXISTS, std::move(left), std::move(right));
    }
#line 3359 "yacc_sql.cpp"
    break;

  case 164:
#line 1335 "yacc_sql.y"
    {
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), nullptr, std::move(right));
    }
#line 3368 "yacc_sql.cpp"
    break;

  case 165:
#line 1342 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3374 "yacc_sql.cpp"
    break;

  case 166:
#line 1343 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3380 "yacc_sql.cpp"
    break;

  case 167:
#line 1344 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3386 "yacc_sql.cpp"
    break;

  case 168:
#line 1345 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3392 "yacc_sql.cpp"
    break;

  case 169:
#line 1346 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3398 "yacc_sql.cpp"
    break;

  case 170:
#line 1347 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3404 "yacc_sql.cpp"
    break;

  case 171:
#line 1348 "yacc_sql.y"
           { (yyval.comp) = LIKES; }
#line 3410 "yacc_sql.cpp"
    break;

  case 172:
#line 1349 "yacc_sql.y"
               { (yyval.comp) = NOT_LIKES; }
#line 3416 "yacc_sql.cpp"
    break;

  case 173:
#line 1354 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3430 "yacc_sql.cpp"
    break;

  case 174:
#line 1367 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3439 "yacc_sql.cpp"
    break;

  case 175:
#line 1375 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3451 "yacc_sql.cpp"
    break;


#line 3455 "yacc_sql.cpp"

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
#line 1387 "yacc_sql.y"

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
