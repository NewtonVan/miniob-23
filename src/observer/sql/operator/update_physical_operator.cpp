#include "sql/operator/update_physical_operator.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "sql/expr/expression.h"
#include "sql/parser/value.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(
    Table *table, std::vector<Expression *> &values, std::vector<std::string> &field_names)
    : table_(table), value_exprs_(values), field_names_(field_names), field_metas_(field_names_.size())
{
  const int value_amount = field_names_.size();
  for (int i = 0; i < value_amount; ++i) {
    const FieldMeta *field = table_->table_meta().field(field_names_[i].c_str());
    field_metas_[i]        = field;
  }
}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC                                 rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;
  // gen value
  rc = gen_values();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to generate values: %s", strrc(rc));
    return rc;
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::gen_values()
{
  auto get_cell_for_sub_query = [](const SubQueryExpression *expr, Value &cell) {
    RC rc = expr->open_sub_query();
    if (rc != RC::SUCCESS) {
      LOG_WARN("fail to open sub query: %s", strrc(rc));
      return rc;
    }
    rc = expr->try_get_value(cell);

    if (RC::RECORD_EOF == rc) {
      cell.set_type(AttrType::NULLS);
    } else if (OB_SUCC(rc)) {
      Value tmp;
      if (RC::SUCCESS == (rc = expr->try_get_value(tmp))) {
        LOG_WARN("sub query return multi value in update");
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

  RC     rc            = RC::SUCCESS;
  size_t update_amount = value_exprs_.size();

  for (size_t i = 0; i < update_amount; ++i) {
    Value value;
    if (value_exprs_[i]->type() == ExprType::SUBQUERYTYPE) {
      SubQueryExpression *sub_expr = static_cast<SubQueryExpression *>(value_exprs_[i]);
      if (RC::SUCCESS != (rc = get_cell_for_sub_query(sub_expr, value))) {
        return rc;
      }
      rc = UpdateStmt::cast(field_metas_[i]->nullable(), field_metas_[i]->type(), value.attr_type(), &value);
      if (rc != RC::SUCCESS) {
        LOG_WARN("field type mismatch after exec sub query. table=%s, field=%s, field type=%d, value_type=%d",
            table_->name(), field_names_[i].c_str(), field_metas_[i]->type(), value.attr_type());
        return rc;
      }
    } else {
      ValueExpr *v_expr = static_cast<ValueExpr *>(value_exprs_[i]);
      v_expr->try_get_value(value);
    }
    // TODO(chen): type cast like update_stmt

    values_.push_back(value);
  }

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child        = children_[0].get();
  const int         value_amount = value_exprs_.size();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();

    rc = trx_->update_record(table_, record, values_, field_metas_);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
  }

  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
