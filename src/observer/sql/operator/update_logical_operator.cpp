#include "sql/operator/update_logical_operator.h"
#include <string>

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Value value, std::string field_name)
    : table_(table), value_(value), field_name_(field_name)
{}
