#include "sql/operator/update_logical_operator.h"
#include <string>

UpdateLogicalOperator::UpdateLogicalOperator(
    Table *table, std::vector<Expression *> values, std::vector<std::string> field_names)
    : table_(table), values_(values), field_names_(field_names)
{}
