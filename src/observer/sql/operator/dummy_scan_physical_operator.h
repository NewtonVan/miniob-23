#pragma once

#include "common/rc.h"
#include "sql/operator/physical_operator.h"
class DummyScanPhysicalOperator : public PhysicalOperator
{
public:
  DummyScanPhysicalOperator()          = default;
  virtual ~DummyScanPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::DUMMY; }

  RC open(Trx *trx) override { return RC::SUCCESS; }
  RC next() override
  {
    RC rc = RC::DUMMY_SUCCESS;
    if (emitted_) {
      return RC::RECORD_EOF;
    }
    emitted_ = true;

    return rc;
  }
  RC close() override { return RC::SUCCESS; }

  int cell_num() const { return 0; }

  Tuple *current_tuple() override
  {
    // TODO(chen): add null tuple?
    return nullptr;
  }

private:
  bool emitted_ = false;
};