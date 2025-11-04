#ifndef KARLS_STANDARD_LIBRARY_UNORDERED_MAP_HPP
#define KARLS_STANDARD_LIBRARY_UNORDERED_MAP_HPP

#include "utility.hpp"

namespace karls_standard_library {
  template<typename K, typename V>
  class Unordered_Map {
  private:

  public:
    Hash hash_function() const {}
    bool empty() const noexcept {}
    size_t size() const noexcept {}
    void clear() noexcept {}
    pair<iterator, bool> insert(const pair<Key, Value>& kv_pair) {}
    pair<iterator, bool> insert(pair<Key, Value>&& kv_pair) {}
    void insert(initializer_list<pair<Key, Value>> list) {}
  };
}

#endif