#include <vector>
#include <memory>

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"

#pragma once
class AggLogicalOperator : public LogicalOperator {
    public:
        explicit AggLogicalOperator(const std::vector<AggType>& agg_types, const std::vector<Field>& fields, const std::vector<Field>& groub_bys, const std::vector<std::string>& all_agg_expr_name):agg_types_(agg_types), fields_(fields),group_bys_(groub_bys), agg_expr_names_(all_agg_expr_name) {};
        virtual ~AggLogicalOperator() = default;

        // void add_expressions(std::vector<std::unique_ptr<Expression>>&& expressions) {
        //     for(auto& expr : expressions) {
        //         expressions_.push_back(expr);
        //     }
        // }

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
        std::vector<AggType>& agg_types() {
            return agg_types_;
        }
        const std::vector<Field>& fields() const {
            return fields_;
        }
        const std::vector<Field>& group_bys() const {
            return group_bys_;
        }
        const std::vector<std::string>& agg_expr_names() const {
            return agg_expr_names_;
        }

    private:    
        std::vector<AggType> agg_types_;
        std::vector<std::string> agg_expr_names_;
        std::vector<Field> fields_; 
        std::vector<Field> group_bys_;   
};