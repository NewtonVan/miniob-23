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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include "common/defs.h"
#include "common/log/log.h"
#include <bits/stdint-intn.h>
#include <string>
#include <cstdint>
#include "math.h"
#include "util.h"


/**
 * @brief 属性的类型
 *
 */
enum AttrType
{
  UNDEFINED,
  CHARS,   ///< 字符串类型
  INTS,    ///< 整数类型(4字节)
  DATES,   ///< 日期类型
  FLOATS,  ///< 浮点数类型(4字节)
  TEXTS,   ///< 文本类型
  NULLS,
  BOOLEANS,  ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
};

const char *attr_type_to_string(AttrType type);
AttrType    attr_type_from_string(const char *s);

bool   deserialize_date(char *out, size_t len_out, int in);
time_t deserialize_date_ts(int64_t in);
bool   serialize_date(int64_t *out, const char *in);
bool   PerformLikeComparison(const std::string &left, const std::string &right);
bool   PerformNotLikeComparison(const std::string &left, const std::string &right);

/**
 * @brief 属性的值
 *
 */
class Value
{
public:
  Value() = default;

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type) { this->set_data(data, length); }

//  ~Value() {
//    if (text_value_) {
//      delete[] text_value_;
//    }
//  }

  void clearTextValue() {
    if (text_value_) {
      delete[] text_value_;
      text_value_ = nullptr; // 将指针设置为 nullptr，以避免悬挂指针
    }
  }

  explicit Value(int val);
  explicit Value(int64_t val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0);
  //  explicit Value(const char *s, int len = 4096, AttrType attr_type = TEXTS);

  Value(const Value &other)            = default;
  Value &operator=(const Value &other) = default;

  void set_null()
  {
    this->attr_type_ = AttrType::NULLS;
  }
  void set_type(AttrType type) { this->attr_type_ = type; }
  void set_data(char *data, int length);
  void set_data(const char *data, int length) { this->set_data(const_cast<char *>(data), length); }
  void set_int(int val);
  void set_date(int64_t val);
  void set_float(float val);
  void set_text(const char *s);
  void set_boolean(bool val);
  void set_string(const char *s, int len = 0);
  void set_value(const Value &value);

  bool is_null() const {
    return attr_type() == AttrType::NULLS;

  }

  static Value get_null(AttrType attr) {
    switch (attr) {
    case CHARS:
      return Value("", 0);
    case INTS:
      return Value(static_cast<int>(0));
    case DATES:
      return Value(static_cast<int64_t>(0));
    case FLOATS:
      return Value(static_cast<float>(EPSILON));
    case BOOLEANS:
      return Value(false);
    default:
      LOG_WARN("get null value on %d or %d", UNDEFINED, TEXTS);
      Value val;
      val.set_type(AttrType::NULLS);
      return val;
    }
  }

  std::string to_string() const;

  int compare(const Value &other) const;

  const char *data() const;
  int         length() const { return length_; }

  AttrType attr_type() const { return attr_type_; }

  bool operator==(const Value &other) const { return 0 == compare(other); }

  bool operator!=(const Value &other) const { return 0 != compare(other); }

  bool operator<(const Value &other) const { return 0 > compare(other); }

  bool operator<=(const Value &other) const { return 0 >= compare(other); }

  bool operator>(const Value &other) const { return 0 < compare(other); }

  bool operator>=(const Value &other) const { return 0 <= compare(other); }

  // consider null: null is euqal to null
  bool equal_to(const Value &other) const
  {
    if (is_null()) {
    return other.is_null();
    }
    if (other.is_null()) {
    return false;
    }
    return 0 == compare(other);
  }

  bool in_cells(const std::vector<Value> &cells) const
  {
    for (auto &cell : cells) {
      if (equal_to(cell)) {
        return true;
      }
    }
    return false;
  }

  // return false if is_null and null in cells
  bool not_in_cells(const std::vector<Value> &cells) const
  {
    for (auto &cell : cells) {
    if (equal_to(cell)) {
      return false;
    }
    }
    return true;
  }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  int         get_int() const;
  int64_t     get_date() const;
  float       get_float() const;
  const char *get_text() const;
  std::string get_string() const;
  bool        get_boolean() const;

private:
  AttrType attr_type_ = UNDEFINED;
  int      length_    = 0;

  union
  {
    int     int_value_;
    int64_t date_value_;
    float   float_value_;
    bool    bool_value_;
  } num_value_;
  std::string str_value_;
  char* text_value_ = nullptr; // 新增的用于存储text类型值的成员变量
};