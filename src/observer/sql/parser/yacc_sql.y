
%{

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

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        AS
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        LENGTH
        ROUND
        DATE_FORMAT
        INNER
        JOIN
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        DATE_T
        MIN
        MAX
        AVG
        COUNT
        SUM
        STRING_T
        FLOAT_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        LIKE
        NOT_LIKE
        IS
        NOT
        NULLABLE
        NULL_T
        UNIQUE
		ORDER
		BY
		ASC
        EQ
        LT
        GT
        LE
        GE
        NE
        IN
        EXISTS

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
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
  AggregationFuncSqlNode *          agg_func_call;
  enum AggFuncType                  agg_func;
  std::vector<AggregationFuncSqlNode> * agg_func_call_list;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <value>               unsigned_value
%type <number>              number
%type <comp>                comp_op
%type <general_relation_sql_node> general_rel
%type <rel_attr>            rel_attr
%type <attr_names>          attr_name_list
%type <bools>               order
%type <order_item>          order_item
%type <order_item_list>     order_item_list
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <bools>               nullable;
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <condition_list>      join_condition
%type <expression_list>     select_attr
%type <agg_func_call>       agg_func_call;
%type <agg_func>            agg_func
%type <agg_func_call_list>  agg_func_call_list;
%type <single_table>        single_table
%type <relation_list>       rel_list
%type <field>               agg_field
%type <field_list>          agg_field_list;
%type <expression>          expression
%type <func_args>           length_args
%type <func_args>           round_args
%type <func_args>           date_format_args
%type <expression>          func_expr
%type <expression>          sub_query_expr
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE ID attr_name_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;

      std::vector<std::string> *attribute_names = $8;
      if (attribute_names != nullptr) {
         create_index.attribute_names.swap(*attribute_names);
      }
      create_index.attribute_names.emplace_back($7);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());

      create_index.unique = false;
      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE ID attr_name_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.relation_name = $6;

      std::vector<std::string> *attribute_names = $9;
      if (attribute_names != nullptr) {
          create_index.attribute_names.swap(*attribute_names);
      }
      create_index.attribute_names.emplace_back($8);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());

      create_index.unique = true;
      free($4);
      free($6);
      free($8);
    }
    ;

attr_name_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA ID attr_name_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<std::string>;
      }
      $$->emplace_back($2);
      delete $2;
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->null = $6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      $$->null = $3;
      free($1);
    }
    ;

nullable:
    { $$ = true; }
    | NULL_T { $$ = true; }
    | NOT NULL_T { $$ = false; }
    ;

number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | DATE_T   { $$=DATES; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | TEXT_T   { $$=TEXTS; }
    | NULL_T   { $$=NULLS; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    unsigned_value {
      $$ = $1;
      @$ = @1;
    }
    | '-' NUMBER {
      $$ = new Value(-(int)$2);
      @$ = @2;
    }
    | '-' FLOAT {
      $$ = new Value(-(float)$2);
      @$ = @2;
    }
    ;

unsigned_value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |NULL_T {
      $$ = new Value();
      $$->set_type(NULLS);
      @$ = @1;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_name = $4;
      $$->update.value = *$6;
      if ($7 != nullptr) {
        $$->update.conditions.swap(*$7);
        delete $7;
      }
      free($2);
      free($4);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr FROM single_table rel_list where
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.select_expressions.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back(std::move(*$4));
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }
      free($4);
    }
    | SELECT select_attr FROM general_rel INNER JOIN ID join_condition where
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.select_expressions.swap(*$2);
        delete $2;
      }

      $$->selection.join_relation = new JoinSqlNode(JT_INNER, $4, new GeneralRelationSqlNode($7), std::move(*$8));
      delete $8;

      if ($9 != nullptr) {
        $$->selection.conditions.swap(*$9);
        delete $9;
      }
      free($7);
    }
    | SELECT select_attr FROM single_table rel_list where ORDER BY order_item order_item_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.select_expressions.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {
        $$->selection.relations.swap(*$5);
        delete $5;
      }
      $$->selection.relations.push_back(std::move(*$4));
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      std::vector<OrderBy> *order_by_attrs = $10;
      if(order_by_attrs != nullptr) {
        $$->selection.order_by.swap(*order_by_attrs);
      }
      $$->selection.order_by.emplace_back(*$9);
      std::reverse($$->selection.order_by.begin(), $$->selection.order_by.end());
      delete $9;

      if ($6 != nullptr) {
        $$->selection.conditions.swap(*$6);
        delete $6;
      }
      free($4);
    }
    | SELECT agg_func_call agg_func_call_list FROM single_table rel_list where
    {
        $$ = new ParsedSqlNode(SCF_SELECT);

        if($3 != nullptr) {
            $$->selection.agg_funcs.swap(*$3);
            delete $3;
        }

        $$->selection.agg_funcs.push_back(*$2);
        delete $2;

        if ($6 != nullptr) {
            $$->selection.relations.swap(*$6);
            delete $6;
        }
        $$->selection.relations.push_back(*$5);
        std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

         if ($7 != nullptr) {
            $$->selection.conditions.swap(*$7);
            delete $7;
         }
         free($5);
    }
    | SELECT expression_list
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        std::reverse($2->begin(), $2->end());
        $$->selection.select_expressions.swap(*$2);
        delete $2;
      }
    }
    ;

