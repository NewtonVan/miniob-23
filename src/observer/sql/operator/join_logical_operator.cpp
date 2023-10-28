
#include "sql/operator/join_logical_operator.h"
#include "common/rc.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/filter_stmt.h"
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>
JoinLogicalOperator::JoinLogicalOperator(std::unique_ptr<Expression> expression)
{
  expressions_.emplace_back(std::move(expression));
}

// TODO(chen): should be classified in rewrite stage
RC JoinLogicalOperator::push_down_predicate(PredicateLogicalOperator *predicate)
{
  RC                                        rc          = RC::SUCCESS;
  std::vector<std::unique_ptr<Expression>> &expressions = predicate->expressions();
  ASSERT(expressions.size() == 1, "predicate logical operator's children should be 1");

  std::unique_ptr<Expression> &expression = expressions.front();

  ASSERT(children_.size() == 2, "join logical operator's children should be 2");
  std::unique_ptr<LogicalOperator> &left  = children_[0];
  std::unique_ptr<LogicalOperator> &right = children_[1];

  if (left->type() == LogicalOperatorType::TABLE_GET) {
    std::vector<std::unique_ptr<Expression>> pushdown_exprs;
    TableGetLogicalOperator                 *single_table = static_cast<TableGetLogicalOperator *>(left.get());
    rc = get_exprs_can_pushdown(single_table, expression, pushdown_exprs);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to push down to single table. rc=%s", strrc(rc));
      return rc;
    }
    if (!pushdown_exprs.empty()) {
      single_table->set_predicates(std::move(pushdown_exprs));
    }

  } else if (left->type() == LogicalOperatorType::JOIN) {
    JoinLogicalOperator *join_child = static_cast<JoinLogicalOperator *>(left.get());
    rc                              = join_child->push_down_predicate(predicate);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to push down to child join. rc=%s", strrc(rc));
      return rc;
    }
  }

  if (right->type() == LogicalOperatorType::TABLE_GET) {
    std::vector<std::unique_ptr<Expression>> pushdown_exprs;
    TableGetLogicalOperator                 *single_table = static_cast<TableGetLogicalOperator *>(right.get());
    rc = get_exprs_can_pushdown(single_table, expression, pushdown_exprs);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to push down to single table. rc=%s", strrc(rc));
      return rc;
    }
    if (!pushdown_exprs.empty()) {
      single_table->set_predicates(std::move(pushdown_exprs));
    }

  } else if (right->type() == LogicalOperatorType::JOIN) {
    JoinLogicalOperator *join_child = static_cast<JoinLogicalOperator *>(right.get());
    rc                              = join_child->push_down_predicate(predicate);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to push down to child join. rc=%s", strrc(rc));
      return rc;
    }
  }

  if (!expression) {
    // 所有的表达式都下推到了下层算子
    // 这个predicate operator其实就可以不要了。但是这里没办法删除，弄一个空的表达式吧
    LOG_TRACE("all expressions of predicate operator were pushdown to table get operator, then make a fake one");

    Value value((bool)true);
    expression = std::unique_ptr<Expression>(new ValueExpr(value));
  }

  return RC::SUCCESS;
}

RC JoinLogicalOperator::get_exprs_can_pushdown(TableGetLogicalOperator *single_table, std::unique_ptr<Expression> &expr,
    std::vector<std::unique_ptr<Expression>> &pushdown_exprs)
{
  RC rc = RC::SUCCESS;
  if (expr->type() == ExprType::CONJUNCTION) {
    ConjunctionExpr *conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());
    // 或 操作的比较，太复杂，现在不考虑
    if (conjunction_expr->conjunction_type() == ConjunctionExpr::Type::OR) {
      return rc;
    }

    std::vector<std::unique_ptr<Expression>> &child_exprs = conjunction_expr->children();
    for (auto iter = child_exprs.begin(); iter != child_exprs.end();) {
      // 对每个子表达式，判断是否可以下放到table get 算子
      // 如果可以的话，就从当前孩子节点中删除他
      rc = get_exprs_can_pushdown(single_table, *iter, pushdown_exprs);
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to get pushdown expressions. rc=%s", strrc(rc));
        return rc;
      }

      if (!*iter) {
        child_exprs.erase(iter);
      } else {
        ++iter;
      }
    }
  } else if (expr->type() == ExprType::COMPARISON) {
    // 如果是比较操作，并且比较的左边或右边是表某个列值，那么就下推下去
    auto   comparison_expr = static_cast<ComparisonExpr *>(expr.get());
    CompOp comp            = comparison_expr->comp();
    if (comp != EQUAL_TO && comp != LESS_EQUAL && comp != NOT_EQUAL && comp != LESS_THAN && comp != GREAT_EQUAL &&
        comp != GREAT_THAN) {
      // FIXME
      // 简单比较。当然还可以取一些范围比较，还有 like % 等操作
      // 其它的还有 is null 等
      return rc;
    }

    std::unique_ptr<Expression> &left_expr  = comparison_expr->left();
    std::unique_ptr<Expression> &right_expr = comparison_expr->right();
    // 比较操作的左右两边只要有一个是取列字段值的并且另一边也是取字段值或常量，就pushdown
    if (left_expr->type() != ExprType::FIELD && right_expr->type() != ExprType::FIELD) {
      return rc;
    }
    if (left_expr->type() != ExprType::FIELD && left_expr->type() != ExprType::VALUE &&
        right_expr->type() != ExprType::FIELD && right_expr->type() != ExprType::VALUE) {
      return rc;
    }

    // predicate should be related to `single_table`
    const char *table_name = single_table->table()->name();
    if (left_expr->type() == ExprType::FIELD) {
      FieldExpr *field_expr = static_cast<FieldExpr *>(left_expr.get());
      if (0 != strcmp(table_name, field_expr->table_name())) {
        return rc;
      }
    }
    if (right_expr->type() == ExprType::FIELD) {
      FieldExpr *field_expr = static_cast<FieldExpr *>(right_expr.get());
      if (0 != strcmp(table_name, field_expr->table_name())) {
        return rc;
      }
    }

    pushdown_exprs.emplace_back(std::move(expr));
  }
  return rc;
}