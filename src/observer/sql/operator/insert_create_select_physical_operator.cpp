//
// Created by hyq on 11/5/23.
//

#include "sql/operator/insert_create_select_physical_operator.h"
#include "sql/operator/project_physical_operator.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

RC InsertCreateSelectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;
  return RC::SUCCESS;
}

RC InsertCreateSelectPhysicalOperator::next()
{
  if(is_first_) {
    ProjectPhysicalOperator* projectOp = static_cast<ProjectPhysicalOperator*>(children_[0].get());

    // 创建表
    if(!projectOp->expressions().empty()) {
      int attr_count = projectOp->expressions().size();
      std::vector<AttrInfoSqlNode> attr_infos(attr_count);
      for(int i = 0; i < attr_count; i++) {
        for(int i = 0; i < attr_count; i++) {
          attr_infos[i].type = projectOp->expressions()[i]->value_type();
          attr_infos[i].null = false;
          attr_infos[i].length = 4;
          attr_infos[i].name = projectOp->expressions()[i]->name();
        }
        db_->create_table(table_name_.c_str(), attr_count, attr_infos.data());
        is_first_ = false;
        table_ = db_->find_table(table_name_.c_str());
      }
    } else {
      int attr_count = fields_.size();
      std::vector<AttrInfoSqlNode> attr_infos(attr_count);
      for(int i = 0; i < attr_count; i++) {
        attr_infos[i].type = fields_[i].meta()->type();
        attr_infos[i].null = fields_[i].meta()->nullable();
        attr_infos[i].length = fields_[i].meta()->len();
        attr_infos[i].name = fields_[i].field_name();
      }
      db_->create_table(table_name_.c_str(), attr_count, attr_infos.data());
      is_first_ = false;
      table_ = db_->find_table(table_name_.c_str());
    }
  }

  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  RC rc = RC::SUCCESS;
  // 一次全部取出
  while(RC::SUCCESS == (rc = children_[0]->next())) {
    std::vector<Value> values;
    Tuple    *tuple    = children_[0]->current_tuple();
    const int cell_num = tuple->cell_num();
    Value     cell;
    for (int i = 0; i < cell_num; ++i) {
      if (tuple->cell_at(i, cell) != RC::SUCCESS) {
        return RC::RECORD_EOF;
      }
      values.push_back(cell);
    }
    rc = make_record(values);
    if(rc != RC::SUCCESS) {
      return rc;
    }
  }
  return RC::RECORD_EOF;
}

RC InsertCreateSelectPhysicalOperator::make_record(std::vector<Value>& values) {
  Record record;
  RC rc = table_->make_record(static_cast<int>(values.size()), values.data(), record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to make record. rc=%s", strrc(rc));
    return rc;
  }

  rc = trx_->insert_record(table_, record);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
  }
  return rc;
}

RC InsertCreateSelectPhysicalOperator::close()
{
  return RC::SUCCESS;
}