#ifndef KARLS_STANDARD_LIBRARY_CSTDDEF_HPP
#define KARLS_STANDARD_LIBRARY_CSTDDEF_HPP

namespace karls_standard_library {
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

#endif 