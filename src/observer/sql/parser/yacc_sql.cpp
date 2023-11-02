/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y" /* yacc.c:337  */


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


#line 114 "yacc_sql.cpp" /* yacc.c:337  */
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

/* In a future release of Bison, this section will be replaced
   by #include "yacc_sql.hpp".  */
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
    SET = 302,
    ON = 303,
    LOAD = 304,
    DATA = 305,
    INFILE = 306,
    EXPLAIN = 307,
    LIKE = 308,
    NOT_LIKE = 309,
    IS = 310,
    NOT = 311,
    NULLABLE = 312,
    NULL_T = 313,
    UNIQUE = 314,
    ORDER = 315,
    BY = 316,
    ASC = 317,
    EQ = 318,
    LT = 319,
    GT = 320,
    LE = 321,
    GE = 322,
    NE = 323,
    NUMBER = 324,
    FLOAT = 325,
    ID = 326,
    SSS = 327,
    UMINUS = 328
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 125 "yacc_sql.y" /* yacc.c:352  */

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

#line 264 "yacc_sql.cpp" /* yacc.c:352  */
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

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   269

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  148
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  262

#define YYUNDEFTOK  2
#define YYMAXUTOK   328

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   259,   265,   270,   276,   282,   288,   294,
     301,   307,   315,   334,   357,   360,   373,   383,   402,   405,
     418,   427,   439,   440,   441,   445,   448,   449,   450,   451,
     452,   453,   456,   472,   475,   486,   490,   494,   501,   505,
     509,   514,   522,   534,   548,   553,   566,   573,   593,   610,
     638,   650,   659,   662,   665,   672,   675,   688,   698,   703,
     714,   717,   720,   723,   726,   730,   733,   738,   742,   746,
     750,   754,   758,   762,   767,   772,   780,   783,   786,   795,
     811,   854,   857,   872,   877,   885,   889,   893,   897,   901,
     909,   917,   927,   932,   943,   956,   963,   970,   975,   986,
     989,  1001,  1006,  1012,  1021,  1026,  1036,  1039,  1045,  1048,
    1054,  1057,  1061,  1067,  1076,  1084,  1093,  1094,  1095,  1096,
    1097,  1098,  1099,  1100,  1104,  1117,  1125,  1135,  1136
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
  "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EXPLAIN",
  "LIKE", "NOT_LIKE", "IS", "NOT", "NULLABLE", "NULL_T", "UNIQUE", "ORDER",
  "BY", "ASC", "EQ", "LT", "GT", "LE", "GE", "NE", "NUMBER", "FLOAT", "ID",
  "SSS", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "attr_name_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list", "value",
  "unsigned_value", "delete_stmt", "update_stmt", "update_list",
  "update_unit", "select_stmt", "order_item", "order", "order_item_list",
  "calc_stmt", "expression_list", "expression", "func_expr", "agg_expr",
  "agg_field_list", "agg_field", "agg_func", "length_args", "round_args",
  "date_format_args", "select_attr", "rel_attr", "rel_list",
  "single_table", "general_rel", "join_condition", "where",
  "condition_list", "condition", "comp_op", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,    43,    45,    42,    47,   328
};
# endif

#define YYPACT_NINF -217

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-217)))

