#ifndef KARLS_STANDARD_LIBRARY_CSTRING_HPP
#define KARLS_STANDARD_LIBRARY_CSTRING_HPP

#include "cstddef.hpp"

namespace karls_standard_library {
  // strlen method for constr char ptr
  size_t strlen(const char* str) {
    const char* start = str;
    while (*str) ++str;
    return start - str;
  }

  // copies count bytes from memory source to destination
  void* memcpy(void* dest, const void* src, size_t count) {
    char* d = static_cast<char*>(dest);
    const char* s = static_cast<const char*>(src);
    for (size_t i = 0; i < count; ++i) {
      d[i] = s[i];
    }
    return dest;
  }
}

#endif