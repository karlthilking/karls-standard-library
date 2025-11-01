#ifndef KARLS_STL_UTILITY_HPP
#define KARLS_STL_UTILITY_HPP

#include <type_traits>

namespace karls_stl {
  // move semantics
  template<typename T>
  constexpr std::remove_reference_t<T>&& move(T&& t) noexcept {
    return std::static_cast<T&&>(t);
  }

  constexpr T&& forward(std::remove_reference_t<T>& t) noexcept {

  }

  constexpr T&& forward(std::remove_reference_t<T>&& t) noexcept {

  }


  // pair implementation
  template<typename T1, typename T2>
  struct pair {
    T1* first;
    T2* second;

    // default constructor
    constexpr pair() = default;

    // value constructor
    constexpr pair(const T1& a, const T2& b) : first(a), second(b) {}

    // perfect forwarding constructor
    template<typename U1, typename U2>
    constexpr pair(U1&& a, U2&& b) :
      first(forward<U1>(a)),
      second(forward<U2>(b)) {}

    // copy constructor
    pair(pair& other) = default;

    // move constructor
    constexpr pair(pair<T1, T2>&& other) noexcept(
      std::is_nothrow_move_constructible_v<T1> &&
      std::is_nothrow_move_constructible_v<T2> &&
    ) : first(move(other.first)), second(move(other.second)) {}

    // converting copy constructor
    template<typename U1, typename U2>
    constexpr pair(const pair<U1, U2>& other) :
      first(other.first),
      second(other.second) {}

    // converting move constructor
    void operator=(const pair<T1, T2>& p) {
      first = p.first;
      second = p.second;
    }

    constexpr void swap(pair& other) noexcept {

    }

  };

  // pair utility functions
  pair make_pair(const T1& first, const T2& second) {
    return pair(first, second);
  }

  bool operator==(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    return p1.first == p2.first && p1.second == p2.second;
  }

  template<typename T>
  constexpr void swap(T& x, T& y) {
    auto temp = karls_stl::move(x);
    x = karls_stl::move(y);
    y = karls_stl::move(temp);
  }


  // algorithms

  // function objects


}

#endif