#define YYTABLE_NINF -126

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     178,    12,    24,   108,    55,   -41,    33,  -217,     2,    18,
      -7,  -217,  -217,  -217,  -217,  -217,    25,    19,   178,    98,
     101,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,    34,    41,    97,    43,    44,    84,    94,    95,   108,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,  -217,    82,  -217,
     108,  -217,  -217,     7,     3,     4,   105,     5,  -217,    88,
      91,  -217,  -217,    66,    73,   100,    85,    99,  -217,  -217,
    -217,  -217,   126,   107,    89,  -217,   111,   -45,   108,   108,
     -18,    90,  -217,   108,   108,   108,   108,   108,    92,  -217,
      93,  -217,   -10,    96,  -217,   102,   113,   117,   104,    64,
     109,   114,   115,   120,   119,  -217,   141,  -217,    27,   146,
      35,   147,  -217,  -217,  -217,   -26,   -26,  -217,  -217,  -217,
    -217,  -217,  -217,   151,  -217,  -217,     1,   162,   158,   168,
     108,  -217,   129,    -3,  -217,    15,  -217,  -217,   165,   116,
     183,   170,   138,  -217,  -217,   150,  -217,   154,  -217,   -46,
     186,   149,  -217,   157,   117,   214,    64,   148,  -217,   185,
      64,   104,  -217,  -217,  -217,   225,  -217,  -217,  -217,  -217,
    -217,  -217,    -5,   114,   209,   163,   212,  -217,  -217,   151,
    -217,  -217,     6,   162,   176,   166,   213,  -217,  -217,    36,
    -217,  -217,  -217,  -217,  -217,  -217,   108,   108,  -217,  -217,
     169,   172,   181,  -217,  -217,   183,  -217,   217,   173,  -217,
    -217,   182,   197,    64,   222,   189,  -217,   -38,  -217,  -217,
    -217,   224,  -217,  -217,   179,   227,   217,   184,   108,    -2,
     213,  -217,  -217,    39,   217,  -217,   228,   229,    17,  -217,
    -217,  -217,  -217,  -217,  -217,   184,  -217,  -217,  -217,  -217,
     229,  -217
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
     147,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     106,   105,   107,   108,   109,    61,    58,    59,   117,    60,
       0,    86,    77,    78,    90,    93,     0,    87,   115,    70,
       0,    31,    30,     0,     0,     0,     0,     0,   145,     1,
     148,     2,     0,     0,     0,    29,     0,     0,     0,     0,
       0,     0,    85,     0,     0,     0,     0,     0,     0,    91,
       0,    94,     0,     0,    88,     0,     0,   128,     0,     0,
       0,     0,     0,     0,     0,   110,     0,   111,   112,     0,
       0,     0,    84,   118,    79,    80,    81,    82,    83,    92,
      95,    99,   103,   101,   104,    89,   121,   119,     0,     0,
     130,    62,     0,   128,    64,     0,   146,    55,     0,     0,
      38,     0,     0,    36,    96,     0,    97,     0,    98,     0,
       0,     0,   122,     0,   128,     0,     0,     0,   129,   131,
       0,     0,    63,    56,    57,     0,    46,    47,    48,    49,
      50,    51,    42,     0,     0,     0,     0,   113,   114,   101,
     100,   123,   121,   119,    67,     0,    53,   142,   143,     0,
     136,   137,   138,   139,   140,   141,     0,   130,    66,    65,
       0,     0,     0,    43,    41,    38,    37,    34,     0,   102,
     120,     0,   126,     0,     0,     0,   133,   135,   132,   144,
      45,     0,    44,    39,     0,     0,    34,     0,   130,   128,
      53,    52,   134,    42,    34,    32,     0,    75,    72,   127,
      68,    54,    40,    35,    33,     0,    69,    74,    73,    71,
      75,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -217,  -217,   231,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,  -216,  -217,  -217,    38,    74,    13,  -217,
    -217,  -217,    20,  -153,  -107,  -217,  -217,  -217,    87,  -217,
       8,  -217,    -1,  -217,     0,   -49,  -217,  -217,    72,   103,
    -217,  -217,  -217,  -217,  -217,   -86,    71,   106,  -217,  -217,
    -140,  -184,  -217,  -217,  -217,  -217,  -217,  -217
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   235,    31,    32,   184,   150,   214,   231,
     182,    33,   224,   146,    61,    34,    35,   143,   144,    36,
     247,   259,   256,    37,    62,    63,    64,    65,   160,   133,
      66,   116,   119,   121,    70,    67,   164,   137,   138,   239,
     141,   168,   169,   206,    38,    39,    40,    81
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      90,   117,   147,   172,    69,   161,   122,    98,   100,   103,
     161,    92,  -125,   196,   131,  -124,   134,   208,   211,    41,
     246,    42,   171,   228,   194,    58,    58,   115,   253,   132,
      71,    44,    93,    45,   257,    94,    95,    96,    97,   118,
     120,    72,   140,   140,    73,   125,   126,   127,   128,    96,
      97,   212,   155,   213,   249,    94,    95,    96,    97,   147,
     157,    58,    74,   147,    75,   132,    46,    47,    48,    77,
     240,    43,   162,   134,    99,   101,   104,   162,    49,   258,
      94,    95,    96,    97,   173,   174,    50,    51,    52,    53,
      54,   167,   225,   124,   226,   212,    76,   213,    79,   250,
      94,    95,    96,    97,    80,    82,    84,    87,    94,    95,
      96,    97,    83,    55,    85,    86,   147,    88,    89,    46,
      47,    48,    55,    91,    56,    57,    58,    59,   102,    60,
      68,    49,  -116,    56,    57,   105,    59,   106,   145,    50,
      51,    52,    53,    54,   107,   176,   177,   108,   109,   111,
     110,   248,   178,   179,   180,   112,   139,   227,   167,   114,
     113,   123,   140,   129,   130,   154,    55,   135,   152,   248,
     156,   158,   165,   136,   181,   142,   159,    56,    57,    58,
      59,   148,    60,     1,     2,   149,   151,   163,     3,   167,
     153,   166,   170,   185,     4,     5,     6,     7,     8,     9,
      10,   197,   198,   199,    11,    12,    13,   175,   183,   186,
     190,   200,   201,   202,   203,   204,   205,    14,    15,   187,
     191,    94,    95,    96,    97,    16,   188,    17,   192,   195,
      18,   207,   210,   216,   217,   218,   221,   222,   223,   232,
     229,   230,   234,   237,   236,   238,   241,   242,   243,    78,
     244,   245,   254,   233,   255,    58,   252,   215,   209,   261,
     251,   219,   189,   260,   220,     0,     0,     0,     0,   193
};

