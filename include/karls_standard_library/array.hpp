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
    using iterator = value_type*;
    using const_iterator = const value_type*;

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }

    iterator end() { return data_ + N; }
    const_iterator end() const { return data_ + N; }
    const_iteratoe cend() const { return data_ + N; }
  private:
    T data_[N];
  public:
    // default constructor
    array() = default;

    // brace initialization
    array(std::initializer_list<T> init) 
    {
      size_t i = 0;
      for (const T& value : init) {
        data_[i++] = value;
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

    reference data() noexcept { return data_; }
    const_reference data() const noexcept { return data_; }

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
      for (size_t i = 0; i < N; ++i)
      {
        std::swap(data_[i], other.data_[i]);
      }
    }
  };

  // non-member functions
  template<typename T, size_t N>
  void swap(array<T, N> lhs, array<T, N> rhs) noexcept(noexcept(lhs.swap(rhs)))
  {
    lhs.swap(rhs);
  }

  template<typename T, size_t N>
  bool operator==(const array<T, N> lhs, const array<T, N> rhs)
  {
    for (size_t i = 0; i < N; ++i)
    {
      if (lhs.data_[i] != rhs.data_[i])
      {
        return false;
      }
    }
    return true;
  }

}

#endif