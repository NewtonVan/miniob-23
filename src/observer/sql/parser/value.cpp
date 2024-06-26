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
// Created by WangYunlai on 2023/06/28.
//

#include <cstdint>
#include <sstream>
#include <sys/types.h>
#include <string>
#include <regex>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "floats", "texts", "nulls", "booleans"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= NULLS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

bool deserialize_date(char *out, size_t len_out, int in)
{
  const time_t ONE_DAY = 24 * 60 * 60;
  tm           timeinfo{};
  // 1970-01-01
  timeinfo.tm_year = 70;
  timeinfo.tm_mon  = 0;
  timeinfo.tm_mday = 1;
  time_t t         = mktime(&timeinfo) + in * ONE_DAY;
  strftime(out, len_out, "%F", localtime(&t));
  return true;
}

time_t deserialize_date_ts(int64_t in)
{
  const time_t ONE_DAY = 24 * 60 * 60;
  tm           timeinfo{};
  // 1970-01-01
  timeinfo.tm_year = 70;
  timeinfo.tm_mon  = 0;
  timeinfo.tm_mday = 1;
  time_t t         = mktime(&timeinfo) + in * ONE_DAY;
  return t;
}

bool serialize_date(int64_t *out, const char *in)
{
  int year = 0, month = 0, day = 0;
  enum State
  {
    YEAR = 0,
    MONTH,
    DAY
  };
  State s = YEAR;
  for (int i = 0; in[i] != '\0'; i++) {
    if (isdigit(in[i])) {
      switch (s) {
        case YEAR:
          year *= 10;
          year += in[i] - '0';
          break;
        case MONTH:
          month *= 10;
          month += in[i] - '0';
          break;
        case DAY:
          day *= 10;
          day += in[i] - '0';
          break;
      }
    } else if (in[i] == '-') {
      s = (State)(s + 1);
    } else {
      return false;
    }
  }

  if (s != DAY) {
    return false;
  }

  if (month < 1 || month > 12) {
    return false;
  }

  // Check for the number of days in the given month, accounting for leap years
  int maxDays = 31;
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    maxDays = 30;
  } else if (month == 2) {
    maxDays = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
  }

  if (day < 1 || day > maxDays) {
    return false;
  }

  tm input_date{};
  year -= 1900;
  input_date.tm_year = year;
  month -= 1;
  input_date.tm_mon  = month;
  input_date.tm_mday = day;
  time_t input_time  = mktime(&input_date);
  if (input_time == -1 || input_date.tm_year != year || input_date.tm_mon != month || input_date.tm_mday != day) {
    return false;
  }

  tm origin{};
  // 1970-01-01
  origin.tm_year     = 70;
  origin.tm_mon      = 0;
  origin.tm_mday     = 1;
  time_t origin_time = mktime(&origin);

  const time_t ONE_DAY = 24 * 60 * 60;
  *out                 = (int64_t)((input_time - origin_time) / ONE_DAY);
  return true;
}

bool PerformLikeComparison(const std::string &left, const std::string &right)
{
  if (right.find("%") != std::string::npos || right.find("_") != std::string::npos) {
    std::string pattern = right;
    // Escape any regex metacharacters in the pattern.
    pattern = std::regex_replace(pattern, std::regex("([.\\^$|()\\[\\]{}+*?])"), "\\$1");
    // Replace % with .* and _ with .
    pattern = std::regex_replace(pattern, std::regex("%"), ".*");
    pattern = std::regex_replace(pattern, std::regex("_"), ".");
    // Create a regex pattern with anchors to ensure exact matching.
    std::string regex_pattern = "^" + pattern + "$";
    std::regex  regex(regex_pattern);
    return std::regex_search(left, regex);
  } else {
    return (left == right);
  }
}

bool PerformNotLikeComparison(const std::string &left, const std::string &right)
{
  if (right.find("%") != std::string::npos || right.find("_") != std::string::npos) {
    std::string pattern = right;
    // Escape any regex metacharacters in the pattern.
    pattern = std::regex_replace(pattern, std::regex("([.\\^$|()\\[\\]{}+*?])"), "\\$1");
    // Replace % with .* and _ with .
    pattern = std::regex_replace(pattern, std::regex("%"), ".*");
    pattern = std::regex_replace(pattern, std::regex("_"), ".");
    // Create a regex pattern with anchors to ensure exact matching.
    std::string regex_pattern = "^" + pattern + "$";
    std::regex  regex(regex_pattern);
    return !std::regex_search(left, regex);
  } else {
    return (left != right);
  }
}

Value::Value(int val) { set_int(val); }

Value::Value(int64_t val) { set_date(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case DATES: {
      num_value_.date_value_ = *(int64_t *)data;
      length_                = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case TEXTS: {
      set_text(data);
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_date(int64_t val)
{
  attr_type_             = DATES;
  num_value_.date_value_ = val;
  length_                = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}

void Value::set_text(const char *s)
{
    attr_type_ = TEXTS;
    if (!text_value_) {
    // 分配内存，根据需要分配 MAX_TEXT_SIZE 大小的内存
      text_value_ = new char[MAX_TEXT_SIZE];
    }
    strncpy(text_value_, s, MAX_TEXT_SIZE-1);
    text_value_[MAX_TEXT_SIZE-1] = '\0'; // 确保字符数组以 null 终止
    length_ = MAX_TEXT_SIZE;
}

void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}

void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case DATES: {
      set_date(value.get_date());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case TEXTS: {
      set_text(value.get_text());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
    case NULLS:
      break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    case TEXTS: {
      if (text_value_) {
        return text_value_;
      } else {
        return nullptr;
      }
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case TEXTS: {
      std::string text = text_value_;
      std::transform(text.begin(), text.end(), text.begin(), ::toupper);  // 转换为大写
      os << text;
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case DATES: {
      char buf[11];
      deserialize_date(buf, sizeof(buf), num_value_.date_value_);
      os << buf;
    } break;
    case NULLS: {
      os << "null";
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  LOG_DEBUG("Value::compare this->attr_type_=%d, other.attr_type_=%d", this->attr_type_, other.attr_type_);
  if (this->attr_type_ == other.attr_type_) {
    LOG_DEBUG("same type");
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case DATES: {
        return common::compare_date((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case TEXTS: {
        return common::compare_string(
            (void *)this->text_value_, strlen(this->text_value_), (void *)other.text_value_, strlen(other.text_value_));
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case NULLS: {
        return false;
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data = common::str_prefix_double(this->str_value_);
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data = common::str_prefix_double(other.str_value_);
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    float this_data  = common::str_prefix_double(this->str_value_);
    float other_data = other.get_int();
    return common::compare_float((void *)&this_data, (void *)&other_data);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    float this_data  = this->get_int();
    float other_data = common::str_prefix_double(other.get_string());
    return common::compare_float((void *)&this_data, (void *)&other_data);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case DATES: {
      return int(num_value_.date_value_);
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

int64_t Value::get_date() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int64_t)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return (int64_t)(num_value_.int_value_);
    }
    case DATES: {
      return num_value_.date_value_;
    }
    case FLOATS: {
      return (int64_t)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int64_t)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case DATES: {
      return float(num_value_.date_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

const char *Value::get_text() const { return text_value_; }

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case DATES: {
      return num_value_.date_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}