sub_query_expr:
    LBRACE SELECT select_attr FROM single_table rel_list where RBRACE
    {
      SelectSqlNode* select_sql_node = new SelectSqlNode();
      if ($3 != nullptr) {
        select_sql_node->select_expressions.swap(*$3);
        delete $3;
      }
      if ($6 != nullptr) {
        select_sql_node->relations.swap(*$6);
        delete $6;
      }
      select_sql_node->relations.push_back(std::move(*$5));
      std::reverse(select_sql_node->relations.begin(), select_sql_node->relations.end());

      if ($7 != nullptr) {
        select_sql_node->conditions.swap(*$7);
        delete $7;
      }

      $$ = new SubQueryExpression(select_sql_node);
      free($5);
    }

order_item:
	rel_attr order {
        $$ = new OrderBy;
        $$->order_by_attribute = *$1;
        $$->order = $2;
        delete $1;
	}
	;

order:
	/* empty */ {
		$$ = 0;
	}
	| ASC {
		$$ = 0;
	}
	| DESC {
		$$ = 1;
	}
	;

order_item_list:
	/* empty */
	{
	    $$ = nullptr;
	}
	| COMMA order_item order_item_list
	{
        if($3 != nullptr) {
            $$ = $3;
        } else {
            $$ = new std::vector<OrderBy>;
        }
        $$->emplace_back(*$2);
        delete $2;
	}
	;



agg_func_call_list:
        /* empty */
        {
          $$ = nullptr;
        }
        | COMMA agg_func_call agg_func_call_list {
          if ($3 != nullptr) {
            $$ = $3;
          } else {
            $$ = new std::vector<AggregationFuncSqlNode>;
          }

          $$->push_back(*$2);

          delete $2;
        }


agg_func_call:
    agg_func LBRACE RBRACE
    {
      $$ = new AggregationFuncSqlNode;
      $$->func = $1;
      $$->attr.attribute_name = "";
    }
    | agg_func LBRACE agg_field agg_field_list RBRACE
    {
        $$ = new AggregationFuncSqlNode;
        $$->func = $1;
        if($4 == nullptr) {
          $$->attr.attribute_name = $3->name;
        }else {
          $$->attr.attribute_name = "";
          delete($4);
        }
        delete($3);
    }
    ;


agg_field_list:
  // empty
  {
    $$=nullptr;
  }
  | COMMA agg_field agg_field_list
  {
    if ($3 != nullptr) {
      $$ = $3;
    } else {
      $$ = new std::vector<std::string>;
    }
    $$->push_back($2->name);
    delete($2);
  }
  ;

agg_field:
  '*'
  {
    $$ = new AggField;
    $$->name = "*";
  }
  | ID
  {
    $$ = new AggField;
    $$->name = $1;
    free($1);
  }
  ;



agg_func:
    MAX
    {
       $$=MAX_FUNC;
    }
    | MIN
    {
       $$=MIN_FUNC;
    }
    | AVG
    {
       $$=AVG_FUNC;
    }
    | COUNT
    {
       $$=COUNT_FUNC;
    }
    | SUM
    {
       $$=SUM_FUNC;
    }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | unsigned_value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      $$ = new RelAttrExprSqlNode($1);
      $$->set_name($1->name());
    }
    | rel_attr ID {
      $$ = new RelAttrExprSqlNode($1, $2);
      $$->set_name($2);
    }
    | rel_attr AS ID {
      $$ = new RelAttrExprSqlNode($1, $3);
      $$->set_name($3);
    }
    | func_expr {
      $$ = $1;
      $$->set_name(token_name(sql_string, &@$));
    }
    | func_expr ID {
      $$ = $1;
      $$->set_name($2);
    }
    | func_expr AS ID {
      $$ = $1;
      $$->set_name($3);
    }
    | sub_query_expr {
      $$ = $1;
      $$->set_name(token_name(sql_string, &@$));
    }
    | sub_query_expr AS ID {
      $$ = $1;
      $$->set_name($3);
    }
    ;

