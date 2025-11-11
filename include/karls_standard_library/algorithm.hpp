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

  // find, find_if, find_if_not
  template<typename It, typename T>
  constexpr It find(It first, It last, const T& value)
  {
    for (; first != last; ++first)
    {
      if (*first == value) return first;
    }
    return last;
  }
  template<typename It, typename Pred>
  constexpr It find_if(It first, It last, Pred p)
  {
    for (; first != last; ++first)
    {
      if (p(*first)) return first;
    }
    return last;
  }
  template<typename It, typename Pred>
  constexpr It find_if_not(It first, It last, Pred p)
  {
    for (; first != last; ++first)
    {
      if (!p(*first)) return first;
    }
    return last;
  }
  
  // check if predicate returns true for all elements in range
  template<typename It, typename Pred>
  constexpr bool all_of(It first, It last, Pred p)
  {
    for (; first != last; ++first)
    {
      if (!p(*first)) return false;
    }
    return true;
  }
  // check if predicate returns true for any elements in range
  template<typename It, typename Pred>
  constexpr bool any_of(It first, It last, Pred p)
  {
    for (; first != last; ++first)
    {
      if (p(*first)) return true;
    }
    return false;
  }
  // check if predicate returns false for all elements in range
  template<typename It, typename Pred>
  constexpr bool none_of(It first, It last, Pred p)
  {
    for (; first != last; ++first)
    {
      if (p(*first)) return false;
    }
    return true;
  }

  // return number of iterators satisfy *it == value
  template<typename It, typename T>
  constexpr typename std::iterator_traits<It>::difference_type
  count(It first, It last, const T& value)
  {
    typename std::iterator_traits<It>::difference_type count = 0;
    for (; first != last; ++first)
    {
      if (*first == value) ++count;
    }
    return count;
  }
  template<typename It, typename Pred>
  constexpr typename std::iterator_traits<It>::difference_type
  count_if(It first, It last, Pred p)
  {
    typename std::iterator_traits<It>::difference_type count = 0;
    for (; first != last; ++first)
    {
      if (p(*first)) ++count;
    }
    return count;
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