static const yytype_int16 yycheck[] =
{
      49,    87,   109,   143,     4,     4,    24,     4,     4,     4,
       4,    60,    14,   166,    24,    14,   102,   170,    23,     7,
     236,     9,    25,   207,   164,    71,    71,    72,   244,    75,
      71,     7,    25,     9,    17,    73,    74,    75,    76,    88,
      89,     8,    45,    45,    42,    94,    95,    96,    97,    75,
      76,    56,    25,    58,   238,    73,    74,    75,    76,   166,
      25,    71,    44,   170,    71,    75,    11,    12,    13,    50,
     223,    59,    71,   159,    71,    71,    71,    71,    23,    62,
      73,    74,    75,    76,    69,    70,    31,    32,    33,    34,
      35,   140,    56,    93,    58,    56,    71,    58,     0,   239,
      73,    74,    75,    76,     3,    71,     9,    23,    73,    74,
      75,    76,    71,    58,    71,    71,   223,    23,    23,    11,
      12,    13,    58,    41,    69,    70,    71,    72,    23,    74,
      75,    23,    44,    69,    70,    44,    72,    71,    74,    31,
      32,    33,    34,    35,    71,    29,    30,    47,    63,    23,
      51,   237,    36,    37,    38,    48,    43,   206,   207,    48,
      71,    71,    45,    71,    71,    24,    58,    71,    48,   255,
      24,    24,    14,    71,    58,    71,    25,    69,    70,    71,
      72,    72,    74,     5,     6,    71,    71,    25,    10,   238,
      71,    23,    63,    23,    16,    17,    18,    19,    20,    21,
      22,    53,    54,    55,    26,    27,    28,    42,    25,    71,
      24,    63,    64,    65,    66,    67,    68,    39,    40,    69,
      71,    73,    74,    75,    76,    47,    72,    49,    71,    15,
      52,    46,     7,    24,    71,    23,    60,    71,    25,    58,
      71,    69,    25,    61,    71,    48,    24,    58,    24,    18,
      71,    24,    24,   215,    25,    71,   243,   183,   171,   260,
     240,   189,   159,   255,   193,    -1,    -1,    -1,    -1,   163
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    10,    16,    17,    18,    19,    20,    21,
      22,    26,    27,    28,    39,    40,    47,    49,    52,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    92,    93,    99,   103,   104,   107,   111,   132,   133,
     134,     7,     9,    59,     7,     9,    11,    12,    13,    23,
      31,    32,    33,    34,    35,    58,    69,    70,    71,    72,
      74,   102,   112,   113,   114,   115,   118,   123,    75,   112,
     122,    71,     8,    42,    44,    71,    71,    50,    80,     0,
       3,   135,    71,    71,     9,    71,    71,    23,    23,    23,
     113,    41,   113,    25,    73,    74,    75,    76,     4,    71,
       4,    71,    23,     4,    71,    44,    71,    71,    47,    63,
      51,    23,    48,    71,    48,    72,   119,   123,   113,   120,
     113,   121,    24,    71,   112,   113,   113,   113,   113,    71,
      71,    24,    75,   117,   123,    71,    71,   125,   126,    43,
      45,   128,    71,   105,   106,    74,   101,   102,    72,    71,
      95,    71,    48,    71,    24,    25,    24,    25,    24,    25,
     116,     4,    71,    25,   124,    14,    23,   113,   129,   130,
      63,    25,   128,    69,    70,    42,    29,    30,    36,    37,
      38,    58,    98,    25,    94,    23,    71,    69,    72,   117,
      24,    71,    71,   125,   128,    15,   101,    53,    54,    55,
      63,    64,    65,    66,    67,    68,   131,    46,   101,   106,
       7,    23,    56,    58,    96,    95,    24,    71,    23,   116,
     124,    60,    71,    25,   100,    56,    58,   113,   129,    71,
      69,    97,    58,    94,    25,    91,    71,    61,    48,   127,
     101,    24,    58,    24,    71,    24,    91,   108,   123,   129,
     128,   100,    96,    91,    24,    25,   110,    17,    62,   109,
     108,   110
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    90,    91,    91,    92,    93,    94,    94,
      95,    95,    96,    96,    96,    97,    98,    98,    98,    98,
      98,    98,    99,   100,   100,   101,   101,   101,   102,   102,
     102,   102,   103,   104,   105,   105,   106,   107,   107,   107,
     107,   108,   109,   109,   109,   110,   110,   111,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   114,   114,   115,
     115,   116,   116,   117,   117,   118,   118,   118,   118,   118,
     119,   119,   120,   120,   121,   122,   122,   123,   123,   124,
     124,   125,   125,   125,   126,   126,   127,   127,   128,   128,
     129,   129,   129,   130,   130,   130,   131,   131,   131,   131,
     131,   131,   131,   131,   132,   133,   134,   135,   135
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     2,     9,    10,     0,     3,     5,     7,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     8,     0,     3,     1,     2,     2,     1,     1,
       1,     1,     4,     5,     1,     3,     3,     6,     9,    10,
       2,     2,     0,     1,     1,     0,     3,     2,     1,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     2,     3,
       1,     2,     3,     1,     2,     3,     4,     4,     4,     3,
       5,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     3,     0,
       3,     1,     2,     3,     1,     5,     0,     2,     0,     2,
       0,     1,     3,     3,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     7,     2,     4,     0,     1
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
  YYUSE (yytype);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
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
          yyp++;
          yyformat++;
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

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

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

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
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
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
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

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
#line 229 "yacc_sql.y" /* yacc.c:1652  */
    {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1685 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 259 "yacc_sql.y" /* yacc.c:1652  */
    {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1694 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 265 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1702 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 270 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1710 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 276 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1718 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 282 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1726 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 288 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1734 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 294 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1744 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 301 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1752 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 307 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1762 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 316 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1785 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 335 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1808 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 357 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.attr_names) = nullptr;
    }
#line 1816 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 361 "yacc_sql.y" /* yacc.c:1652  */
    {
      if ((yyvsp[0].attr_names) != nullptr) {
        (yyval.attr_names) = (yyvsp[0].attr_names);
      } else {
        (yyval.attr_names) = new std::vector<std::string>;
      }
      (yyval.attr_names)->emplace_back((yyvsp[-1].string));
      delete (yyvsp[-1].string);
    }
#line 1830 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 374 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1842 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 384 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1862 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 402 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1870 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 406 "yacc_sql.y" /* yacc.c:1652  */
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1884 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 419 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 1897 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 428 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      (yyval.attr_info)->null = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 1910 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 439 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.bools) = true; }
#line 1916 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 440 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.bools) = true; }
#line 1922 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 441 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.bools) = false; }
#line 1928 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 445 "yacc_sql.y" /* yacc.c:1652  */
    {(yyval.number) = (yyvsp[0].number);}
