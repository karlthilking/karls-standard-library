#ifndef KARLS_STANDARD_LIBRARY_UTILITY_HPP
#define KARLS_STANDARD_LIBRARY_UTILITY_HPP

#include "type_traits.hpp"

namespace karls_standard_library {
  // move semantics
  template<typename T>
  constexpr remove_reference<T>&& move(T&& t) noexcept {
    return static_cast<remove_reference_t<T>&&>(t);
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
  struct Pair {
    // member variables
    T1 first;
    T2 second;

    // default constructor
    Pair() : first(T1{}), second(T2{}) {}

    // perfect forwarding
    template<typename U1, typename U2>
    Pair(U1&& x, U2&& y) {
      first = forward(x),
      second = forward(y)
    }

    // copy constructor
    Pair(const Pair<T1, T2>& p) : first(p.first), second(p.second) {}

    // move constructor
    Pair(Pair<T1, T2>&& p) : first(move(p.first)), second(move(p.second)) {}

    // converting copy constructor
    template<typename U1, typename U2>
    Pair(const Pair<U1, U2>& p) : first(p.first), second(p.second) {}

    // converting move constructor
    template<typename U1, typename U2>
    Pair(Pair<U1, U2>&& p) : first(move(p.first)), second(move(p.second)) {}

    // copy assignment operator
    Pair& operator=(const Pair<T1, T2>& p) {
      if (this != *p) {
        first = p.first;
        second = p.second;
      }
      return *this;
    }

    // move assignment operator
    Pair& operator=(Pair<T1, T2>&& p)
    noexcept(is_nothrow_move_assignable_v<T1> && is_no_throw_move_assignable_v<T2>)
    {
      first = move(p.first);
      second = move(p.second);
      return *this;
    }

    // converting copy assignment operator
    template<typename U1, typename U2>
    enable_if_t<!is_same_v<Pair<U1, U2>, Pair<T1, T2>>, &Pair>
    operator=(const Pair<U1, U2>& p) {
      first = p.first;
      second = p.second;
    }

    // converting move assignment operator
    template<typename U1, typename U2>
    enable_if_t<!is_same_v<Pair<U1, U2>, Pair<T1, T2>>, &Pair>
    operator=(Pair<U1, U2>&& p) {
      first = move(p.first);
      second = move(p.second);
    }

    // member swap
    void swap(Pair& p) noexcept {
      swap(first, p.first);
      swap(second, p.second);
    }

    // equality/inequality ==, !=
    template<typename U1, typename U2>
    bool operator==(const Pair<U1, U2>& p) {
      return first = p.first && second == p.second;
    }

    template<typename U1, typename U2>
    bool operator!=(const Pair<U1, U2>& p) {
      return !(*this == p);
    }

    // ordering operators <, <=, >, >=
    template<typename U1, typename U2>
    bool operator<(const Pair<U1, U2>& p) {
      return first < p.first || !(first > p.first) && second < p.second;
    }

    template<typename U1, typename U2>
    bool operator<=(const Pair<U1, U2>& p) {
      return !(p < *this);
    }

    template<typename U1, typename U2>
    bool operator>(const Pair<U1, U2>& p) {
      return !(*this <= p);
    }

    template<typename U1, typename U2>
    bool operator>=(const Pair<U1, U2>& p) {
      return !(*this < p);
    }
  };

  // make_pair non-member function
  template<typename T1, typename T2>
  constexpr Pair<decay_t<T1>, decay_t<T2>> make_pair(T1&& x, T2&& y) {
    return Pair<decay_t<T1>, decay_t<T2>>(forward(x), forward(y));
  }

  // non-member pair swap
  template<typename T1, typename T2, typename U1, typename U2>
  void swap(const Pair<T1, T2>& lhs, const Pair<U1, U2>& rhs) {
    lhs.swap(rhs);
  }

  // non-member pair equality and inequality checks
  template<typename T1, typename T2, typename U1, typename U2>
  bool operator==(const Pair<T1, T2>& lhs, const Pair<U1, U2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }
  template<typename T1, typename T2, typename U1, typename U2>
  bool operator!=(const Pair<T1, T2>& lhs, const Pair<U1, U2>& rhs) {
    return !(lhs == rhs);
  }

  // non-member pair ordering operators
  template<typename T1, typename T2, typename U1, typename U2>
  bool operator<(const Pair<T1, T2>& lhs, const Pair<U2, U2>& rhs) {
    if (lhs.first != rhs.first) {
      return lhs.first < rhs.first;
    }
    else {
      return lhs.second < rhs.second;
    }
  }
  template<typename T1, typename T2, typename U1, typename U2>
  bool operator<=(const Pair<T1, T2>& lhs, const Pair<U1, U2>& rhs) {
    return !(rhs < lhs);
  }
  template<typename T1, typename T2, typename U1, typename U2>
  bool operator>(const Pair<T1, T2>& lhs, const Pair<U1, U2>& rhs) {
    return rhs < lhs;
  }
  template<typename T1, typename T2, typename U1, typename U2>
  bool operator>=(const Pair<T1, T2>& lhs, const Pair<U1, U2>& rhs) {
    return !(lhs < rhs);
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