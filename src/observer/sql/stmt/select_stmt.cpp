/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/orderby_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/join_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstring>
#include <sys/socket.h>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

// static void wildcard_agg_fields(Table *table, AggFuncType func, std::vector<SelectStmt::agg_field>& fields) {
//   const TableMeta &table_meta = table->table_meta();
//   const int field_num = table_meta.field_num();
//   for (int i = table_meta.sys_field_num(); i < field_num; i++) {
//     fields.push_back(SelectStmt::agg_field(func, Field(table,table_meta.field(i))));
//   }
// }


RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                         tables;
  std::unordered_map<std::string, std::string> alias2tables;
  std::unordered_map<std::string, Table *>     table_map;
  if (select_sql.join_relation != nullptr) {
    std::unique_ptr<GeneralRelationSqlNode> rel = std::make_unique<GeneralRelationSqlNode>(select_sql.join_relation);
    if (RC::SUCCESS != collectJoinTables(db, rel.get(), tables, table_map, alias2tables)) {
      LOG_WARN("invalid argument. tables in join not exist");
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  } else {
    for (size_t i = 0; i < select_sql.relations.size(); i++) {
      if (select_sql.relations[i].relation.empty()) {
        LOG_WARN("invalid argument. relation name is null. index=%d", i);
        return RC::INVALID_ARGUMENT;
      }
      // select_sql.conditions.data()->right_value.data()
      Table *table = db->find_table(select_sql.relations[i].relation.c_str());
      if (nullptr == table) {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), select_sql.relations[i].relation.c_str());
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }

      tables.push_back(table);
      table_map.insert(std::pair<std::string, Table *>(select_sql.relations[i].relation, table));
      if (!select_sql.relations[i].alias.empty()) {
        table_map.insert(std::pair<std::string, Table *>(select_sql.relations[i].alias, table));
        alias2tables.insert(
            std::pair<std::string, std::string>(select_sql.relations[i].alias, select_sql.relations[i].relation));
      } else {
        alias2tables.insert(
            std::pair<std::string, std::string>(select_sql.relations[i].relation, select_sql.relations[i].relation));
      }
    }
  }


  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  bool is_agg = !select_sql.agg_funcs.empty();
  if(is_agg && !select_sql.attributes.empty()) {
    return RC::BAD_AGG;
  }


  std::vector<agg_field> agg_fields;

  if(is_agg) {
    // is handle multi-table needed

    // collect query fields in `select` statement
    for(int i = static_cast<int>(select_sql.agg_funcs.size())-1; i >= 0; i--) {
      const AggFuncType func = select_sql.agg_funcs[i].func;
      const RelAttrSqlNode &relation_attr = select_sql.agg_funcs[i].attr;
      // handle empty field name
      // select count() from t;
      // select count(*, num) from t;
      if(relation_attr.attribute_name.empty()) {
        return RC::BAD_AGG;
      }

      // handle "*"
      if(0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
        if(func != AggFuncType::COUNT_FUNC) {
          return RC::BAD_AGG;
        }
        // '*'
        if(relation_attr.relation_name.empty()) {
          // count on first field of default table
          agg_fields.push_back(agg_field(func, Field(nullptr, nullptr)));
          agg_fields.back().field_is_star = true;
        } else {
          // 't1.*'
          return RC::BAD_AGG;
        }
      } else  {
        // handle  *.rel
        if(relation_attr.relation_name == "*") {
          return RC::SCHEMA_FIELD_MISSING;
        } else if(relation_attr.relation_name == "") {
          // fix() select count(a) from t;
          // select count(a) from t1, t2; -> select count(t1.a), count(t2.a) from t1 join t2;



          for (Table *table : tables) {
              const FieldMeta * field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
              if(field_meta != nullptr) {
                agg_fields.push_back(SelectStmt::agg_field(func, Field(table,field_meta)));
              }
          }
          if(agg_fields.empty()) {
            LOG_ERROR("no exist field");
            return RC::BAD_AGG;
          }


        } else {
          auto iter = table_map.find(relation_attr.relation_name);
          if(iter == table_map.end()) {
            return RC::SCHEMA_TABLE_NOT_EXIST;
          }
          Table* table = iter->second;

          const auto field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
          // avg semantic legal check, todo(lyq)
          // sum avg only on INTS and FLOATS
          // todo(lyq, recheck)
          if(func == AggFuncType::AVG_FUNC || func == AggFuncType::SUM_FUNC) {
            if(field_meta->type() != AttrType::INTS && field_meta->type() != AttrType::FLOATS) {
              LOG_ERROR("agg avg or sum on non-arithmetic attr");
              return RC::BAD_AGG;
            }
          }
          agg_fields.push_back(agg_field(func, Field(table, field_meta)));
        }
     }
    }
  }


  std::vector<Field> query_fields;
  // FIXME(CHEN): too hacky, fix this after merge our job
  std::vector<RelAttrSqlNode> query_attrs;
  bool                        field_only = true;
  collectQueryFields(select_sql.select_expressions, query_attrs, field_only);
  std::reverse(query_attrs.begin(), query_attrs.end());

  for (int i = static_cast<int>(query_attrs.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = query_attrs[i];

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());



  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions,
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // create order_by stmt
  OrderByStmt *orderby_stmt = nullptr;
  if (!select_sql.order_by.empty()) {
    rc = OrderByStmt::create(
        db, default_table, &table_map, select_sql.order_by, select_sql.order_by.size(), orderby_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct order by stmt");
      return rc;
    }
  }

  std::vector<std::unique_ptr<Expression>> select_expressions;
  if (!field_only || query_fields.empty()) {
    for (int i = 0; i < select_sql.select_expressions.size(); ++i) {
      std::unique_ptr<Expression> select_expr;
      rc =
          rewrite_attr_expr_to_field_expr(db, default_table, &table_map, select_sql.select_expressions[i], select_expr);
      if (OB_FAIL(rc)) {
        LOG_WARN("fail to rewrite, idx: %d, rc: %s", i, strrc(rc));
        return rc;
      }
      select_expressions.emplace_back(std::move(select_expr));
    }
  }

  // create join stmt
  Stmt *join_stmt = nullptr;
  if (select_sql.join_relation != nullptr) {
    std::unique_ptr<GeneralRelationSqlNode> rel = std::make_unique<GeneralRelationSqlNode>(select_sql.join_relation);
    rc                                          = JoinStmt::create(db, table_map, query_fields, rel.get(), join_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct join stmt");
      return rc;
    }
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->agg_fields_.swap(agg_fields);
  select_stmt->is_agg_ = is_agg;
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_       = filter_stmt;
  select_stmt->orderby_stmt_      = orderby_stmt;
  select_stmt->join_stmt_         = static_cast<JoinStmt *>(join_stmt);
  select_stmt->use_project_exprs_ = !field_only || select_stmt->query_fields().empty();
  select_stmt->project_exprs_.swap(select_expressions);
  stmt = select_stmt;
  return RC::SUCCESS;
}

RC SelectStmt::collectJoinTables(Db *db, GeneralRelationSqlNode *rel, std::vector<Table *> &tables,
    std::unordered_map<std::string, Table *> &table_map, std::unordered_map<std::string, std::string> &alias_map)
{
  if (rel->type == REL_TABLE) {
    const char *table_name = std::get<std::string>(rel->relation).c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null");
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
    alias_map.insert(std::pair<std::string, std::string>(table_name, table_name));

    return RC::SUCCESS;
  }

  // handle cascade join
  JoinSqlNode *join = std::get<JoinSqlNode *>(rel->relation);
  RC           rc   = RC::SUCCESS;
  rc                = collectJoinTables(db, join->left, tables, table_map, alias_map);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = collectJoinTables(db, join->right, tables, table_map, alias_map);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC SelectStmt::collectQueryFields(
    const std::vector<Expression *> &select_expressions, std::vector<RelAttrSqlNode> &query_attr, bool &field_only)
{
  RC rc = RC::SUCCESS;
  for (int i = 0; i < select_expressions.size(); ++i) {
    rc = collectQueryFieldsInExpression(select_expressions[i], query_attr, field_only);
    if (rc != RC::SUCCESS) {
      LOG_WARN("Unsupported query expressions, idx: %d, type: %d", i, select_expressions[i]->type());
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC SelectStmt::collectQueryFieldsInExpression(
    Expression *select_expr, std::vector<RelAttrSqlNode> &query_attr, bool &field_only)
{
  RC rc = RC::SUCCESS;
  switch (select_expr->type()) {
    case ExprType::ARITHMETIC: {
      field_only                 = false;
      ArithmeticExpr *arithmetic = static_cast<ArithmeticExpr *>(select_expr);

      if (arithmetic->arithmetic_type() == ArithmeticExpr::Type::NEGATIVE) {
        // consider left only
        rc = collectQueryFieldsInExpression(arithmetic->left().get(), query_attr, field_only);
        if (rc != RC::SUCCESS) {
          LOG_WARN("fail to collec in left");
          return rc;
        }
      } else {
        rc = collectQueryFieldsInExpression(arithmetic->left().get(), query_attr, field_only);
        if (rc != RC::SUCCESS) {
          LOG_WARN("fail to collec in left");
          return rc;
        }
        rc = collectQueryFieldsInExpression(arithmetic->right().get(), query_attr, field_only);
        if (rc != RC::SUCCESS) {
          LOG_WARN("fail to collec in left");
          return rc;
        }
      }
    } break;
    case ExprType::REL_ATTR: {
      query_attr.push_back(*static_cast<RelAttrExprSqlNode *>(select_expr)->get_rel_attr());
    } break;
    case ExprType::VALUE: {

    } break;
    case ExprType::FUNCTION: {
      field_only     = false;
      FuncExpr *func = static_cast<FuncExpr *>(select_expr);
      for (std::unique_ptr<Expression> &argv : func->args()) {
        rc = collectQueryFieldsInExpression(argv.get(), query_attr, field_only);
        if (rc != RC::SUCCESS) {
          LOG_WARN("fail to collect in children");
          return rc;
        }
      }
    } break;
    default: {
      LOG_WARN("Unsupported query expressions, type: %d",  select_expr->type());
      return RC::INTERNAL;
    }
  }

  return rc;
}

RC SelectStmt::get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

// TODO(chen): abstract as a common rewriter instead of owned by filter stmt and too hacky!
RC SelectStmt::rewrite_attr_expr_to_field_expr(Db *db, Table *default_table,
    std::unordered_map<std::string, Table *> *tables, Expression *old_expr, std::unique_ptr<Expression> &ret_expr)
{
  RC rc = RC::SUCCESS;

  // follow logic in expression_rewriter.cpp
  switch (old_expr->type()) {
    case ExprType::REL_ATTR: {
      LOG_DEBUG("Expr is rel attr expr");
      RelAttrExprSqlNode *rel_attr = static_cast<RelAttrExprSqlNode *>(old_expr);
      Table              *table    = nullptr;
      const FieldMeta    *field    = nullptr;
      rc = get_table_and_field(db, default_table, tables, *rel_attr->get_rel_attr(), table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }

      std::unique_ptr<Expression> field_expr(new FieldExpr(table, field));
      field_expr->set_name(rel_attr->name());
      ret_expr.swap(field_expr);
      LOG_DEBUG("rel attr expr rewrited to FieldExpr");
    } break;
    case ExprType::ARITHMETIC: {
      LOG_DEBUG("Expr is arithmetic expr");
      ArithmeticExpr             *arithmetic = static_cast<ArithmeticExpr *>(old_expr);
      std::unique_ptr<Expression> left_expr;
      std::unique_ptr<Expression> right_expr;

      if (arithmetic->arithmetic_type() == ArithmeticExpr::Type::NEGATIVE) {
        rc = rewrite_attr_expr_to_field_expr(db, default_table, tables, arithmetic->left().get(), left_expr);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannnot rewrite right");
          return rc;
        }
      } else {
        rc = rewrite_attr_expr_to_field_expr(db, default_table, tables, arithmetic->left().get(), left_expr);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannnot rewrite right");
          return rc;
        }

        rc = rewrite_attr_expr_to_field_expr(db, default_table, tables, arithmetic->right().get(), right_expr);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannnot rewrite right");
          return rc;
        }
      }

      std::unique_ptr<Expression> new_arithmetic(
          new ArithmeticExpr(arithmetic->arithmetic_type(), std::move(left_expr), std::move(right_expr)));
      ret_expr.swap(new_arithmetic);

      LOG_DEBUG("arithmetic attr expr transferred success");
    } break;
    case ExprType::VALUE: {
      ValueExpr                  *value = static_cast<ValueExpr *>(old_expr);
      std::unique_ptr<Expression> new_value(new ValueExpr(value->get_value()));
      ret_expr.swap(new_value);
    } break;
    case ExprType::FUNCTION: {
      // TODO(chen): func
      std::vector<std::unique_ptr<Expression>> args;
      FuncExpr                                *func = static_cast<FuncExpr *>(old_expr);
      for (std::unique_ptr<Expression> &argv : func->args()) {
        std::unique_ptr<Expression> new_argv;
        rewrite_attr_expr_to_field_expr(db, default_table, tables, argv.get(), new_argv);
        args.emplace_back(std::move(new_argv));
      }
      std::unique_ptr<Expression> new_func(new FuncExpr(func->func_type(), args));
      ret_expr.swap(new_func);
    }
    default: {
      // TODO(chen): handle '*'
      LOG_DEBUG("type: %d, no need to rewrite", old_expr->type());
    }
  }

  ret_expr->set_name(old_expr->name());
  return rc;
}