#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"

#pragma once
class AggLogicalOperator : public LogicalOperator {
    public:
        AggLogicalOperator(const std::vector<SelectStmt::agg_field>& fields):fields_(fields){};
        virtual ~AggLogicalOperator() = default;
        LogicalOperatorType type() const override {
            return LogicalOperatorType::AGG;
        }
        std::vector<std::unique_ptr<Expression>> &expressions()
        {
            return expressions_;
        }
        const std::vector<std::unique_ptr<Expression>> &expressions() const
        {
            return expressions_;
        }
    
        std::vector<SelectStmt::agg_field> fields_;    
};