#line 1934 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 448 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=INTS; }
#line 1940 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 449 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=DATES; }
#line 1946 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 450 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=CHARS; }
#line 1952 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 451 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=FLOATS; }
#line 1958 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 452 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=TEXTS; }
#line 1964 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 453 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.number)=NULLS; }
#line 1970 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 457 "yacc_sql.y" /* yacc.c:1652  */
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
#line 1986 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 472 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value_list) = nullptr;
    }
#line 1994 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 475 "yacc_sql.y" /* yacc.c:1652  */
    { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2008 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 486 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value) = (yyvsp[0].value);
      (yyloc) = (yylsp[0]);
    }
#line 2017 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 490 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value) = new Value(-(int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2026 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 494 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value) = new Value(-(float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2035 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 501 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2044 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 505 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2053 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 509 "yacc_sql.y" /* yacc.c:1652  */
    {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2063 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 514 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.value) = new Value();
      (yyval.value)->set_type(NULLS);
      (yyloc) = (yylsp[0]);
    }
#line 2073 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 523 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2087 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 535 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2102 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 549 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2111 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 554 "yacc_sql.y" /* yacc.c:1652  */
    {
      if ((yyvsp[-2].update_unit_list) == nullptr) {
        (yyval.update_unit_list) = new std::vector<UpdateUnit>;
      } else {
        (yyval.update_unit_list) = (yyvsp[-2].update_unit_list);
      }

      (yyval.update_unit_list)->emplace_back(std::move(*(yyvsp[0].update_unit)));
    }
