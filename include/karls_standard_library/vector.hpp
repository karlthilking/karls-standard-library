#ifndef KARLS_STANDARD_LIBRARY_VECTOR_HPP
#define KARLS_STANDARD_LIBRARY_VECTOR_HPP

#include <stdexcept>
#include "utility.hpp"

namespace karls_standard_library {
  template<typename vector>
  class vector_iterator {
  public:
    using value_type = typename vector::value_type;
    using pointer = value_type*;
    using reference = value_type&;
  private:
    pointer ptr_;
  public:
    vector_iterator(pointer ptr) : ptr_(ptr) {}

    vector_iterator& operator++() {
      ptr_++;
      return *this;
    }
    vector_iterator operator++(int) {
      vector_iterator temp = *this;
      ++(*this);
      return temp;
    }

    vector_iterator& operator--() {
      ptr_--;
      return *this;
    }
    vector_iterator operator--(int) {
      vector_iterator temp = *this;
      --(*this);
      return temp;
    }

    reference operator[](size_t index) { return *(ptr_ + index); }
    pointer operator->() { return ptr_; }
    reference operator&() { return *ptr_; } 
    bool operator==(const vector_iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const vector_iterator& other) const { return !(*this == other); }
  };


  // vector implementation
  template<typename T>
  class vector {
  public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const value_type&;
    using iterator = vector_iterator<vector<T>>;
    using const_iterator = const vector_iterator<vector<T>>;

    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }

    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() const { return data_ + size_; }
  private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void dealloc() {
      if (data_) {
        operator delete[](data_);
        data_ = nullptr;
      }
      capacity_ = 0;
    }
  public:
    // default constructor
    vector() : data_(nullptr), size_(0), capacity_(0) {}

    // initial size and capacity, optional initial value
    explicit vector(size_t count, const T& value = T{}) :
      data_(nullptr), size_(count), capacity_(count)
    {
      if (size_ > 0) {
        data_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
        for (size_t i = 0; i < size_; ++i) {
          data_[i] = value;
        }
      }
    }

    // list initialization
    vector(std::initializer_list<T> init) :
      data_(nullptr), size_(init.size()), capacity_(init.size())
    {
      if (size_ > 0) {
        data_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
        std::uninitialized_copy(init.begin(), init.end(), data_);
      }
    }

    // copy constructor
    vector(const vector& other) : 
      data_(nullptr), size_(other.size_), capacity_(other.capacity_)
    {
      if (size_ > 0) {
        data_ = static_cast<T*>(operator new[](capacity_ * sizeof(T)));
        for (size_t i = 0; i < other.size_; ++i) {
          data_[i] = other.data_[i];
        }
      }
    }

    // copy assignment operator
    vector& operator=(const vector& other) {
      if (this != &other) {
        vector temp(other);
        swap(temp);
      }
      return *this;
    }

    // move constructor
    vector(vector&& other) : 
      data_(exchange(other.data_, nullptr)),
      size_(exchange(other.size_, 0)),
      capacity_(exchange(other.capacity_, 0)) {}

    // move assignment operator
    vector& operator=(vector&& other) {
      if (this != &other) {
        clear();
        operator delete[](data_);
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
      if (index >= size_) throw std::out_of_range("Index out of bounds"); 
      return data_[index];
    }
    const T& at(size_t index) const {
      if (index >= size_) throw std::out_of_range("Index out of bounds");
      return data_[index];
    }

    // remove unused capacity
    void shrink_to_fit() noexcept {
      if (size_ == capacity_) 
      {
        return;
      }
      else if (size_ == 0)
      {
        dealloc();
        return;
      }
      T* new_data = static_cast<T*>(operator new[](size_ * sizeof(T)));
      for (size_t i = 0; i < size_; ++i) {
        if constexpr (std::is_nothrow_move_constructible_v<T>) {
          new(&new_data[i]) T(move(data_[i]));
        }
        else {
          new(&new_data[i]) T(data_[i]);
        }
        data_[i].~T();
      }
      operator delete[](data_);
      data_ = new_data;
      capacity_ = size_;
    }

    // remove all elements and reduce size to 0; capacity remains unchanged
    void clear() noexcept {
      for (size_t i = 0; i < size_; ++i) {
        data_[i].~T();
      }
      size_ = 0;
    }

    // add element to end of vector
    void push_back(const T& value) noexcept {
      if (size_ == capacity_) {
        size_t new_cap = (capacity_ == 0) ? 1 : 2 * capacity_;
        reserve(new_cap);
      }
      new(&data_[size_]) T(value);
      ++size_;
    }

    template<typename... Args>
    reference emplace_back(Args... args) {
      if (size_ == capacity_) {
        size_t new_cap = (capacity_ == 0) ? 1 : 2 * capacity_;
        reserve(new_cap);
      }
      new(&data_[size_]) T(forward<Args>(args)...);
      return data_[size_++];
    }
    
    // remove element from end of vector
    void pop_back() noexcept {
      if (size_ > 0) {
        --size;
        data_[size_].~T();
      }
    }

    void resize(size_t count) { resize(count, T{}); }
    void resize(size_t count, const T& value) {
      if (count == 0) return;
      else if (count < size_) {
        for (size_t i = count; i < size_; ++i) {
          data_[i].~T();
        }
        size_ = count;
      }
      else {
        reserve(count);
        for (size_t i = size_; i < count; ++i) {
          new(&data_[i]) T(value);
        }
        size_ = count;
      }
    }

    void reserve(size_t new_cap) {
      if (capacity_ >= new_cap) return;
      T* new_data = static_cast<T*>(operator new[](new_cap * sizeof(T)));
      for (size_t i = 0; i < size_; ++i) {
        if constexpr (std::is_nothrow_move_constructible_v<T>) {
          new(&new_data[i]) T(move(data_[i]));
        }
        else {
          new(&new_data[i]) T(data_[i]);
        }
        data_[i].~T();
      }
      operator delete[](data_);
      data_ = new_data;
      capacity_ = new_cap;
    }

    // swap with other vector
    void swap(vector& other) noexcept {
      swap(data_, other.data_);
      swap(size_, other.size_);
      swap(capacity_, other.capacity_);
    }
  };

  template<typename T, typename U>
  bool operator==(const vector<T>& lhs, const vector<U>& rhs) {
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