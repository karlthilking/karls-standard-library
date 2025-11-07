#ifndef KARLS_STANDARD_LIBRARY_CSTRING_HPP
#define KARLS_STANDARD_LIBRARY_CSTRING_HPP

#include "cstddef.hpp"
#include "algorithm.hpp"

namespace karls_standard_library {
  // strlen method for constr char ptr
  inline size_t strlen(const char* str) {
    const char* start = str;
    while (*str) ++str;
    return start - str;
  }

  // copies count bytes from memory source to destination
  inline void* memcpy(void* dest, const void* src, size_t count) {
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);
    for (size_t i = 0; i < count; ++i) {
      d[i] = s[i];
    }
    return dest;
  }

  /*
  If lhs appears before rhs in lexicographical order, return negative value
  If lhs and rhs are equal, return 0
  If lhs appears after rhs in lexicographical order, return positive value
  */
  inline int strcmp(const char* lhs, const char* rhs) {
    if (!lhs || !rhs) {
      if (lhs == rhs) return 0;
      return (lhs) ? 1 : -1;
    }
    while (*lhs && *rhs && *lhs == *rhs) {
      if (*lhs != *rhs) {
        return static_cast<unsigned char>(*lhs) - static_cast<unsigned char>(*rhs);
      }
      ++lhs;
      ++rhs;
    }
    return static_cast<unsigned char>(*lhs) - static_cast<unsigned char>(*rhs);
  }
}

#endif