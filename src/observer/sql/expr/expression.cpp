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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "common/math/float_tools.h"
#include "common/time/datetime.h"
#include "sql/expr/tuple.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
#include "sql/operator/project_physical_operator.h"
#include "storage/trx/trx.h"
#include "common/global_context.h"
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value) const
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

RC RelAttrExprSqlNode::get_value(const Tuple &tuple, Value &value) const
{
  LOG_ERROR("RelAttrExpr only used as a container in parse stage");
  return RC::INTERNAL;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value) const
{
  value = value_;
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }

  switch (cast_type_) {
    case BOOLEANS: {
      bool val = value.get_boolean();
      cast_value.set_boolean(val);
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported convert from type %d to %d", child_->value_type(), cast_type_);
    }
  }
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &cell) const
{
  RC rc = child_->get_value(tuple, cell);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(cell, cell);
}

RC CastExpr::try_get_value(Value &value) const
{
  RC rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, value);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : comp_(comp), left_(std::move(left)), right_(std::move(right))
{}

ComparisonExpr::~ComparisonExpr() {}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  RC rc = RC::SUCCESS;

  // 左右其中一个为空，且比较符号不是IS_LEFT_NULL和IS_LEFT_NULL，则永远返回false，因为null和任何值比较都返回false
  if (left.attr_type() != right.attr_type() && (left.attr_type() == NULLS || right.attr_type() == NULLS) &&
      comp_ != IS_LEFT_NULL && comp_ != IS_LEFT_NULL) {
    result = false;
    return rc;
  }

  if (left.attr_type() == NULLS && right.attr_type() == NULLS && comp_ != IS_LEFT_NULL && comp_ != IS_LEFT_NULL) {
    result = false;
    return rc;
  }

  int cmp_result = left.compare(right);
  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      LOG_DEBUG("EQUAL_TO cmp_result: %d", cmp_result);
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    case LIKES: {
      result = PerformLikeComparison(left.get_string(), right.get_string());
    } break;
    case NOT_LIKES: {
      result = PerformNotLikeComparison(left.get_string(), right.get_string());
    } break;
    case IS_LEFT_NULL: {
      result = left.attr_type() == NULLS;
    } break;
    case IS_LEFT_NOT_NULL: {
      result = left.attr_type() != NULLS;
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr   *left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr   *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;

  // 当是比较符号是EXISTS或NOT_EXISTS字段时，只需要返回是否存在
  if(comp_ == EXISTS_OP || comp_ == NOT_EXISTS) {
    assert(ExprType::SUBQUERYTYPE == right_->type());
    auto sub_query_expr = (const SubQueryExpression *)(right_.get());
    sub_query_expr->open_sub_query();
    RC tmp_rc = sub_query_expr->get_value(tuple, right_value);
    sub_query_expr->close_sub_query();
    bool res = CompOp::EXISTS_OP == comp_ ? (RC::SUCCESS == tmp_rc) : (RC::RECORD_EOF == tmp_rc);
    value.set_boolean(res);
    return RC::SUCCESS;
  }

  // 当是IN 或 NOT IN时，需要获取子查询的所有tuple的value，然后查看left_value是否存在
  if(comp_ == IN_OP || comp_ == NOT_IN) {
    RC rc = left_->get_value(tuple, left_value);
    if (RC::SUCCESS != rc) {
      return rc;
    }
    if (left_value.is_null()) {
     // 目前默认 null 不在任何value list中
      value.set_boolean(false);
      return RC::SUCCESS;
    }
    std::vector<Value> right_cells;
    right_cells.emplace_back(Value());
    RC tmp_rc = RC::SUCCESS;
    if (ExprType::SUBQUERYTYPE == right_->type()) {
      auto sub_query_expr = (const SubQueryExpression *)(right_.get());
      sub_query_expr->open_sub_query();
      while (RC::SUCCESS == (tmp_rc = sub_query_expr->get_value(tuple, right_cells.back()))) {
        right_cells.emplace_back(Value());
      }
      sub_query_expr->close_sub_query();
      if (RC::RECORD_EOF != tmp_rc) {
        LOG_ERROR("[NOT] IN Get SubQuery Value Failed. RC = %d:%s", tmp_rc, strrc(tmp_rc));
        return tmp_rc;
      }
      // 因为在SubQueryExpression中record_eof时，value为空，所以需要弹出
      right_cells.pop_back();
    }

    auto has_null = [](const std::vector<Value> &values) {
      for (auto &value : values) {
        if (value.is_null()) {
          return true;
        }
      }
      return false;
    };
    bool res = CompOp::IN_OP == comp_ ? left_value.in_cells(right_cells)
                                : (has_null(right_cells) ? false : left_value.not_in_cells(right_cells));
    value.set_boolean(res);
    return RC::SUCCESS;
  }

  auto get_cell_for_sub_query = [](const SubQueryExpression *expr, const Tuple &tuple, Value &cell) {
    expr->open_sub_query();
    RC rc = expr->get_value(tuple, cell);
    if (RC::RECORD_EOF == rc) {
      // e.g. a = select a  -> a = null
      cell.set_null();
    } else if (RC::SUCCESS == rc) {
      Value tmp_cell;
      if (RC::SUCCESS == (rc = expr->get_value(tuple, tmp_cell))) {
        // e.g. a = select a  -> a = (1, 2, 3)
        // std::cout << "Should not have rows more than 1" << std::endl;
        expr->close_sub_query();
        return RC::INTERNAL;
      }
    } else {
      expr->close_sub_query();
      return rc;
    }
    expr->close_sub_query();
    return RC::SUCCESS;
  };

  RC rc = RC::SUCCESS;
  if (ExprType::SUBQUERYTYPE == left_->type()) {
    if (RC::SUCCESS != (rc = get_cell_for_sub_query((const SubQueryExpression *)(left_.get()), tuple, left_value))) {
      LOG_ERROR("Predicate get left cell for sub_query failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  } else {
    if (RC::SUCCESS != (rc = left_->get_value(tuple, left_value))) {
      LOG_ERROR("Predicate get left cell failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  }

  if (ExprType::SUBQUERYTYPE == right_->type()) {
    if (RC::SUCCESS != (rc = get_cell_for_sub_query((const SubQueryExpression *)(right_.get()), tuple, right_value))) {
      LOG_ERROR("Predicate get right cell for sub_query failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  } else {
    if (RC::SUCCESS != (rc = right_->get_value(tuple, right_value))) {
      LOG_ERROR("Predicate get right cell failed. RC = %d:%s", rc, strrc(rc));
      return rc;
    }
  }

  rc = left_->get_value(tuple, left_value);

  if (rc == RC::INTERNAL_DIV_ZERO) {
    value.set_boolean(false);
    return RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc == RC::INTERNAL_DIV_ZERO) {
    value.set_boolean(false);
    return RC::SUCCESS;
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc              = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();

  switch (arithmetic_type_) {
    case Type::ADD: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() + right_value.get_int());
      } else {
        value.set_float(left_value.get_float() + right_value.get_float());
      }
    } break;

    case Type::SUB: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() - right_value.get_int());
      } else {
        value.set_float(left_value.get_float() - right_value.get_float());
      }
    } break;

    case Type::MUL: {
      if (target_type == AttrType::INTS) {
        value.set_int(left_value.get_int() * right_value.get_int());
      } else {
        value.set_float(left_value.get_float() * right_value.get_float());
      }
    } break;

    case Type::DIV: {
      if (target_type == AttrType::INTS) {
        if (right_value.get_int() == 0) {
          // NOTE:
          // 设置为整数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为整数最大值。
          value.set_int(numeric_limits<int>::max());
          return RC::INTERNAL_DIV_ZERO;
        } else {
          value.set_int(left_value.get_int() / right_value.get_int());
        }
      } else {
        if (right_value.get_float() > -EPSILON && right_value.get_float() < EPSILON) {
          // NOTE:
          // 设置为浮点数最大值是不正确的。通常的做法是设置为NULL，但是当前的miniob没有NULL概念，所以这里设置为浮点数最大值。
          value.set_float(numeric_limits<float>::max());
          return RC::INTERNAL_DIV_ZERO;
        } else {
          value.set_float(left_value.get_float() / right_value.get_float());
        }
      }
    } break;

    case Type::NEGATIVE: {
      if (target_type == AttrType::INTS) {
        value.set_int(-left_value.get_int());
      } else {
        value.set_float(-left_value.get_float());
      }
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  if (arithmetic_type_ != ArithmeticExpr::Type::NEGATIVE) {
    rc = right_->get_value(tuple, right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

FuncExpr::FuncExpr(FuncExpr::FuncType type, std::vector<std::unique_ptr<Expression>> &args)
    : func_type_(type), args_(std::move(args))
{}

AttrType FuncExpr::value_type() const
{
  AttrType type = AttrType::UNDEFINED;
  switch (func_type_) {
    case FuncType::LENGTH: {
      type = AttrType::INTS;
      LOG_DEBUG("length func, type: %d", type);
    } break;
    case FuncType::ROUND: {
      type = AttrType::FLOATS;
      LOG_DEBUG("round func, type: %d", type);
    } break;
    case FuncType::DATE_FORMAT: {
      type = AttrType::CHARS;
      LOG_DEBUG("date_format func, type: %d", type);
    } break;
  }

  return type;
}

RC FuncExpr::get_value(const Tuple &tuple, Value &value) const
{
  RC rc = RC::SUCCESS;

  std::vector<Value> args_values;
  for (int i = 0; i < args_.size(); ++i) {
    Value v;
    rc = args_[i]->get_value(tuple, v);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of %d expression. rc=%s", i, strrc(rc));
      return rc;
    }
    args_values.emplace_back(std::move(v));
  }

  return eval_func(args_values, value);
}

RC FuncExpr::eval_func(std::vector<Value> &args, Value &value) const
{
  RC rc = RC::SUCCESS;

  switch (func_type_) {
    case FuncType::LENGTH: {
      std::string str = args[0].get_string();
      value.set_int(str.length());
    } break;
    case FuncType::ROUND: {
      float num     = args[0].get_float();
      int   bits    = args.size() == 2 ? args[1].get_int() : 0;
      float rnd_num = common::roundToNDecimalPlaces(num, bits);
      LOG_DEBUG("%f round to %f", num, rnd_num);
      value.set_float(rnd_num);
    } break;
    case FuncType::DATE_FORMAT: {
      int64_t date = 0;
      if (args[0].attr_type() == AttrType::CHARS) {
        if (!serialize_date(&date, args[0].get_string().c_str())) {
          LOG_WARN("fail to serialize %s", args[0].get_string().c_str());
        }
      } else if (args[0].attr_type() == AttrType::DATES || args[0].attr_type() == AttrType::INTS) {
        date = args[0].get_date();
      } else {
        LOG_WARN("unknown format: %d", args[0].attr_type());
        return RC::INVALID_ARGUMENT;
      }
      const std::string format = args[1].get_string();
      std::string       formatted_date(common::DateTime::format_date(deserialize_date_ts(date), format));
      if (formatted_date.empty()) {
        LOG_WARN("invalid date/format, date: %d, format: %s", date, format.c_str());
        return RC::INTERNAL;
      }
      value.set_string(formatted_date.c_str(), formatted_date.length());
      return RC::SUCCESS;
    } break;
    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported func type. %d", func_type_);
    } break;
  }

  return rc;
}

RC FuncExpr::try_get_value(Value &value) const
{
  RC                 rc = RC::SUCCESS;
  std::vector<Value> args_values;
  for (int i = 0; i < args_.size(); ++i) {
    Value v;
    rc = args_[i]->try_get_value(v);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to try get value of %d expression. rc=%s", i, strrc(rc));
      return rc;
    }
    args_values.emplace_back(std::move(v));
  }

  return eval_func(args_values, value);
}



RC SubQueryExpression::open_sub_query() const
{
  assert(nullptr != sub_physical_op_oper_);
  return sub_physical_op_oper_->open(GCTX.trx_kit_->create_trx(db_->clog_manager()));
}

RC SubQueryExpression::close_sub_query() const
{
  assert(nullptr != sub_physical_op_oper_);
  return sub_physical_op_oper_->close();
}

RC SubQueryExpression::get_value(const Tuple &tuple, Value &value) const
{
  assert(nullptr != sub_physical_op_oper_);
  sub_physical_op_oper_->set_parent_tuple(&tuple);  // set parent tuple
  RC rc = sub_physical_op_oper_->next();
  // TODO: hyq note
  if (RC::RECORD_EOF == rc) {
    value.set_null();
  }
  if (RC::SUCCESS != rc) {
    return rc;
  }
  Tuple *child_tuple = sub_physical_op_oper_->current_tuple();
  if (nullptr == child_tuple) {
    LOG_WARN("failed to get current record. rc=%s", strrc(rc));
    return RC::INTERNAL;
  }
  rc = child_tuple->cell_at(0, value);  // only need the first cell
  return rc;
}

RC SubQueryExpression::create_expression(const std::unordered_map<std::string, Table *> &table_map,
    const std::vector<Table *> &tables, CompOp comp, Db *db) {
  Stmt *stmt = nullptr;
  RC rc = SelectStmt::create(db, *select_sql_node_, stmt);
  this->set_sub_query_stmt((SelectStmt *)stmt);
  if (RC::SUCCESS != rc) {
    LOG_ERROR("SubQueryExpression Create SelectStmt Failed. RC = %d:%s", rc, strrc(rc));
    return rc;
  }
  db_ = db;
}