//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// hash_util.h
//
// Identification: src/include/common/util/hash_util.h
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <algorithm>
#include <bits/stdint-intn.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include "unordered_map"

#include "common/log/log.h"
#include "sql/parser/value.h"

namespace MyHash {

using hash_t = std::size_t;

class HashUtil {
 private:
  static const hash_t PRIME_FACTOR = 10000019;

 public:
  static inline auto HashBytes(const char *bytes, size_t length) -> hash_t {
    // https://github.com/greenplum-db/gpos/blob/b53c1acd6285de94044ff91fbee91589543feba1/libgpos/src/utils.cpp#L126
    hash_t hash = length;
    for (size_t i = 0; i < length; ++i) {
      hash = ((hash << 5) ^ (hash >> 27)) ^ bytes[i];
    }
    return hash;
  }

  static inline auto CombineHashes(hash_t l, hash_t r) -> hash_t {
    hash_t both[2] = {};
    both[0] = l;
    both[1] = r;
    return HashBytes(reinterpret_cast<char *>(both), sizeof(hash_t) * 2);
  }

  static inline auto SumHashes(hash_t l, hash_t r) -> hash_t {
    return (l % PRIME_FACTOR + r % PRIME_FACTOR) % PRIME_FACTOR;
  }

  template <typename T>
  static inline auto Hash(const T *ptr) -> hash_t {
    return HashBytes(reinterpret_cast<const char *>(ptr), sizeof(T));
  }

  template <typename T>
  static inline auto HashPtr(const T *ptr) -> hash_t {
    return HashBytes(reinterpret_cast<const char *>(&ptr), sizeof(void *));
  }
  static inline auto HashChar(const char* ptr, size_t len) -> hash_t {
    return HashBytes(ptr, len);
  }

  /** @return the hash of the value */
  static inline auto HashValue(const Value *val) -> hash_t {
    switch (val->attr_type()) {
      case AttrType::DATES: {
        auto raw = static_cast<int64_t>(val->get_date());
        return Hash<int64_t>(&raw);
      }
      case AttrType::INTS: {
        auto raw = static_cast<int32_t>(val->get_int());
        return Hash<int32_t>(&raw);
      }
      case AttrType::FLOATS: {
        auto raw = static_cast<int32_t>(val->get_float());
        return Hash<int32_t>(&raw);
      }
      case AttrType::BOOLEANS: {
        auto raw = val->get_boolean();
        return Hash<bool>(&raw);
      }
      case AttrType::CHARS: {
        auto raw = val->get_string();
        // todo (recheck)
        std::hash<std::string> hasher;
        return static_cast<hash_t>(hasher(raw));
      }
      case AttrType::NULLS: {
        LOG_WARN("hash on null");
        auto raw = val->get_string();
        std::hash<std::string> hasher;
        return static_cast<hash_t>(hasher(raw));
      }break;
      default: {
        LOG_PANIC("Unsupported type%d.", val->attr_type());
        return 0;
      }
    }
  }
};

} 
