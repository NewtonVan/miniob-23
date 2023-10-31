/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/sort_logical_operator.h"
#include "sql/operator/agg_func_logical_operator.h"

#include "sql/operator/update_logical_operator.h"
#include "sql/stmt/join_stmt.h"
#include "sql/stmt/single_table_stmt.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/field/field.h"
#include "storage/table/table.h"
#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc                  = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc                      = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc                      = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc                      = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc                      = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc                        = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(JoinStmt *join_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  RC                               rc = RC::SUCCESS;
  std::unique_ptr<LogicalOperator> left_op;
  if (join_stmt->left()->type() == StmtType::JOIN) {
    rc = create_plan(static_cast<JoinStmt *>(join_stmt->left()), left_op);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else if (join_stmt->left()->type() == StmtType::SINGLE_TABLE) {
    SingleTableStmt *left_table_stmt = static_cast<SingleTableStmt *>(join_stmt->left());
    Table           *table           = left_table_stmt->table();

    unique_ptr<LogicalOperator> table_get_oper(
        new TableGetLogicalOperator(table, left_table_stmt->query_fields(), true));
    left_op = std::make_unique<TableGetLogicalOperator>(table, left_table_stmt->query_fields(), true);
  }

  std::unique_ptr<LogicalOperator> right_op;
  if (join_stmt->right()->type() == StmtType::JOIN) {
    rc = create_plan(static_cast<JoinStmt *>(join_stmt->right()), right_op);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  } else if (join_stmt->right()->type() == StmtType::SINGLE_TABLE) {
    SingleTableStmt *right_table_stmt = static_cast<SingleTableStmt *>(join_stmt->right());
    Table           *table            = right_table_stmt->table();

    unique_ptr<LogicalOperator> table_get_oper(
        new TableGetLogicalOperator(table, right_table_stmt->query_fields(), true));
    right_op = std::make_unique<TableGetLogicalOperator>(table, right_table_stmt->query_fields(), true);
  }

  // TODO(chen): expression
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = join_stmt->join_condition()->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    unique_ptr<Expression> left(filter_obj_left.is_attr
                                    ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                    : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

    unique_ptr<Expression> right(filter_obj_right.is_attr
                                     ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                     : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
  JoinLogicalOperator        *join_oper = new JoinLogicalOperator(std::move(conjunction_expr));
  join_oper->add_child(std::move(left_op));
  join_oper->add_child(std::move(right_op));

  logical_operator = unique_ptr<LogicalOperator>(join_oper);

  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables     = select_stmt->tables();
  const std::vector<Field>   &query_fields = select_stmt->query_fields();
  const std::vector<SelectStmt::agg_field> all_agg_fields = select_stmt->all_agg_fields();

  if (select_stmt->join_stmt() != nullptr) {
    RC rc = RC::SUCCESS;
    rc    = create_plan(select_stmt->join_stmt(), table_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create join logical plan. rc=%s", strrc(rc));
      return rc;
    }
  } else {
    for (Table *table : tables) {
      std::vector<Field> fields;
      for (const Field &field : query_fields) {
        if (0 == strcmp(field.table_name(), table->name())) {
          fields.push_back(field);
        }
      }

      unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true /*readonly*/));
      if (table_oper == nullptr) {
        table_oper = std::move(table_get_oper);
      } else {
        JoinLogicalOperator *join_oper = new JoinLogicalOperator;
        join_oper->add_child(std::move(table_oper));
        join_oper->add_child(std::move(table_get_oper));
        table_oper = unique_ptr<LogicalOperator>(join_oper);
      }
    }
  }

  // 生成predicate operator
  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  std::vector<Field> all_fields;
  for (auto &table : tables) {
    const std::vector<FieldMeta> *field_metas = table->table_meta().field_metas();
    const Table *table_ptr = table; // 指向当前表的指针
    for (const FieldMeta &field_meta : *field_metas) {
      all_fields.emplace_back(table_ptr, &field_meta);
    }
  }
  unique_ptr<SortLogicalOperator> sort_oper(new SortLogicalOperator(all_fields, select_stmt->orderby_stmt()));


  // WIP(lyq) agg logicalOperator comes in
  if(select_stmt->is_agg()) {
    unique_ptr<LogicalOperator> agg_oper(new AggLogicalOperator(all_agg_fields));
    if(predicate_oper) {
      if(table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      agg_oper->add_child(std::move(predicate_oper));
    } else {
      if(table_oper) {
        agg_oper->add_child(std::move(table_oper));
      }
    }

    logical_operator.swap(agg_oper);

    return RC::SUCCESS;
  }


  unique_ptr<LogicalOperator> project_oper;
  if (select_stmt->use_project_exprs()) {
    unique_ptr<LogicalOperator> proj_exprs(
        new ProjectLogicalOperator(query_fields, std::move(select_stmt->project_exprs())));
    project_oper.swap(proj_exprs);
  } else {
    unique_ptr<LogicalOperator> proj_fields(new ProjectLogicalOperator(query_fields));
    project_oper.swap(proj_fields);
  }
  if (predicate_oper) {
    if (table_oper) {
      if (select_stmt->join_stmt() != nullptr || select_stmt->tables().size() > 1) {
        // inner join case
        rc = static_cast<JoinLogicalOperator *>(table_oper.get())
                 ->push_down_predicate(static_cast<PredicateLogicalOperator *>(predicate_oper.get()));
        if (rc != RC::SUCCESS) {
          LOG_WARN("failed to push down filter into join logical plan. rc=%s", strrc(rc));
          return rc;
        }
      }

      predicate_oper->add_child(std::move(table_oper));

      // TODO : 优化算子添加逻辑
      if(select_stmt->orderby_stmt() != nullptr) {
        sort_oper->add_child(std::move(predicate_oper));
        predicate_oper = std::move(sort_oper);
      }
    }

    project_oper->add_child(std::move(predicate_oper));
  } else {
    if (table_oper) {

      // TODO : 优化算子添加逻辑
      if(select_stmt->orderby_stmt() != nullptr) {
        sort_oper->add_child(std::move(table_oper));
        table_oper = std::move(sort_oper);
      }

      project_oper->add_child(std::move(table_oper));
    }
  }




  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    Expression *left_ptr = nullptr;
    if (filter_obj_left.expr != nullptr) {
      left_ptr = filter_obj_left.expr;
    } else if (filter_obj_left.is_attr) {
      left_ptr = static_cast<Expression *>(new FieldExpr(filter_obj_left.field));
    } else {
      left_ptr = static_cast<Expression *>(new ValueExpr(filter_obj_left.value));
    }
    unique_ptr<Expression> left(left_ptr);

    Expression *right_ptr = nullptr;
    if (filter_obj_right.expr != nullptr) {
      right_ptr = filter_obj_right.expr;
    } else if (filter_obj_right.is_attr) {
      right_ptr = static_cast<Expression *>(new FieldExpr(filter_obj_right.field));
    } else {
      right_ptr = static_cast<Expression *>(new ValueExpr(filter_obj_right.value));
    }
    unique_ptr<Expression> right(right_ptr);

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  // use AND to conjunct several cmp_expr
  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }

  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  Table      *table       = update_stmt->table();
  TableMeta   table_meta  = table->table_meta();
  FilterStmt *filter_stmt = update_stmt->filter_stmt();

  std::vector<Field> fields(table_meta.field_num() - table_meta.sys_field_num());
  for (int i = table_meta.sys_field_num(), j = 0; i < table_meta.field_num(); ++i, ++j) {
    fields[j] = Field(table, table_meta.field(i));
  }

  // layout: update->filter->scan
  // 1. fetch the records
  unique_ptr<LogicalOperator> scan_op(new TableGetLogicalOperator(table, fields, false));
  unique_ptr<LogicalOperator> filter_op;
  RC                          rc = create_plan(filter_stmt, filter_op);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  // 2. update
  unique_ptr<LogicalOperator> update_op(
      new UpdateLogicalOperator(table, *update_stmt->values(), update_stmt->attribute_name()));

  if (filter_op) {
    filter_op->add_child(std::move(scan_op));
    update_op->add_child(std::move(filter_op));
  } else {
    update_op->add_child(std::move(scan_op));
  }

  logical_operator = std::move(update_op);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt                       *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC                          rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
