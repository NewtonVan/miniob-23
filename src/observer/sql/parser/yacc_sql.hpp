/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 125 "yacc_sql.y" /* yacc.c:1921  */

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

#line 162 "yacc_sql.hpp" /* yacc.c:1921  */
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
