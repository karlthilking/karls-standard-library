#ifndef KARLS_STANDARD_LIBRARY_VECTOR_HPP
#define KARLS_STANDARD_LIBRARY_VECTOR_HPP

#include <stdexcept>
#include "utility.hpp"

namespace karls_standard_library {
  // vector implementation
  template<typename T>
  class Vector {
  private:
    T* data_;
    size_t size_;
    size_t capacity_;

    // helper function to increase capacity
    void grow() noexcept {
      size_t new_cap = (capacity_ == 0) ? 1 : 2 * capacity_;
      T* new_data = new T[new_cap];
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = new_cap;
    }
  public:
    // default constructor
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // initial size and capacity, optional initial value
    explicit Vector(size_t count, const T& value = T{}) : size_(count), capacity_(count)
    {
      if (size_ == 0) {
        data_ = nullptr;
      }
      else {
        data_ = new T[count];
        for (size_t i = 0; i < count; ++i) {
          data_[i] = value;
        }
      }
    }

    // list initialization
    Vector(initializer_list<T> init) : size_(init.size()), capacity_(init.size())
    {
      if (capacity_ == 0) {
        data_ = nullptr;
      }
      else {
        data_ = new T[capacity_];
        size_t i = 0;
        for (const T& item : init) {
          data_[i++] = item;
        }
      }
    }

    // copy constructor
    Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_)
    {
      if (capacity_ == 0) {
        data_ = nullptr;
      }
      else {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
          data_[i] = other.data_[i];
        }
      }
    }

    // copy assignment operator
    Vector& operator=(const Vector& other) {
      if (this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        delete[] data_;
        if (capacity_ == 0) {
          data_ = nullptr;
        }
        else {
          data_ = new T[capacity_];
          for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
          }
        }
      }
      return *this;
    }

    // move constructor
    Vector(Vector&& other) : 
      data_(exchange(other.data_, nullptr)),
      size_(exchange(other.size_, 0)),
      capacity_(exchange(other.capacity_, 0)) {}

    // move assignment operator
    Vector& operator=(Vector&& other) {
      if (this != &other) {
        delete[] data_;
        data_ = exchange(other.data_, nullptr);
        size_ = exchange(other.size_, 0);
        capacity_ = exchange(other.capacity_, 0);
      }
      return *this;
    }

    // true if vector is empty, false otherwise
    bool empty() const noexcept { return size_ == 0; }

    // return size of the vector
    size_t size() const noexcept { return size_; }

    // return capacity of the vector
    size_t capacity() const noexcept { return capacity_; }

    // direct access into vector
    T& operator[](size_t index) noexcept { return data_[index]; }
    const T& operator[](size_t index) const noexcept { return data_[index]; }

    // direct access to first element
    T& front() noexcept { return data_[0]; }
    const T& front() const noexcept { return data_[0]; }

    // direct access to last element
    T& back() noexcept { return data_[size_ - 1]; }
    const T& back() const noexcept { return data_[size_ - 1]; }

    // index into the vector with bounds checking
    T& at(size_t index) {
      if (index >= size) throw std::out_of_range("Index out of bounds"); 
      return data_[index];
    }
    const T& at(size_t index) const {
      if (index >= size) throw std::out_of_range("Index out of bounds");
    }

    // remove unused capacity
    void shrink_to_fit() noexcept {
      while (capacity_ > size_) {
        --size_;
      }
    }

    // remove all elements and reduce size to 0; capacity remains unchanged
    void clear() noexcept {
      delete[] data_;
      data_ = nullptr;
      size_ = 0;
    }

    // add element to end of vector
    void push_back(const T& value) noexcept {
      if (size_ == capacity_) {
        grow();
      }
      data_[size_] = value;
      ++size_;
    }

    // remove element from end of vector
    void pop_back() noexcept {
      if (size_ > 0) {
        --size;
      }
    }

    // swap with other vector
    void swap(Vector& other) noexcept {
      swap(data_, other.data_);
      swap(size_, other.size_);
      swap(capacity_, other.capacity_);
    }
  };

  template<typename T, typename U>
  bool operator==(const Vector<T>& lhs, const Vector<U>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    else {
      for (size_t i = 0; i < lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
          return false;
        }
      }
    }
    return true;
  }
}

#endif