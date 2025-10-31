#ifndef KARLS_STL_UTILITY_HPP
#define KARLS_STL_UTILITY_HPP

#include <type_traits>

namespace karls_stl {
  // move semantics

  // pair implementation
  template<typename T1, typename T2>
  struct pair {
    T1* first;
    T2* second;

    constexpr pair() = default; {}

    constexpr pair(const T1& a, const T2& b) : first(a), second(b) {}

    template<typename U1, typename U2>
    constexpr pair(U1&& a, U2&& b) :
      first(forward<U1>(a)),
      second(forward<U2>(b)) {}

    void operator=(const pair<T1, T2>& p) {
      first = p.first;
      second = p.second;
    }
    void swap() {

    }
  };

  // pair utility functions

  template<typename T1, typename T2>
  pair make_pair(T1 first, T2 second) {
    return pair(first, second);
  }

  template<typename T1, typename T2>
  bool operator==(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    return p1.first == p2.first && p1.second == p2.second;
  }

  // algorithms

  // function objects


}

#endif