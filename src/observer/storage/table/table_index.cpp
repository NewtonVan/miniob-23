
#include "storage/table/table_index.h"

bool TableIndex::is_conflict(Record &record) { return is_conflict(record.data()); }

bool TableIndex::is_conflict(char *data)
{
  if (!unique_) {
    return false;
  }

  const FieldMeta *null_field = table_->null_mask_field();
  common::Bitmap   bitmap(data + null_field->offset(), null_field->len());

  std::vector<std::vector<std::string>> rid_set_group;
  const int                             idx_num = index_group_.size();
  for (int i = 0; i < idx_num; ++i) {
    if (bitmap.get_bit(index_field_order_[i])) {
      // uniq index exist null, there won't be conflic
      return false;
    }
    std::list<RID> rid_set;
    if (index_group_[i]->get_entry(data, rid_set) == RC::SUCCESS) {
      std::vector<std::string> rid_str(rid_set.size());
      int                      i = 0;
      for (const RID &rid : rid_set) {
        rid_str[i++] = rid.to_id();
      }
      rid_set_group.push_back(std::move(rid_str));
    } else {
      return false;
    }
  }

  return interaction_group(rid_set_group);
}

bool TableIndex::interaction_group(std::vector<std::vector<std::string>> group)
{
  if (group.size() == 1) {
    // only one idx
    return true;
  }

  std::unordered_set<std::string> common_ids[2];
  common_ids[0] = std::unordered_set<std::string>(group[0].begin(), group[0].end());
  int cur       = 0;

  for (size_t i = 1; i < group.size(); ++i) {
    std::unordered_set<std::string> current(group[i].begin(), group[i].end());
    for (const std::string &s : common_ids[cur]) {
      if (current.count(s) > 0) {
        common_ids[cur ^ 1].insert(s);
      }
    }
    common_ids[cur].clear();
    cur ^= 1;
    if (common_ids[cur].empty()) {
      return false;
    }
  }

  return true;
}