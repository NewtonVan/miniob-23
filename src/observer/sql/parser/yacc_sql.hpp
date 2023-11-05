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

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
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
    SEMICOLON = 258,               /* SEMICOLON  */
    AS = 259,                      /* AS  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    TABLE = 262,                   /* TABLE  */
    TABLES = 263,                  /* TABLES  */
    INDEX = 264,                   /* INDEX  */
    CALC = 265,                    /* CALC  */
    LENGTH = 266,                  /* LENGTH  */
    ROUND = 267,                   /* ROUND  */
    DATE_FORMAT = 268,             /* DATE_FORMAT  */
    INNER = 269,                   /* INNER  */
    JOIN = 270,                    /* JOIN  */
    SELECT = 271,                  /* SELECT  */
    DESC = 272,                    /* DESC  */
    SHOW = 273,                    /* SHOW  */
    SYNC = 274,                    /* SYNC  */
    INSERT = 275,                  /* INSERT  */
    DELETE = 276,                  /* DELETE  */
    UPDATE = 277,                  /* UPDATE  */
    LBRACE = 278,                  /* LBRACE  */
    RBRACE = 279,                  /* RBRACE  */
    COMMA = 280,                   /* COMMA  */
    TRX_BEGIN = 281,               /* TRX_BEGIN  */
    TRX_COMMIT = 282,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 283,            /* TRX_ROLLBACK  */
    INT_T = 284,                   /* INT_T  */
    DATE_T = 285,                  /* DATE_T  */
    MIN = 286,                     /* MIN  */
    MAX = 287,                     /* MAX  */
    AVG = 288,                     /* AVG  */
    COUNT = 289,                   /* COUNT  */
    SUM = 290,                     /* SUM  */
    STRING_T = 291,                /* STRING_T  */
    FLOAT_T = 292,                 /* FLOAT_T  */
    TEXT_T = 293,                  /* TEXT_T  */
    HELP = 294,                    /* HELP  */
    EXIT = 295,                    /* EXIT  */
    DOT = 296,                     /* DOT  */
    INTO = 297,                    /* INTO  */
    VALUES = 298,                  /* VALUES  */
    FROM = 299,                    /* FROM  */
    WHERE = 300,                   /* WHERE  */
    AND = 301,                     /* AND  */
    OR = 302,                      /* OR  */
    SET = 303,                     /* SET  */
    ON = 304,                      /* ON  */
    LOAD = 305,                    /* LOAD  */
    DATA = 306,                    /* DATA  */
    INFILE = 307,                  /* INFILE  */
    EXPLAIN = 308,                 /* EXPLAIN  */
    LIKE = 309,                    /* LIKE  */
    NOT_LIKE = 310,                /* NOT_LIKE  */
    IS = 311,                      /* IS  */
    NOT = 312,                     /* NOT  */
    NULLABLE = 313,                /* NULLABLE  */
    NULL_T = 314,                  /* NULL_T  */
    UNIQUE = 315,                  /* UNIQUE  */
    ORDER = 316,                   /* ORDER  */
    BY = 317,                      /* BY  */
    ASC = 318,                     /* ASC  */
    EQ = 319,                      /* EQ  */
    LT = 320,                      /* LT  */
    GT = 321,                      /* GT  */
    LE = 322,                      /* LE  */
    GE = 323,                      /* GE  */
    NE = 324,                      /* NE  */
    IN = 325,                      /* IN  */
    EXISTS = 326,                  /* EXISTS  */
    NUMBER = 327,                  /* NUMBER  */
    FLOAT = 328,                   /* FLOAT  */
    ID = 329,                      /* ID  */
    SSS = 330,                     /* SSS  */
    UMINUS = 331                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 128 "yacc_sql.y"

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

#line 173 "yacc_sql.hpp"

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
