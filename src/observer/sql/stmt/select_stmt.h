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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt 
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);

public:
  struct agg_field {
    AggFuncType func_;
    Field field_;
    // whether initial field is star
    bool field_is_star = false;
    agg_field(AggFuncType func, const Field& field):func_(func), field_(field) {};
    static std::string name(AggFuncType func) {
      switch (func) {
      case AggFuncType::COUNT_FUNC:
        return {"COUNT"};
        break;
      case AggFuncType::SUM_FUNC:
        return {"SUM"};
        break;
      case AggFuncType::MAX_FUNC:
        return {"MAX"};
        break;
      case AggFuncType::MIN_FUNC:
        return {"MIN"};
        break;
      case AggFuncType::AVG_FUNC:
        return {"AVG"};
        break;
      }
    }
  };
  bool is_agg() {
    return is_agg_;
  }
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  const std::vector<Field> &query_fields() const
  {
    return query_fields_;
  }
  const std::vector<agg_field>& all_agg_fields() const 
  {
    return agg_fields_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }

private:
  std::vector<Field> query_fields_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
  // whether select has agg func 
  bool is_agg_; 
  std::vector<agg_field> agg_fields_;
};
