#ifndef KARLS_STANDARD_LIBRARY_ALGORITHM_HPP
#define KARLS_STANDARD_LIBRARY_ALGORITHM_HPP

#include <compare>
#include <cstring>

namespace karls_standard_library {
  template<typename T>
  const T& min(const T& a, const T& b) 
  {
    return (a < b) ? a : b;
  }
  template<typename T>
  const T& max(const T& a, const T& b) 
  {
    return (a > b) ? a : b;
  }

  template<typename It1, typename It2>
  constexpr bool equal(It1 f1, It1 l1, It2 f2)
  {
    for (; f1 != l1; ++f1, ++f2)
    {
      if (*f1 != *f2) return false;
    }
    return true;
  }

  // three way comparison
  template<typename It1, typename It2>
  constexpr auto lexicographical_compare_three_way(It1 f1, It1 l1, It2 f2, It2 l2)
  {
    for (; f1 != l1 && f2 != l2; ++f1, ++f2)
    {
      if (auto cmp = *f1 <=> *f2; cmp != 0) return cmp;
    }
    return (f1 == l1 && f2 == l2) ? std::strong_ordering::equal :
           (f1 == l1) ? std::strong_ordering::less :
           std::strong_ordering::greater;
  }
}

#endif