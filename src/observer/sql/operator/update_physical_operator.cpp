#include "sql/operator/update_physical_operator.h"
#include "sql/parser/value.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"
#include <cstdint>
#include <string>
#include <variant>
#include <vector>

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(
    Table *table, std::vector<Value> &values, std::vector<std::string> &field_names)
    : table_(table), values_(values), field_names_(field_names)
{}

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

  return RC::SUCCESS;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child        = children_[0].get();
  const int         value_amount = values_.size();
  std::vector<int>  offsets(value_amount);
  std::vector<int>  lens(value_amount);
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();

    for (int i = 0; i < value_amount; ++i) {
      const FieldMeta *field = table_->table_meta().field(field_names_[i].c_str());
      offsets[i]             = field->offset();
      lens[i]                = field->len();
    }

    rc = trx_->update_record(table_, record, values_, offsets, lens);
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
