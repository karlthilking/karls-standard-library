#ifndef KARLS_STANDARD_LIBRARY_UTILITY_HPP
#define KARLS_STANDARD_LIBRARY_UTILITY_HPP

#include "type_traits.hpp"

namespace karls_standard_library {
  // move semantics
  template<typename T>
  constexpr remove_reference<T>&& move(T&& t) noexcept {
    return static_cast<remove_reference_t<T>::type&&>(t);
  }

  // forward
  template<typename T>
  constexpr T&& forward(remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
  }

  template<typename T>
  constexpr T&& forward(remove_reference_t<T>&& t) noexcept {
    static_assert(!is_lvalue_reference_v<T>);
    return static_cast<T&&>(t);
  }

  // swap function
  template<typename T>
  void swap(T& a, T& b) noexcept(
    is_nothrow_move_constructible_v<T> &&
    is_nothrow_move_assignable_v<T>
  )
  {
    T temp = move(a);
    a = move(b);
    b = move(temp);
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
    template<typename U1, typename U2>
    constexpr pair(const pair<U1, U2>&& other) :
      first(move(other.first)),
      second(moe(other.second)) {}

    void operator=(const pair<T1, T2>& p) {
      first = p.first;
      second = p.second;
    }

  };

  // pair utility functions
  pair make_pair(const T1& first, const T2& second) {
    return pair(first, second);
  }

  bool operator==(const pair<T1, T2>& p1, const pair<T1, T2>& p2) {
    return p1.first == p2.first && p1.second == p2.second;
  }

  // exchange function
  template<typename T, typename U = T>
  T exchange(T& obj, U&& new_value) 
  noexcept(
    is_nothrow_move_constructible_t<T>::value &&
    is_nothrow_move_assignable_t<T&, U>::value
  )
  {
    T old_value = move(obj);
    obj = forward<U>(new_value);
    return old_value;
  }

  template<typename T>
  typename add_rvalue_reference<T>::type declval() noexcept;


  // algorithms

  // function objects


}

#endif