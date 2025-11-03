#ifndef KARLS_STL_CSTDDEF_H
#define KARLS_STL_CSTDDEF_H

namespace karls_stl {
  // size_t alias
  using size_t = decltype(sizeof(0));

  // ptr diff alias
  using ptrdiff_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

  // null ptr alias
  using nullptr_t = decltype(nullptr);

  // npos constant
  constexpr size_t npos = static_cast<size_t>(-1);

  // represents the strictest alignment needed for common types
  union max_align_t {
    long double ld;
    long long ll;
    void* ptr;
  };

  // byte type
  enum class byte : unsigned char {};
}