#line 2125 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 567 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.update_unit) = new UpdateUnit((yyvsp[-2].string), (yyvsp[0].value));
    }
#line 2133 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 574 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2157 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 594 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2178 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 611 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2210 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 639 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[0].expression_list) != nullptr) {
        std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
        (yyval.sql_node)->selection.select_expressions.swap(*(yyvsp[0].expression_list));
        delete (yyvsp[0].expression_list);
      }
    }
#line 2223 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 650 "yacc_sql.y" /* yacc.c:1652  */
    {
        (yyval.order_item) = new OrderBy;
        (yyval.order_item)->order_by_attribute = *(yyvsp[-1].rel_attr);
        (yyval.order_item)->order = (yyvsp[0].bools);
        delete (yyvsp[-1].rel_attr);
	}
#line 2234 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 659 "yacc_sql.y" /* yacc.c:1652  */
    {
		(yyval.bools) = 0;
	}
#line 2242 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 662 "yacc_sql.y" /* yacc.c:1652  */
    {
		(yyval.bools) = 0;
	}
#line 2250 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 665 "yacc_sql.y" /* yacc.c:1652  */
    {
		(yyval.bools) = 1;
	}
#line 2258 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 672 "yacc_sql.y" /* yacc.c:1652  */
    {
	    (yyval.order_item_list) = nullptr;
	}
