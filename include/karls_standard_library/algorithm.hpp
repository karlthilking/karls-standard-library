#ifndef KARLS_STANDARD_LIBRARY_ALGORITHM_HPP
#define KARLS_STANDARD_LIBRARY_ALGORITHM_HPP

namespace karls_standard_library {
  template<typename T>
  const T& min(const T& a, const T& b) {
    return (a < b) ? a : b;
  }
  template<typename T>
  const T& max(const T& a, const T& b) {
    return (a > b) ? a : b;
  }
}

#endif