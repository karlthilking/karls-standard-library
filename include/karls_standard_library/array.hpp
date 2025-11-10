#ifndef KARLS_STANDARD_LIBRARY_ARRAY_HPP
#define KARLS_STANDARD_LIBRARY_ARRAY_HPP

#include "cstddef.hpp"
#include <stdexcept>
#include <utility>
#include <type_traits>

namespace karls_standard_library {
  template<typename T, size_t N>
  class array {
  public:
    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = value_type*;
    using const_iterator = const value_type*;

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }

    iterator end() { return data_ + N; }
    const_iterator end() const { return data_ + N; }
    const_iterator cend() const { return data_ + N; }
  private:
    T data_[N];
  public:
    // default constructor
    array() = default;

    // brace initialization
    array(std::initializer_list<T> init) 
    {
      size_t i = 0;
      for (const T& value : init) 
      {
        if (i < N) data_[i++] = value;
      }
      for(; i < N; ++i)
      {
        data_[i] = T{};
      }
    }

    // fill constructor
    explicit array(const T& value)
    {
      for (size_t i = 0; i < N; ++i)
      {
        data_[i] = value;
      }
    }

    constexpr size_type size() const noexcept { return N; }
    reference operator[](size_t index) noexcept { return data_[index]; }
    const_reference operator[](size_t index) const noexcept { return data_[index]; }
    constexpr bool empty() const noexcept { return N == 0; }
    reference front() noexcept { return data_[0]; }
    const_reference front() const noexcept { return data_[0]; }
    reference back() noexcept{ return data_[N - 1]; }
    const_reference back() const noexcept { return data_[N - 1]; }

    pointer data() noexcept { return data_; }
    const_pointer data() const noexcept { return data_; }

    reference at(size_t index) 
    {
      if (index >= N) {
        throw std::out_of_range("index out of bounds");
      }
      return data_[index];
    }
    const_reference at(size_t index) const 
    {
      if (index >= N) {
        throw std::out_of_range("index out of bounds");
      }
      return data_[index];
    }

    void fill(const T& value) noexcept 
    {
      for (size_t i = 0; i < N; ++i) {
        data_[i] = value;
      }
    }

    void swap(array& other) noexcept(std::is_nothrow_swappable_v<T>)
    {
      for(size_t i = 0; i < N; ++i)
      {
        swap(data_[i], other.data_[i]);
      }
    }

    constexpr bool operator==(const array& other)
    {
      return std::equal(data_, data_ + N, other.data_);
    }
    constexpr auto operator<=>(const array& other)
    {
      return std::lexicographical_compare_three_way(data_, data_ + N, other.data_, other.data_ + M);
    }
  };

  // non-member swap
  template<typename T, size_t N>
  void swap(array<T, N>& lhs, array<T, N>& rhs) noexcept(noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }

  // convert cstyle arrays to array
  template<typename T, size_t N>
  constexpr array<std::remove_cv_t<T>, N> to_array(T(&a)[N])
  {
    array<std::remove_cv_t<T>, N> temp;
    for (size_t i = 0; i < N; ++i)
    {
      temp[i] = a[i];
    }
    return temp;
  }

  // rvalue specialized 
  template<typename T, size_t N>
  constexpr array<std::remove_cv_t<T>, N> to_array(T(&&a)[N])
  {
    array<std::remove_cv_t<T>, N> temp;
    for (size_t i = 0; i < N; ++i)
    {
      temp[i] = move(a[i]);
    }
    return temp;
  }

}

#endif