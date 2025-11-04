#ifndef KARLS_STANDARD_LIBRARY_ARRAY_HPP
#define KARLS_STANDARD_LIBRARY_ARRAY_HPP

#include "cstddef.hpp"
#include "initializer_list.hpp"
#include <stdexcept>

namespace karls_standard_library {
  template<typename T, size_t N>
  class Array {
  private:
    T data_[N];
  public:
    // default constructor
    Array() = default;

    // brace initialization
    Array(intializer_list<T> init) {
      size_t i = 0;
      for (const T& value : init) {
        data_[i++] = value;
      }
    }

    constexpr size_t size() const noexcept { return N; }
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    constexpr bool empty() const noexcept { return N == 0; }
    T& front() { return data_[0]; }
    const T& front() const { return data_[0]; }
    T& back() { return data_[N - 1]; }
    const T& back() const { return data_[N - 1]; }

    T& at(size_t index) {
      if (index >= N) {
        throw std::out_of_range("index out of bounds");
      }
      return data_[index];
    }
    const T& at(size_t index) const {
      if (index >= N) {
        throw std::out_of_range("index out of bounds");
      }
      return data_[index];
    }

    void fill(const T& value) {
      for (size_t i = 0; i < N; ++i) {
        data_[i] = value;
      }
    }

    void swap(Array& other) {
      std::swap(data_, other.data_);
    }
  };

}

#endif