#line 2266 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 676 "yacc_sql.y" /* yacc.c:1652  */
    {
        if((yyvsp[0].order_item_list) != nullptr) {
            (yyval.order_item_list) = (yyvsp[0].order_item_list);
        } else {
            (yyval.order_item_list) = new std::vector<OrderBy>;
        }
        (yyval.order_item_list)->emplace_back(*(yyvsp[-1].order_item));
        delete (yyvsp[-1].order_item);
	}
#line 2280 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 689 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2291 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 699 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2300 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 704 "yacc_sql.y" /* yacc.c:1652  */
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2313 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 714 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2321 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 717 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2329 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 720 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2337 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 723 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2345 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 726 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2354 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 730 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2362 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 733 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2372 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 738 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      (yyval.expression)->set_name((yyvsp[0].rel_attr)->name());
    }
#line 2381 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 742 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-1].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2390 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 746 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new RelAttrExprSqlNode((yyvsp[-2].rel_attr), (yyvsp[0].string));
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2399 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 750 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = (yyvsp[0].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2408 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 754 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2417 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 758 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = (yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2426 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 763 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression)=(yyvsp[0].expression); 
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2435 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 768 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression)=(yyvsp[-1].expression); 
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2444 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 773 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression)=(yyvsp[-2].expression);
      (yyval.expression)->set_name((yyvsp[0].string));
    }
#line 2453 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 780 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::LENGTH, *(yyvsp[-1].func_args));
    }
#line 2461 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 783 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::ROUND, *(yyvsp[-1].func_args));
    }
#line 2469 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 786 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression) = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, *(yyvsp[-1].func_args));
    }
#line 2477 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 796 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2497 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 812 "yacc_sql.y" /* yacc.c:1652  */
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
#line 2540 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 854 "yacc_sql.y" /* yacc.c:1652  */
    {
    (yyval.rel_attr_list)=nullptr;
  }
#line 2548 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 858 "yacc_sql.y" /* yacc.c:1652  */
    {
    if ((yyvsp[0].rel_attr_list) != nullptr) {
      (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
    } else {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
    }
    (yyval.rel_attr_list)->push_back(*(yyvsp[-1].rel_attr));
    delete (yyvsp[-1].rel_attr);
  }
#line 2562 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 873 "yacc_sql.y" /* yacc.c:1652  */
    {
    (yyval.rel_attr) = new RelAttrSqlNode;
    (yyval.rel_attr)->attribute_name = "*";
  }
#line 2571 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 878 "yacc_sql.y" /* yacc.c:1652  */
    {
    (yyval.rel_attr)=(yyvsp[0].rel_attr); 
  }
#line 2579 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 886 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.agg_func)=MAX_FUNC;
    }
#line 2587 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 890 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.agg_func)=MIN_FUNC;
    }
#line 2595 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 894 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.agg_func)=AVG_FUNC;
    }
#line 2603 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 898 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.agg_func)=COUNT_FUNC;
    }
#line 2611 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 902 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.agg_func)=SUM_FUNC;
    }
#line 2619 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 909 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *value_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      free(tmp);
    }
#line 2632 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 917 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      RelAttrExprSqlNode *attr_expr = new RelAttrExprSqlNode((yyvsp[0].rel_attr));
      attr_expr->set_name((yyvsp[0].rel_attr)->name());
      std::unique_ptr<Expression> target(attr_expr);
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2644 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 927 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[0].expression));
      (yyval.func_args)->emplace_back(std::move(target));
    }
#line 2654 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 932 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      ValueExpr *value_expr = new ValueExpr(Value((int)(yyvsp[0].number)));
      std::unique_ptr<Expression> precise(value_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(precise));
    }
#line 2667 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 943 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.func_args) = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      ValueExpr *format_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target((yyvsp[-2].expression));
      std::unique_ptr<Expression> format(format_expr);
      (yyval.func_args)->emplace_back(std::move(target));
      (yyval.func_args)->emplace_back(std::move(format));
    }
#line 2681 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 115:
#line 956 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.expression_list) = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      (yyval.expression_list)->emplace_back(new RelAttrExprSqlNode(attr));
    }
