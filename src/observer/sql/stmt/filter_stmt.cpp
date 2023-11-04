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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <memory>
#include <vector>

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt)
{
  LOG_DEBUG("create filter stmt");
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const std::vector<ComparisonExpr *> &conditions, int condition_num, FilterStmt *&stmt)
{
  LOG_DEBUG("create filter stmt");
  RC rc = RC::SUCCESS;
  stmt  = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
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

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit)
{
  LOG_DEBUG("create filter unit");
  LOG_DEBUG("left_is_attr: %d, right_is_attr: %d", condition.left_is_attr, condition.right_is_attr);
  LOG_DEBUG("condition.left_value.attr_type(): %d, condition.right_value.attr_type(): %d", condition.left_value.attr_type(), condition.right_value.attr_type());
  LOG_DEBUG("condition.left_value.data(): %s, condition.right_value.data(): %s", condition.left_value.data(), condition.right_value.data());

  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  filter_unit = new FilterUnit;
  AttrType lefr_attr_name;
  if (condition.left_is_attr) {
    LOG_DEBUG("condition.left_is_attr");
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
    lefr_attr_name = table->table_meta().field(condition.left_attr.attribute_name.c_str())->type();
  } else {
    LOG_DEBUG("FilterObj filter_obj");
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }

  AttrType right_attr_name;
  if (condition.right_is_attr) {
    LOG_DEBUG("condition.right_is_attr");
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
    right_attr_name = table->table_meta().field(condition.right_attr.attribute_name.c_str())->type();
  } else {
    LOG_DEBUG("filter_obj.init_value(condition.right_value)");
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  }

  LOG_DEBUG("filter_unit->left().value.attr_type(): %d, filter_unit->right().value.attr_type(): %d", filter_unit->left().value.attr_type(), filter_unit->right().value.attr_type());
  LOG_DEBUG("filter_unit->left().value.data(): %s, filter_unit->right().value.data(): %s", filter_unit->left().value.data(), filter_unit->right().value.data());
  if (lefr_attr_name == DATES && filter_unit->right().value.attr_type() == CHARS) {
    int64_t date;
    bool    valid = serialize_date(&date, filter_unit->right().value.data());
    if (!valid) {
      LOG_DEBUG("invalid date: %s", filter_unit->right().value.data());
      return RC::INVALID_ARGUMENT;
    } else {
      filter_unit->right().value.set_type(DATES);
      filter_unit->right().value.set_date(date);
    }
  } else if (right_attr_name == DATES && filter_unit->left().value.attr_type() == CHARS) {
    int64_t date;
    bool    valid = serialize_date(&date, filter_unit->left().value.data());
    if (!valid) {
      LOG_DEBUG("invalid date: %s", filter_unit->left().value.data());
      return RC::INVALID_ARGUMENT;
    } else {
      filter_unit->left().value.set_type(DATES);
      filter_unit->left().value.set_date(date);
    }
  }

  if (lefr_attr_name == TEXTS && filter_unit->right().value.attr_type() == CHARS) {
    filter_unit->right().value.set_type(TEXTS);
    filter_unit->right().value.set_text(filter_unit->right().value.data());
  } else if (right_attr_name == TEXTS && filter_unit->left().value.attr_type() == CHARS) {
    filter_unit->left().value.set_type(TEXTS);
    filter_unit->left().value.set_text(filter_unit->left().value.data());
  }

  //  if(lefr_attr_name != filter_unit->right().value.attr_type() && condition.comp != IS_LEFT_NOT_NULL &&
  //  condition.comp != IS_LEFT_NULL && lefr_attr_name != NULLS) {
  //    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  //  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    ComparisonExpr *condition, FilterUnit *&filter_unit)
{
  LOG_DEBUG("create filter unit");
  LOG_DEBUG("left type: %d, right type: %d", condition->left()->type(), condition->right()->type());
  LOG_DEBUG("condition.left_value.attr_type(): %d, condition.right_value.attr_type(): %d", condition->left()->value_type(), condition->right()->value_type());
  if (condition->left()->type() == ExprType::VALUE) {
    LOG_DEBUG("condition.left.value: %s", static_cast<ValueExpr*>(condition->left().get())->get_value().data());
  }
  if (condition->right()->type() == ExprType::VALUE) {
    LOG_DEBUG("condition.right.value: %s", static_cast<ValueExpr*>(condition->right().get())->get_value().data());
  }

  RC rc = RC::SUCCESS;

  CompOp comp = condition->comp();
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  if(CompOp::AND_OP == comp || CompOp::OR_OP == comp) {
    FilterUnit *left_unit = nullptr;
    FilterUnit *right_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, reinterpret_cast<ComparisonExpr*>(condition->left().get()), left_unit);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("filter unit create left expression failed");
      return rc;
    }
    rc = create_filter_unit(db, default_table, tables, reinterpret_cast<ComparisonExpr*>(condition->right().get()), right_unit);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("filter unit create left expression failed");
      delete left_unit;
      return rc;
    }

    filter_unit = new FilterUnit;
    filter_unit->set_comp(comp);
    filter_unit->set_left_unit(left_unit);
    filter_unit->set_right_unit(right_unit);
    return rc;
  }

  filter_unit = new FilterUnit;

  AttrType left_attr_type;
  if (condition->left()->type() == ExprType::REL_ATTR) {
    LOG_DEBUG("condition.left_is_attr");
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db,
        default_table,
        tables,
        *static_cast<RelAttrExprSqlNode *>(condition->left().get())->get_rel_attr(),
        table,
        field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
    left_attr_type =
        table->table_meta()
            .field(static_cast<RelAttrExprSqlNode *>(condition->left().get())->get_rel_attr()->attribute_name.c_str())
            ->type();
  } else if (condition->left()->type() == ExprType::VALUE) {
    LOG_DEBUG("FilterObj filter_obj set value");
    FilterObj filter_obj;
    filter_obj.init_value(static_cast<ValueExpr *>(condition->left().get())->get_value());
    filter_unit->set_left(filter_obj);
  } else if (condition->left()->type() == ExprType::ARITHMETIC) {
    rewrite_attr_expr_to_field_expr(db, default_table, tables, condition->left());
    FilterObj filter_obj;
    filter_obj.init_expr(condition->left().get());
    filter_unit->set_left(filter_obj);
  } else if (condition->left()->type() == ExprType::FUNCTION) {
    FuncExpr *func = static_cast<FuncExpr *>(condition->left().get());
    for (std::unique_ptr<Expression> &argv : func->args()) {
      rewrite_attr_expr_to_field_expr(db, default_table, tables, argv);
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition->left().get());
    filter_unit->set_left(filter_obj);
  } else if(condition->left()->type() == ExprType::SUBQUERYTYPE) {
    SubQueryExpression *sub_query_expr = static_cast<SubQueryExpression *>(condition->left().get());
    if(sub_query_expr->get_select_sql_node()->select_expressions.size() > 1) {
      return RC::SUB_QUERY_MULTI_FIELDS;
    }
    RC rc = sub_query_expr->create_expression(*tables, std::vector<Table *>{default_table}, comp, db);
    if(rc != RC::SUCCESS) {
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition->left().get());
    filter_unit->set_left(filter_obj);
  } else {
    LOG_WARN("unsupported left expr, %d", condition->left()->type());
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  AttrType right_attr_type;
  if (condition->right()->type() == ExprType::REL_ATTR) {
    LOG_DEBUG("condition.right_is_attr");
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db,
        default_table,
        tables,
        *static_cast<RelAttrExprSqlNode *>(condition->right().get())->get_rel_attr(),
        table,
        field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
    right_attr_type =
        table->table_meta()
            .field(static_cast<RelAttrExprSqlNode *>(condition->right().get())->get_rel_attr()->attribute_name.c_str())
            ->type();
  } else if (condition->right()->type() == ExprType::VALUE) {
    LOG_DEBUG("filter_obj.init_value(condition.right_value)");
    FilterObj filter_obj;
    filter_obj.init_value(static_cast<ValueExpr *>(condition->right().get())->get_value());
    filter_unit->set_right(filter_obj);
  } else if (condition->right()->type() == ExprType::ARITHMETIC) {
    rewrite_attr_expr_to_field_expr(db, default_table, tables, condition->right());
    FilterObj filter_obj;
    filter_obj.init_expr(condition->right().get());
    filter_unit->set_right(filter_obj);
  } else if (condition->right()->type() == ExprType::FUNCTION) {
    FuncExpr *func = static_cast<FuncExpr *>(condition->right().get());
    for (std::unique_ptr<Expression> &argv : func->args()) {
      rewrite_attr_expr_to_field_expr(db, default_table, tables, argv);
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition->right().get());
    filter_unit->set_right(filter_obj);
  } else if(condition->right()->type() == ExprType::SUBQUERYTYPE) {
    SubQueryExpression *sub_query_expr = static_cast<SubQueryExpression *>(condition->right().get());
    if(sub_query_expr->get_select_sql_node()->select_expressions.size() > 1) {
      return RC::SUB_QUERY_MULTI_FIELDS;
    }
    RC rc = sub_query_expr->create_expression(*tables, std::vector<Table *>{default_table}, comp, db);
    if(rc != RC::SUCCESS) {
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_expr(condition->right().get());
    filter_unit->set_right(filter_obj);
  } else if (condition->right()->type() == ExprType::SUBLISTTYPE) {
    FilterObj filter_obj;
    filter_obj.init_expr(condition->right().get());
    filter_unit->set_right(filter_obj);
  } else {
      LOG_WARN("unsupported right expr, %d", condition->right()->type());
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  }

  LOG_DEBUG("filter_unit->left().value.attr_type(): %d, filter_unit->right().value.attr_type(): %d", filter_unit->left().value.attr_type(), filter_unit->right().value.attr_type());
  LOG_DEBUG("filter_unit->left().value.data(): %s, filter_unit->right().value.data(): %s", filter_unit->left().value.data(), filter_unit->right().value.data());
  if (condition->left()->type() == ExprType::REL_ATTR && left_attr_type == DATES &&
      filter_unit->right().value.attr_type() == CHARS) {
    int64_t date;
    bool    valid = serialize_date(&date, filter_unit->right().value.data());
    if (!valid) {
      LOG_DEBUG("invalid date: %s", filter_unit->right().value.data());
      return RC::INVALID_ARGUMENT;
    } else {
      filter_unit->right().value.set_type(DATES);
      filter_unit->right().value.set_date(date);
    }
  } else if (condition->right()->type() == ExprType::REL_ATTR && right_attr_type == DATES &&
             filter_unit->left().value.attr_type() == CHARS) {
    int64_t date;
    bool    valid = serialize_date(&date, filter_unit->left().value.data());
    if (!valid) {
      LOG_DEBUG("invalid date: %s", filter_unit->left().value.data());
      return RC::INVALID_ARGUMENT;
    } else {
      filter_unit->left().value.set_type(DATES);
      filter_unit->left().value.set_date(date);
    }
  }

  if (left_attr_type == TEXTS && filter_unit->right().value.attr_type() == CHARS) {
    filter_unit->right().value.set_type(TEXTS);
    filter_unit->right().value.set_text(filter_unit->right().value.data());
  } else if (right_attr_type == TEXTS && filter_unit->left().value.attr_type() == CHARS) {
    filter_unit->left().value.set_type(TEXTS);
    filter_unit->left().value.set_text(filter_unit->left().value.data());
  }

  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}

// TODO(chen): abstract as a common rewriter instead of owned by filter stmt
RC FilterStmt::rewrite_attr_expr_to_field_expr(
    Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables, std::unique_ptr<Expression> &expr)
{
  RC rc = RC::SUCCESS;

  // follow logic in expression_rewriter.cpp
  switch (expr->type()) {
    case ExprType::REL_ATTR: {
      LOG_DEBUG("Expr is rel attr expr");
      RelAttrExprSqlNode *rel_attr = static_cast<RelAttrExprSqlNode *>(expr.get());
      rel_attr->get_rel_attr();
      Table           *table = nullptr;
      const FieldMeta *field = nullptr;
      rc                     = get_table_and_field(db, default_table, tables, *rel_attr->get_rel_attr(), table, field);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot find attr");
        return rc;
      }

      std::unique_ptr<Expression> field_expr(new FieldExpr(table, field));
      field_expr->set_name(expr->name());
      expr.swap(field_expr);
      LOG_DEBUG("rel attr expr rewrited to FieldExpr");
    } break;
    case ExprType::ARITHMETIC: {
      LOG_DEBUG("Expr is arithmetic expr");
      ArithmeticExpr *arithmetic = static_cast<ArithmeticExpr *>(expr.get());

      if (arithmetic->arithmetic_type() == ArithmeticExpr::Type::NEGATIVE) {

        // neg only consider left
        rc = rewrite_attr_expr_to_field_expr(db, default_table, tables, arithmetic->left());
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannnot rewrite right");
          return rc;
        }
      } else {
        rc = rewrite_attr_expr_to_field_expr(db, default_table, tables, arithmetic->left());
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannnot rewrite right");
          return rc;
        }

        rc = rewrite_attr_expr_to_field_expr(db, default_table, tables, arithmetic->right());
        if (rc != RC::SUCCESS) {
          LOG_WARN("cannnot rewrite right");
          return rc;
        }
      }

    } break;
    default: {
      LOG_DEBUG("type: %d, no need to rewrite", expr->type());
    }
  }

  return rc;
}
