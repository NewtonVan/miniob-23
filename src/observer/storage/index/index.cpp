/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by wangyunlai.wyl on 2021/5/19.
//

#include "storage/index/index.h"
#include "common/rc.h"
#include "storage/record/record.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

RC Index::init(const IndexMeta &index_meta, const FieldMeta &field_meta)
{
  index_meta_ = index_meta;
  field_meta_ = field_meta;
  return RC::SUCCESS;
}

bool TableIndex::is_conflict(Record &record) { return is_conflict(record.data()); }

bool TableIndex::is_conflict(const char *data)
{
  if (!unique_) {
    return false;
  }

  std::vector<std::vector<std::string>> rid_set_group;
  for (Index *index : index_group_) {
    std::list<RID> rid_set;
    if (index->get_entry(data, rid_set) == RC::SUCCESS) {
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