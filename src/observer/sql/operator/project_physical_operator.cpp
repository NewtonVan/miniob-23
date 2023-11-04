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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/tuple_cell.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include <memory>

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  RC rc = children_[0]->next();
  if (RC::DUMMY_SUCCESS == rc) {
    Tuple    *tuple    = current_tuple();
    const int cell_num = tuple->cell_num();
    Value     cell;
    for (int i = 0; i < cell_num; ++i) {
      if (tuple->cell_at(i, cell) != RC::SUCCESS) {
        return RC::RECORD_EOF;
      }
    }
    return RC::SUCCESS;
  }

  return rc;
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  if (use_project_exprs()) {
    expression_tuple_->set_tuple(children_[0]->current_tuple());
    tuple_.set_tuple(expression_tuple_);
  } else {
    tuple_.set_tuple(children_[0]->current_tuple());
  }
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(const Table *table, const FieldMeta *field_meta)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(table->name(), field_meta->name(), field_meta->name());
  tuple_.add_cell_spec(spec);
}

void ProjectPhysicalOperator::init_specs()
{
  for (std::unique_ptr<Expression> &expr : expressions_) {
    if (expr->type() == ExprType::FIELD) {
      FieldExpr *field_expr = static_cast<FieldExpr *>(expr.get());
      // TODO(chen): add alias
      TupleCellSpec *spec =
          new TupleCellSpec(field_expr->table_name(), field_expr->field_name(), field_expr->name().c_str());
      tuple_.add_cell_spec(spec);
    } else if (expr->type() == ExprType::ARITHMETIC) {
      ArithmeticExpr *arithmetic = static_cast<ArithmeticExpr *>(expr.get());
      TupleCellSpec  *spec       = new TupleCellSpec("", "", arithmetic->name().c_str());
      tuple_.add_cell_spec(spec);
    } else if (expr->type() == ExprType::FUNCTION) {
      FuncExpr      *func = static_cast<FuncExpr *>(expr.get());
      TupleCellSpec *spec = new TupleCellSpec("", "", func->name().c_str());
      tuple_.add_cell_spec(spec);
    } else if (expr->type() == ExprType::AGG) {
      AggExpr       *agg_expr = static_cast<AggExpr *>(expr.get());
      TupleCellSpec *spec     = new TupleCellSpec("", "", agg_expr->name().c_str());
      tuple_.add_cell_spec(spec);
    }
    // TODO(chen):
  }
}