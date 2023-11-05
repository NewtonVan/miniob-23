
#pragma once

/**
 * @brief 记录multi idx和相关索引信息，在此前旧代码上不得已为之
 * @ingroup Index
 */
#include "storage/index/index.h"
#include "storage/table/table_meta.h"

class TableIndex
{
public:
  TableIndex(std::vector<Index *> index_group, bool uniq, TableMeta *table, std::vector<int> index_field_order)
      : index_group_(index_group), unique_(uniq), table_(table), index_field_order_(index_field_order)
  {}
  bool is_unique() const { return unique_; }
  bool is_conflict(Record &record);
  bool is_conflict(char *data);
  bool interaction_group(std::vector<std::vector<std::string>> group);

private:
  std::vector<Index *> index_group_;
  bool                 unique_ = false;
  TableMeta           *table_  = nullptr;
  std::vector<int>     index_field_order_;
};