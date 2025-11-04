#ifndef KARLS_STANDARD_LIBRARY_SET_HPP
#define KARLS_STANDARD_LIBRARY_SET_HPP

#include "functional.hpp"

namespace karls_standard_library {
  template<typename Key, typename Compare = less<Key>>
  class Set {
  private:

  public:
    Set() : {}
    ~Set() {}
    Set& operator=(const Set& other) {}
    bool empty() const noexcept {}
    size_t size() const noexcept {}
    void clear() {}
    pair<iterator, bool> insert(const T& value) {}
    pair<iterator, bool> insert(T&& value) {}
    void insert(initializer_list<T> list) {}
    template<typename... Args>
    pair<iterator, bool> emplace(Args&&... args) {}
    
  };
}

#endif