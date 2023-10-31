//
// Created by hyq on 10/29/23.
//

#ifndef MINIDB_SORT_PHYSICAL_OPERAOTR_H
#define MINIDB_SORT_PHYSICAL_OPERAOTR_H

#include "sql/operator/physical_operator.h"

class OrderByStmt;

class SortPhysicalOperator : public PhysicalOperator {
public:
  SortPhysicalOperator(Table *table, OrderByStmt *order_stmt) : table_(table), orderby_stmt_(order_stmt) {}

  virtual ~SortPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::SORT; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

  void add_spec(const Table *table, const FieldMeta *field_meta);

private:
  RC fetch_table();


private:
  Table* table_ = nullptr;
  OrderByStmt *orderby_stmt_ = nullptr;
  std::vector<std::shared_ptr<TupleCellSpec>> specs_;

  bool is_first_ = true;
  std::vector<SortTuple> tuples_;
  std::vector<int> ordered_idx_;
  int it_;
};
#endif  // MINIDB_SORT_PHYSICAL_OPERAOTR_H