#line 2693 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 116:
#line 963 "yacc_sql.y" /* yacc.c:1652  */
    {
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2702 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 117:
#line 970 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2712 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 118:
#line 975 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2724 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 119:
#line 986 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.relation_list) = nullptr;
    }
#line 2732 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 120:
#line 989 "yacc_sql.y" /* yacc.c:1652  */
    {
      if ((yyvsp[0].relation_list) != nullptr) {
        (yyval.relation_list) = (yyvsp[0].relation_list);
      } else {
        (yyval.relation_list) = new std::vector<RelationSqlNode>;
      }

      (yyval.relation_list)->push_back(std::move(*(yyvsp[-1].single_table)));
    }
#line 2746 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 121:
#line 1002 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2755 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 122:
#line 1007 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-1].string), (yyvsp[0].string));
      free((yyvsp[-1].string));
      free((yyvsp[0].string));
    }
#line 2765 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 123:
#line 1013 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.single_table) = new RelationSqlNode((yyvsp[-2].string), (yyvsp[0].string));
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2775 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 124:
#line 1022 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode((yyvsp[0].string));
       free((yyvsp[0].string));
    }
#line 2784 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 125:
#line 1027 "yacc_sql.y" /* yacc.c:1652  */
    {
       (yyval.general_relation_sql_node) = new GeneralRelationSqlNode(
        new JoinSqlNode(JT_INNER, (yyvsp[-4].general_relation_sql_node), new GeneralRelationSqlNode((yyvsp[-1].string)), std::move(*(yyvsp[0].condition_list)))
       );
       free((yyvsp[-1].string));
    }
#line 2795 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 126:
#line 1036 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 2803 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 127:
#line 1039 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2811 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 128:
#line 1045 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 2819 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 129:
#line 1048 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2827 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 130:
#line 1054 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = nullptr;
    }
#line 2835 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 131:
#line 1057 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = new std::vector<ComparisonExpr *>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
    }
#line 2844 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 132:
#line 1061 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
    }
#line 2853 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 133:
#line 1068 "yacc_sql.y" /* yacc.c:1652  */
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value value = Value();
      value.set_type(NULLS);
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NULL, std::move(left), std::move(right));
    }
#line 2866 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 134:
#line 1077 "yacc_sql.y" /* yacc.c:1652  */
    {
      std::unique_ptr<Expression> left((yyvsp[-3].expression));
      Value value = Value();
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      (yyval.condition) = new ComparisonExpr(IS_LEFT_NOT_NULL, std::move(left), std::move(right));
    }
#line 2878 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 135:
#line 1085 "yacc_sql.y" /* yacc.c:1652  */
    {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2888 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 136:
#line 1093 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = EQUAL_TO; }
#line 2894 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 137:
#line 1094 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = LESS_THAN; }
#line 2900 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 138:
#line 1095 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = GREAT_THAN; }
#line 2906 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 139:
#line 1096 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = LESS_EQUAL; }
#line 2912 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 140:
#line 1097 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = GREAT_EQUAL; }
#line 2918 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 141:
#line 1098 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = NOT_EQUAL; }
#line 2924 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 142:
#line 1099 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = LIKES; }
#line 2930 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 143:
#line 1100 "yacc_sql.y" /* yacc.c:1652  */
    { (yyval.comp) = NOT_LIKES; }
#line 2936 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 144:
#line 1105 "yacc_sql.y" /* yacc.c:1652  */
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2950 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 145:
#line 1118 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2959 "yacc_sql.cpp" /* yacc.c:1652  */
    break;

  case 146:
#line 1126 "yacc_sql.y" /* yacc.c:1652  */
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2971 "yacc_sql.cpp" /* yacc.c:1652  */
    break;


#line 2975 "yacc_sql.cpp" /* yacc.c:1652  */
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
                  yystos[*yyssp], yyvsp, yylsp, sql_string, sql_result, scanner);
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
#line 1138 "yacc_sql.y" /* yacc.c:1918  */

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
