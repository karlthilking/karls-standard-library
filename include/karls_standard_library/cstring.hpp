#ifndef KARLS_STANDARD_LIBRARY_CSTRING_HPP
#define KARLS_STANDARD_LIBRARY_CSTRING_HPP

#include "cstddef.hpp"
#include "algorithm.hpp"

namespace karls_standard_library {
  constexpr size_t strlen(const char* str)
  {
    const char* start = str;
    while (*str) ++str;
    return str - start;
  }
  char* strcpy(char* dest, const char* src)
  {
    for (size_t i = 0; i < strlen(src) + 1; ++i)
    {
      dest[i] = src[i];
    }
    return dest;
  }
  int strcmp(const char* lhs, const char* rhs)
  {
    while (*lhs && *rhs && *lhs == *rhs)
    {
      ++lhs;
      ++rhs;
    }
    return *lhs - *rhs;
  }

  void* memcpy(void* dest, const void* src, size_t count)
  {
    unsigned char* d = static_cast<unsigned char*>(dest);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (size_t i = 0; i < count; ++i) d[i] = s[i];
    return dest;
  }

  int memcmp(const void* lhs, const void* rhs, size_t count)
  {
    const unsigned char* l = static_cast<const unsigned char*>(lhs);
    const unsigned char* r = static_cast<const unsigned char*>(rhs);
    for (size_t i = 0; i < count; ++i)
    {
      if (l[i] != r[i]) return l[i] - r[i];
    }
    return 0;
  }
}

#endif