func_expr:
    LENGTH LBRACE length_args RBRACE {
      $$ = new FuncExpr(FuncExpr::FuncType::LENGTH, *$3);
    }
    | ROUND LBRACE round_args RBRACE {
      $$ = new FuncExpr(FuncExpr::FuncType::ROUND, *$3);
    }
    | DATE_FORMAT LBRACE date_format_args RBRACE {
      $$ = new FuncExpr(FuncExpr::FuncType::DATE_FORMAT, *$3);
    }
    ;

length_args:
    SSS {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr($1,1,strlen($1)-2);
      ValueExpr *value_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target(value_expr);
      $$->emplace_back(std::move(target));
      free(tmp);
    }
    | rel_attr {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      RelAttrExprSqlNode *attr_expr = new RelAttrExprSqlNode($1);
      attr_expr->set_name($1->name());
      std::unique_ptr<Expression> target(attr_expr);
      $$->emplace_back(std::move(target));
    }
    ;

round_args:
    expression {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target($1);
      $$->emplace_back(std::move(target));
    }
    | expression COMMA NUMBER {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      std::unique_ptr<Expression> target($1);
      ValueExpr *value_expr = new ValueExpr(Value((int)$3));
      std::unique_ptr<Expression> precise(value_expr);
      $$->emplace_back(std::move(target));
      $$->emplace_back(std::move(precise));
    }
    ;

date_format_args:
    expression COMMA SSS {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      char *tmp = common::substr($3,1,strlen($3)-2);
      ValueExpr *format_expr = new ValueExpr(Value(tmp));
      std::unique_ptr<Expression> target($1);
      std::unique_ptr<Expression> format(format_expr);
      $$->emplace_back(std::move(target));
      $$->emplace_back(std::move(format));
    }
    ;
    
 
select_attr:
    '*' {
      $$ = new std::vector<Expression *>;
      RelAttrSqlNode *attr = new RelAttrSqlNode;
      attr->relation_name  = "";
      attr->attribute_name = "*";
      $$->emplace_back(new RelAttrExprSqlNode(attr));
    }
    | expression_list {
      std::reverse($1->begin(), $1->end());
      $$ = $1;
    }
    ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA single_table rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelationSqlNode>;
      }

      $$->push_back(std::move(*$2));
    }
    ;
 
single_table:
    ID
    {
      $$ = new RelationSqlNode($1);
      free($1);
    }
    | ID ID
    {
      $$ = new RelationSqlNode($1, $2);
      free($1);
      free($2);
    }
    | ID AS ID
    {
      $$ = new RelationSqlNode($1, $3);
      free($1);
      free($3);
    }
    ;
general_rel:
    /* primitive table*/
    ID
    {
       $$ = new GeneralRelationSqlNode($1);
       free($1);
    }
    | general_rel INNER JOIN ID join_condition
    {
       $$ = new GeneralRelationSqlNode(
        new JoinSqlNode(JT_INNER, $1, new GeneralRelationSqlNode($4), std::move(*$5))
       );
       free($4);
    }
    ;
join_condition:
    /* empty */
    {
      $$ = nullptr;
    }
    | ON condition_list {
      $$ = $2;
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ComparisonExpr *>;
      $$->emplace_back($1);
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back($1);
    }
    ;
condition:
    expression IS NULL_T
    {
      std::unique_ptr<Expression> left($1);
      Value value = Value();
      value.set_type(NULLS);
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      $$ = new ComparisonExpr(IS_LEFT_NULL, std::move(left), std::move(right));
    }
    | expression IS NOT NULL_T
    {
      std::unique_ptr<Expression> left($1);
      Value value = Value();
      ValueExpr *value_expr = new ValueExpr(value);
      std::unique_ptr<Expression> right(value_expr);
      $$ = new ComparisonExpr(IS_LEFT_NOT_NULL, std::move(left), std::move(right));
    }
    | expression comp_op expression
    {
      std::unique_ptr<Expression> left($1);
      std::unique_ptr<Expression> right($3);
      $$ = new ComparisonExpr($2, std::move(left), std::move(right));
    }
    | comp_op expression
    {
      std::unique_ptr<Expression> right($2);
      $$ = new ComparisonExpr($1, nullptr, std::move(right));
    }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKES; }
    | NOT_LIKE { $$ = NOT_LIKES; }
    | IN { $$ = IN_OP; }
    | NOT IN { $$ = NOT_IN; }
    | EXISTS { $$ = EXISTS_OP; }
    | NOT EXISTS { $$ = NOT_EXISTS; }
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
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
