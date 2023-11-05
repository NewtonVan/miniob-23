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
#include <cstdlib>
#include <ctime>
#include <memory>
#include <string>
#include <sys/types.h>
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
  if (nullptr != join_stmt_) {
    delete join_stmt_;
    join_stmt_ = nullptr;
  }
  if (nullptr != orderby_stmt_) {
    delete orderby_stmt_;
    orderby_stmt_ = nullptr;
  }
  if (nullptr != having_stmt_) {
    delete having_stmt_;
    having_stmt_ = nullptr;
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

RC collect_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, Expression *expr,
    std::vector<Field> &all_agg_field, std::vector<Field> &all_non_agg_field, std::vector<AggType> &agg_types,
    std::vector<std::string> &all_agg_expr_name);

RC parse_rel_attr(Db *db, const std::unordered_map<std::string, Table *> &table_map,
    const RelAttrSqlNode &relation_attr, const std::vector<Table *> &tables, std::vector<Field> &query_fields);

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, const std::vector<Table *> &parent_tables,
    const std::unordered_map<std::string, Table *> &parent_table_map, bool is_sub_query, Stmt *&stmt)
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
        if (table_map.contains(select_sql.relations[i].alias) &&
            table_map[select_sql.relations[i].alias]->table_id() != table->table_id()) {
          LOG_WARN("invalid alias: %s", select_sql.relations[i].alias.c_str());
          return RC::INVALID_ARGUMENT;
        }
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
  // invalid AggExpr
  // example: count(), count(*, num)
  // detected in parse_stage and reported at resolve_stage
  // satisfy AggExpr->rel_attr() == nullptr

  // collect agg (just in select_sql.select_expression，collect having clause in future)
  // collect all_agg_field to construct AggTuple in AggPhysicalOperator
  // while colleting, if any AggExpr is invalid agg return RC::BAD_AGG, (mem manage)
  // finally, if all_agg_field is not empty, set is_agg = true;

  // if is_agg == true:
  // collect all_non_agg_field to be compared with group by field and to construct AggTuple AggPhysicalOperator
  // if any non_agg_field do not exist in group_by clause return RC::BAD_AGG
  // rewrite all expr in select_sql.selection_expression

  // if is_agg == false:

  // agg select
  bool is_agg = false;

  // record agg and non-agg in select attrs
  std::vector<std::string> select_agg_expr_names;
  std::vector<AggType>     select_agg_types;
  std::vector<Field>       select_agg_fields;
  std::vector<Field>       select_non_agg_fields;

  // record group by field
  std::vector<Field> group_by_fields;

  // record agg and non-agg in having clause
  std::vector<Field>       having_agg_fields;
  std::vector<std::string> having_agg_expr_names;
  std::vector<AggType>     having_agg_types;
  std::vector<Field>       having_non_agg_fields;

  // non agg select
  std::vector<Field> query_fields;
  bool               field_only = true;

  // final select expression
  std::vector<std::unique_ptr<Expression>> new_select_expressions;

  for (Expression *select_expr : select_sql.select_expressions) {
    auto rc = collect_field(db,
        default_table,
        &table_map,
        select_expr,
        select_agg_fields,
        select_non_agg_fields,
        select_agg_types,
        select_agg_expr_names);
    if (rc != RC::SUCCESS) {
      // mem manage(todo) free pointer in select_sql.select_expressions
      return rc;
    }
  }

  if (!select_agg_fields.empty()) {
    field_only = false;
    // collect group by field
    for (auto &attr : select_sql.group_by.attrs) {
      Table           *table      = nullptr;
      const FieldMeta *field_meta = nullptr;

      // group by * is illegal
      if (attr.attribute_name == "*") {
        return RC::BAD_AGG;
      }

      auto rc = get_table_and_field(db, default_table, &table_map, attr, table, field_meta);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }
      group_by_fields.emplace_back(table, field_meta);
    }

    // select clause check
    if (!select_non_agg_fields.empty()) {
      // field in all_non_agg_field must exist in all_group_by field
      bool all_hit = true;
      for (auto &non_agg_field : select_non_agg_fields) {
        bool cur_hit = false;
        for (auto &group_by_field : group_by_fields) {
          if (non_agg_field.table_name() == group_by_field.table_name() &&
              non_agg_field.field_name() == group_by_field.field_name()) {
            cur_hit = true;
          }
        }
        if (!cur_hit) {
          all_hit = false;
          break;
        }
      }
      if (!all_hit) {
        return RC::BAD_AGG;
      }
    }

    // having check
    // make sure having clause only have agg func and group by field
    if (!select_sql.group_by.having.conds.empty()) {
      for (auto &cmp_expr : select_sql.group_by.having.conds) {
        auto rc = collect_field(db,
            default_table,
            &table_map,
            cmp_expr,
            having_agg_fields,
            having_non_agg_fields,
            having_agg_types,
            having_agg_expr_names);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }

      // non agg fields in having clause must hit field in group_by field
      if (!having_non_agg_fields.empty()) {
        bool all_hit = true;
        for (auto &having_non_agg_field : having_non_agg_fields) {
          bool cur_hit = false;
          for (auto &group_by_field : group_by_fields) {
            if (having_non_agg_field.table_name() == group_by_field.table_name() &&
                having_non_agg_field.field_name() == group_by_field.field_name()) {
              cur_hit = true;
            }
          }
          if (!cur_hit) {
            all_hit = false;
            break;
          }
        }
        if (!all_hit) {
          return RC::BAD_AGG;
        }
      }
    }

    // finally we have a valid agg
    is_agg = true;

  } else {
    // no agg but with group by
    if (!select_sql.group_by.attrs.empty()) {
      return RC::BAD_AGG;
    }
  }

  if (is_agg) {
    for (Expression *old_expr : select_sql.select_expressions) {
      // rewrite all RelAttrNode to Field
      std::unique_ptr<Expression> new_expr;
      auto rc = rewrite_attr_expr_to_field_expr(db, default_table, &table_map, old_expr, new_expr);
      new_select_expressions.push_back(std::move(new_expr));
    }
  } else {
    // FIXME(CHEN): too hacky, fix this after merge our job
    std::vector<RelAttrSqlNode> query_attrs;
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

    for (int i = 0; i < select_sql.select_expressions.size(); ++i) {
      if (select_sql.select_expressions[i]->type() == ExprType::STAR) {
        if (!select_sql.select_expressions[i]->name().empty()) {
          LOG_ERROR("star expression should not have alias: %s", select_sql.select_expressions[i]->name().c_str());
          return RC::INVALID_ARGUMENT;
        }
        const RelAttrSqlNode &relation_attr =
            *static_cast<StarExprSqlNode *>(select_sql.select_expressions[i])->get_rel_attr();
        std::vector<Field> star_query_fields;
        RC                 rc = parse_rel_attr(db, table_map, relation_attr, tables, star_query_fields);
        if (rc != RC::SUCCESS) {
          LOG_WARN("Fail to expand star");
        }
        // if t.*, then prefix "t."
        std::string table_prefix = relation_attr.relation_name.empty() ? "" : relation_attr.relation_name + ".";
        bool        with_tables  = tables.size() > 1;

        for (Field &field : star_query_fields) {
          std::unique_ptr<Expression> field_expr(new FieldExpr(field.table(), field.meta()));
          if (relation_attr.relation_name.empty()) {
            if (with_tables) {
              field_expr->set_name(std::string(field.table_name()) + "." + field.field_name());
            } else {
              field_expr->set_name(field.field_name());
            }
          } else {
            field_expr->set_name(table_prefix + field.field_name());
          }
          // TODO(chen): set expr name
          new_select_expressions.emplace_back(std::move(field_expr));
        }
      } else {
        std::unique_ptr<Expression> select_expr;
        auto                        rc = rewrite_attr_expr_to_field_expr(
            db, default_table, &table_map, select_sql.select_expressions[i], select_expr);
        if (OB_FAIL(rc)) {
          LOG_WARN("fail to rewrite, idx: %d, rc: %s", i, strrc(rc));
          return rc;
        }
        new_select_expressions.emplace_back(std::move(select_expr));
      }
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;

  // 子查询，需要和父表关联的情况下
  RC rc = RC::SUCCESS;
  if (is_sub_query) {
    std::unordered_map<std::string, Table *> temp_table_map = table_map;
    temp_table_map.insert(parent_table_map.begin(), parent_table_map.end());
    rc = FilterStmt::create(db,
        default_table,
        &temp_table_map,
        select_sql.conditions,
        static_cast<int>(select_sql.conditions.size()),
        filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
  } else {
    rc = FilterStmt::create(db,
        default_table,
        &table_map,
        select_sql.conditions,
        static_cast<int>(select_sql.conditions.size()),
        filter_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }
  }

  HavingStmt *having_stmt = nullptr;
  rc                      = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.group_by.having.conds,
      static_cast<int>(select_sql.group_by.having.conds.size()),
      having_stmt);

  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct having stmt");
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
  // agg related
  // we need all agg fields, types and expr name withing select clause and having clause
  // and all group by fields
  // select_stmt->select_agg_expr_names_.swap(select_agg_expr_names);
  // select_stmt->select_agg_types_.swap(select_agg_types);
  // select_stmt->select_agg_fields_.swap(select_agg_fields);
  // select_stmt->having_agg_expr_names_.swap(having_agg_expr_names);
  // select_stmt->having_agg_types_.swap(having_agg_types);
  // select_stmt->having_agg_fields_.swap(having_agg_fields);

  std::copy(
      select_agg_expr_names.begin(), select_agg_expr_names.end(), std::back_inserter(select_stmt->all_agg_expr_names_));
  std::copy(
      having_agg_expr_names.begin(), having_agg_expr_names.end(), std::back_inserter(select_stmt->all_agg_expr_names_));

  std::copy(select_agg_types.begin(), select_agg_types.end(), std::back_inserter(select_stmt->all_agg_types_));
  std::copy(having_agg_types.begin(), having_agg_types.end(), std::back_inserter(select_stmt->all_agg_types_));

  std::copy(select_agg_fields.begin(), select_agg_fields.end(), std::back_inserter(select_stmt->all_agg_fields_));
  std::copy(having_agg_fields.begin(), having_agg_fields.end(), std::back_inserter(select_stmt->all_agg_fields_));

  select_stmt->group_by_fields_.swap(group_by_fields);

  select_stmt->having_stmt_ = having_stmt;

  select_stmt->is_agg_ = is_agg;
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_  = filter_stmt;
  select_stmt->orderby_stmt_ = orderby_stmt;
  select_stmt->join_stmt_    = static_cast<JoinStmt *>(join_stmt);
  select_stmt->project_exprs_.swap(new_select_expressions);

  // for create-table-select
  if (select_sql.is_create_table_select_stmt && !select_sql.create_table_select_table_name.empty()) {
    select_stmt->is_create_table_select_stmt     = select_sql.is_create_table_select_stmt;
    select_stmt->db                              = db;
    select_stmt->create_table_select_table_name_ = select_sql.create_table_select_table_name;
    select_stmt->table_select_attr_infos_        = select_sql.table_select_attr_infos;
  }

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
    case ExprType::STAR: {
      query_attr.push_back(*static_cast<StarExprSqlNode *>(select_expr)->get_rel_attr());
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

RC collect_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, Expression *expr,
    std::vector<Field> &all_agg_field, std::vector<Field> &all_non_agg_field, std::vector<AggType> &agg_types,
    std::vector<std::string> &all_agg_expr_name)
{
  RC rc = RC::SUCCESS;
  switch (expr->type()) {
    case ExprType::REL_ATTR: {
      RelAttrExprSqlNode *rel_attr = static_cast<RelAttrExprSqlNode *>(expr);
      Table              *table    = nullptr;
      const FieldMeta    *field    = nullptr;

      if (strcmp(rel_attr->field_name(), "*") == 0) {
        // note, arrive here, expr is definitely not an valid agg
        // so we can just append a all_non_agg_field to pass the agg logic
        all_non_agg_field.push_back(Field(nullptr, nullptr));
      } else {
        rc = get_table_and_field(db, default_table, tables, *rel_attr->get_rel_attr(), table, field);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannot find attr");
          return rc;
        }
        all_non_agg_field.push_back(Field(table, field));
      }
    } break;
    case ExprType::AGG: {
      AggExpr         *agg_expr = static_cast<AggExpr *>(expr);
      Table           *table    = nullptr;
      const FieldMeta *field    = nullptr;

      // bad agg call check
      if (agg_expr->rel_attr() == nullptr) {
        return RC::BAD_AGG;
      }

      if (strcmp(agg_expr->rel_attr()->attribute_name.c_str(), "*") == 0) {
        ASSERT(agg_expr->agg_type() == AggType::COUNT_STAR, "inconsistent agg");
        agg_types.push_back(agg_expr->agg_type());
        all_agg_field.push_back(Field(nullptr, nullptr));
      } else {
        rc = get_table_and_field(db, default_table, tables, *agg_expr->rel_attr(), table, field);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannot find attr");
          return rc;
        }
        agg_types.push_back(agg_expr->agg_type());
        all_agg_field.push_back(Field(table, field));
      }

      all_agg_expr_name.push_back(agg_expr->name());
    } break;
    case ExprType::ARITHMETIC: {
      ArithmeticExpr *arithmetic = static_cast<ArithmeticExpr *>(expr);
      if (arithmetic->arithmetic_type() == ArithmeticExpr::Type::NEGATIVE) {
        rc = collect_field(db,
            default_table,
            tables,
            arithmetic->left().get(),
            all_agg_field,
            all_non_agg_field,
            agg_types,
            all_agg_expr_name);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      } else {
        rc = collect_field(db,
            default_table,
            tables,
            arithmetic->left().get(),
            all_agg_field,
            all_non_agg_field,
            agg_types,
            all_agg_expr_name);
        if (rc != RC::SUCCESS) {
          return rc;
        }
        rc = collect_field(db,
            default_table,
            tables,
            arithmetic->right().get(),
            all_agg_field,
            all_non_agg_field,
            agg_types,
            all_agg_expr_name);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    } break;
    case ExprType::CAST: {
      CastExpr *cast_expr = static_cast<CastExpr *>(expr);
      rc                  = collect_field(db,
          default_table,
          tables,
          cast_expr->child().get(),
          all_agg_field,
          all_non_agg_field,
          agg_types,
          all_agg_expr_name);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } break;
    case ExprType::FUNCTION: {
      FuncExpr *func_expr = static_cast<FuncExpr *>(expr);
      for (auto &arg : func_expr->args()) {
        rc = collect_field(
            db, default_table, tables, arg.get(), all_agg_field, all_non_agg_field, agg_types, all_agg_expr_name);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    } break;
    case ExprType::COMPARISON: {
      // only having clause can reache here
      ComparisonExpr *cmp_expr = static_cast<ComparisonExpr *>(expr);
      rc                       = collect_field(db,
          default_table,
          tables,
          cmp_expr->left().get(),
          all_agg_field,
          all_non_agg_field,
          agg_types,
          all_agg_expr_name);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      rc = collect_field(db,
          default_table,
          tables,
          cmp_expr->right().get(),
          all_agg_field,
          all_non_agg_field,
          agg_types,
          all_agg_expr_name);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } break;
    default: return RC::SUCCESS;
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
    } break;
    case ExprType::AGG: {
      // arrive here, must be rewriting a valid select agg
      // fill in field
      // agg do not have child expr
      Table           *table    = nullptr;
      const FieldMeta *field    = nullptr;
      AggExpr         *agg_expr = static_cast<AggExpr *>(old_expr);
      // bad agg
      // select count()
      // select cout(*,num)
      if (agg_expr->rel_attr() == nullptr) {
        return RC::BAD_AGG;
      }

      // special case: select count(*)
      if (agg_expr->agg_type() == AggType::COUNT_STAR) {
        ASSERT(strcmp(agg_expr->rel_attr()->attribute_name.c_str(), "*") == 0, "count star inconsistent");
        agg_expr->set_field(Field(nullptr, nullptr));
      } else {
        rc = get_table_and_field(db, default_table, tables, *agg_expr->rel_attr(), table, field);
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannot find attr");
          return rc;
        }
        agg_expr->set_field(Field(table, field));
      }
      std::unique_ptr<Expression> new_epxr(agg_expr);
      ret_expr.swap(new_epxr);
    } break;
    default: LOG_WARN("unsupported expr rewrite"); return RC::INTERNAL;
  }
  ret_expr->set_name(old_expr->name());
  return rc;
}

RC parse_rel_attr(Db *db, const std::unordered_map<std::string, Table *> &table_map,
    const RelAttrSqlNode &relation_attr, const std::vector<Table *> &tables, std::vector<Field> &query_fields)
{
  if (common::is_blank(relation_attr.relation_name.c_str()) && 0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
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

  return RC::SUCCESS;
}