#ifndef KARLS_STANDARD_LIBRARY_STRING_HPP 
#define KARLS_STANDARD_LIBRARY_STRING_HPP

#include "cstddef.hpp"
#include "utility.hpp"
#include <string.h>
#include <stdexcept>
#include <iostream>

namespace karls_standard_library {
  class String { 
  private:
    char* data_;
    size_t size_;
    size_t capacity_;

    void grow() {
      size_t new_cap = (capacity_ == 0) ? 1 : 2 * capacity_;
      char* new_data = new char[capacity_];
      for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = new_cap;
    }
  public:
    // default constructor
    String() : data_(nullptr), size_(0), capacity_(0) {}
    
    // desctructor
    ~String() { delete[] data_; }

    // c-string constructor
    String(const char* str) : 
      size_(strlen(str)),
      capacity_(strlen(str) + 1)
      {
        data_ = new char[strlen(str) + 1];
        strcpy(data_, str);
      }
    
    // copy constructor
    String(const String& other) :
      size_(other.size_),
      capacity_(other.capacity_)
      {
        if (other.data_) {
          data_ = new char[other.capacity_];
          memcpy(data_, other.data_, other.size_ + 1);
        }
        else {
          data_ = nullptr;
        }
      }

    // copy assignment operator
    String& operator=(const String& other) {
      if (this != &other) {
        String temp = String(other);
        swap(temp);
      }
    }

    // move constructor
    String(String&& other) :
      data_(exchange(other.data_, nullptr)),
      size_(exchange(other.size_, 0)),
      capacity_(exchange(other.capacity_, 0)) {}

    // move assignment operator
    String& operator=(String&& other) {
      if (this != &other) {
        data_ = exchange(other.data_, nullptr);
        size_ = exchange(other.size_, 0);
        capacity_ = exchange(other.capacity_, 0);
      }
      return *this;
    }

    bool empty() const noexcept { return size_; }
    char& operator[](size_t index) { return data_[index]; }
    const char& operator[](size_t index) const { return data_[index]; }

    char& at(size_t index) {
      if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
      }
      return data_[index];
    }
    const char& at(size_t index) const {
      if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
      }
      return data_[index];
    }

    void push_back(const char& c) noexcept {
      if (size_ == capacity_) grow();
      data_[size_] = c;
      ++size_;
    }

    void pop_back() noexcept {
      if (!empty()) --size_;
    }

    char& front() const {
      if (empty()) {
        throw std::logic_error("string is empty");
      }
      return data_[0];
    }

    char& back() const {
      if (empty()) {
        throw std::logic_error("string is empty");
      }
      return data_[size_ - 1];
    }

    String& operator+=(const char& c) noexcept {
      push_back(c);
      return *this;
    }

    String& operator+=(const String& s) noexcept {
      for(size_t i = 0; i < s.size_; ++i) {
        push_back(s[i]);
      }
      return *this;
    }

    void swap(String& other) noexcept {
      karls_standard_library::swap(data_, other.data_);
      karls_standard_library::swap(size_, other.size_);
      karls_standard_library::swap(capacity_, other.capacity_);
    }

    explicit operator bool() const noexcept { return size_ != 0; }
    size_t length() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
      os << (s.data_ ? s.data_ : "");
      return os;
    }
  };
}

#endif