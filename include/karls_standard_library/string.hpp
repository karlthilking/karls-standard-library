#ifndef KARLS_STANDARD_LIBRARY_STRING_HPP 
#define KARLS_STANDARD_LIBRARY_STRING_HPP

#include "cstddef.hpp"
#include "cstring.hpp"
#include "utility.hpp"
#include "memory.hpp"
#include "algorithm.hpp"
#include <stdexcept>
#include <iostream>

namespace karls_standard_library {
  // custom iterator for string class
  template<typename string>
  class string_iterator {
  public:
    using value_type = char;
    using pointer = value_type*;
    using reference = value_type&;
  private:
    pointer ptr_;
  public:
    string_iterator(pointer ptr) : ptr_(ptr) {}

    // increment operators
    string_iterator& operator++() 
    {
      ptr_++;
      return *this;
    }
    string_iterator operator++(int)
    {
      string_iterator temp = *this;
      ++(*this);
      return temp;
    }

    // decrement operators
    string_iterator& operator--() 
    {
      ptr_--;
      return *this;
    }
    string_iterator operator--(int) 
    {
      string_iterator temp = *this;
      --(*this);
      return temp;
    }

    reference operator[](size_t index) { return *(ptr_ + index); }
    pointer operator->() { return ptr_; }
    reference operator*() { return *ptr_; }
    bool operator==(const string_iterator& other) const { return ptr_ == other.ptr_; }
    bool operator!=(const string_iterator& other) const { return !(*this == other); }
  };

  class string { 
  public:
    using value_type = char;
    using size_type = size_t;
    using reference = char&;
    using const_reference = const value_type&;
    using iterator = string_iterator<string>;
    using const_iterator = const string_iterator<string>;
  private:
    char* data_;
    size_t size_;
    size_t capacity_;

    // delete char ptr and set capacity to 0
    void dealloc() 
    {
      if (data_) 
      {
        delete[] data_;
        data_ = nullptr;
      }
      capacity_ = 0;
    }
    
    // templated helper swap function
    template<typename T>
    void swap(T& a, T& b)
    {
      T temp = move(a);
      a = move(b);
      b = move(temp);
    }
  public:
    // default constructor
    string() : data_(nullptr), size_(0), capacity_(0) {}
    
    // destructor
    ~string() 
    {
      clear();
      dealloc();
    }

    // cstring constructor
    string(const char* str) :
      data_(nullptr), size_(strlen(str)), capacity_(strlen(str))
      {
        if (str != nullptr && size_ > 0) 
        {
          data_ = new char[capacity_];
          memcpy(data_, str, size_);
        }
      }

    // cstring fill constructor
    string(const char* str, size_t count) :
      data_(nullptr), size_(count), capacity_(count)
      {
        if (str != nullptr && count > 0) 
        {
          data_ = new char[capacity_];
          memcpy(data_, str, count);
        }
      }
    
    // fill constructor
    string(size_t count, char c = char{}) :
      data_(nullptr), size_(count), capacity_(count)
      {
        if (size_ > 0) 
        {
          data_ = new char[capacity_];
          for (size_t i = 0; i < size_; ++i) 
          {
            data_[i] = c;
          }
        }
      }
    
    // initializer list constructor
    string(std::initializer_list<char> init) : 
      data_(nullptr), size_(init.size()), capacity_(init.size())
      {
        if (size_ > 0) 
        {
          data_ = new char[capacity_];
          std::uninitialized_copy(init.begin(), init.end(), data_);
        }
      }

    // copy constructor
    string(const string& other) :
      data_(nullptr), size_(other.size_), capacity_(other.capacity_)
      {
        if (size_ > 0) 
        {
          data_ = new char[capacity_];
          for (size_t i = 0; i < size_; ++i) 
          {
            data_[i] = other.data_[i];
          }
        }
      }

    // copy assignment operator
    string& operator=(const string& other) 
    {
      if (this != &other) 
      {
        string temp(other);
        swap(temp);
      }
      return *this;
    }

    // move constructor
    string(string&& other) :
      data_(exchange(other.data_, nullptr)),
      size_(exchange(other.size_, 0)),
      capacity_(exchange(other.capacity_, 0)) {}

    // move assignment operator
    string& operator=(string&& other) 
    {
      if (this != &other) 
      {
        clear();
        delete[] data_;
        data_ = exchange(other.data_, nullptr);
        size_ = exchange(other.size_, 0);
        capacity_ = exchange(other.capacity_, 0);
      }
      return *this;
    }

    // element access functions
    char& at(size_t index) 
    {
      if (index >= size_) throw std::out_of_range("index out of bounds");
      return data_[index];
    }
    const char& at(size_t index) const 
    { 
      if (index >= size_) throw std::out_of_range("index out of bounds");
      return data_[index];
    }
    char& operator[](size_t index) noexcept { return data_[index]; }
    const char& operator[](size_t index) const noexcept { return data_[index]; }
    char& front() noexcept { return data_[0]; }
    const char& front() const noexcept { return data_[0]; }
    char& back() noexcept { return data_[size_ - 1]; }
    const char& back() const noexcept { return data_[size_ - 1]; }
    char* data() noexcept { return data_; }
    const char* data() const noexcept { return data_; }
    
    // iterator functions
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    const_iterator cbegin() const { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }
    const_iterator cend() { return data_ + size_; }

    // capacity functions
    constexpr bool empty() const noexcept { return size_ == 0; }
    size_t size() const noexcept { return size_; }
    size_t length() const noexcept { return size_; }
    size_t capacity() const noexcept { return capacity_; }

    // reserve new capacity
    void reserve(size_t new_cap) 
    {
      if (capacity_ >= new_cap) return;
      char* new_data = new char[new_cap];
      for (size_t i = 0; i < size_; ++i) 
      {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = new_cap;
    }

    // decrease capacity to size
    void shrink_to_fit() noexcept 
    {
      if (size_ == capacity_) return;
      else if (size_ == 0) dealloc();
      char* new_data = new char[size_];
      for (size_t i = 0; i < size_; ++i) 
      {
        new_data[i] = data_[i];
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
    }

    // modifiers
    void clear() noexcept 
    {
      size_ = 0;
    }

    // append a single char to end of string
    void push_back(char& c) 
    {
      if (size_ == capacity_) 
      {
        size_t new_cap = (capacity_ == 0) ? 1 : 2 * capacity_;
        reserve(new_cap);
      }
      data_[size_++] = c;
    }
    // pop last char from string
    void pop_back() 
    {
      if (size_ > 0) 
      {
        --size_;
      }
    }

    // append single char to end of string
    string& append(size_t count, char c) 
    {
      size_t new_size = size_ + count;
      if (new_size > capacity_) 
      {
        size_t new_cap = max(new_size, 2 * capacity_);
        reserve(new_cap);
      }
      for (size_t i = 0; i < new_size; ++i) 
      {
        data_[i] = c;
      }
      size_ = new_size;
      return *this;
    }
    // append count chars from str to end of string object
    string& append(const char* str, size_t count) 
    {
      size_t new_size = size_ + count;
      if (new_size > capacity_) 
      {
        size_t new_cap = max(new_size, 2 * capacity_);
        reserve(new_cap);
      }
      for (size_t i = 0; i < count; ++i) 
      {
        data_[size_ + i] = str[i];
      }
      size_ = new_size;
      return *this;
    }
    // append chars in str to end of string
    string& append(const char* str) 
    {
      size_t new_size = size_ + strlen(str);
      if (new_size > capacity_) 
      {
        size_t new_cap = max(new_size, 2 * capacity_);
        reserve(new_cap);
      }
      memcpy(data_ + size_, str, strlen(str));
      size_ = new_size;
      return *this;
    }
    // append other string to end of string
    string& append(const string& str) 
    {
      size_t new_size = size_ + str.size_;
      if (new_size > capacity_) 
      {
        size_t new_cap = max(new_size, 2 * capacity_);
        reserve(new_cap);
      }
      memcpy(data_ + size_, str.data_, str.size_);
      size_ = new_size;
      return *this;
    }
    // append initializer list of chars to end of string
    string& append(std::initializer_list<char> list) 
    {
      size_t new_size = size_ + list.size();
      if (new_size > capacity_) 
      {
        size_t new_cap = max(new_size, 2 * capacity_);
        reserve(new_cap);
      }
      std::uninitialized_copy(list.begin(), list.end(), data_ + size_);
      size_ = new_size;
      return *this;
    }

    // append another string object to end of string
    string& operator+=(const string& str) 
    {
      if (!str.empty())
      {
        size_t new_size = str.length() + size_;
        if (new_size > capacity_) 
        {
          size_t new_cap = std::max(2 * capacity_, new_size);
          reserve(new_cap);
        }
        memcpy(data_ + size_, str.data_, str.length());
        size_ = new_size;
      }
      return *this;
    }
    // append char to end of string
    string& operator+=(char c) 
    {
      if (size_ == capacity_) 
      {
        size_t new_cap = (capacity_ == 0) ? 1 : 2 * capacity_;
        reserve(new_cap);
      }
      data_[size_++] = c;
      return *this;
    }
    // append all chars of const char pointer to string
    string& operator+=(const char* str) 
    {
      if (strlen(str) > 0) 
      {
        size_t new_size = size_ + strlen(str);
        if (new_size > capacity_) 
        {
          size_t new_cap = std::max(2 * capacity_, new_size);
          reserve(new_cap);
        }
        memcpy(data_ + size_, str, strlen(str));
        size_ = new_size;
      }
      return *this;
    }
    // append init list to end of string
    string& operator+=(std::initializer_list<char> list) 
    {
      if (list.size() > 0) 
      {
        size_t new_size = size_ + list.size();
        if (new_size > capacity_) 
        {
          size_t new_cap = std::max(2 * capacity_, new_size);
          reserve(new_cap);
        }
        std::uninitialized_copy(list.begin(), list.end(), data_ + size_);
      } 
      return *this;
    }

    // delegate resize function without speicifed value to other with default constructor
    void resize(size_t count) { resize(count, char{}); }
    // resize the string to count size; appends c to end if count > size
    void resize(size_t count, char c) 
    {
      if (size_ == count) return;
      else if (size_ > count) 
      {
        size_ = count;
      }
      else
      {
        reserve(count);
        for (size_t i = size_; i < count; ++i) 
        {
          data_[i] = c;
        }
        size_ = count;
      }
    }
    
    // swap contents with other string
    void swap(string& other)
    {
      swap(data_, other.data_);
      swap(size_, other.size_);
      swap(capacity_, other.capacity_);
    }

    // substring method
    string substr(size_t pos = 0, size_t count = npos) const {
      if (size_ == 0) return string();
      else if (pos >= size_) throw std::out_of_range("position out of bounds");
      else if (count == 0) return string();
      size_t remaining = size_ - pos;
      size_t length = (count == npos || count > remaining) ? remaining : count;
      return string(data_ + pos, length);
    }

    // functions i/o functions to allow for accessing private members
    friend std::ostream& operator<<(std::ostream& os, const string& str);
    friend std::istream& operator>>(std::istream& is, string& str);
  };

  // non-member comparison
  inline bool operator==(const string& lhs, const string& rhs) {
    return strcmp(lhs.data(), rhs.data()) == 0;
  }
  inline bool operator!=(const string& lhs, const string& rhs) {
    return !(lhs == rhs);
  }
  inline bool operator==(const string& lhs, const char* rhs) {
    return strcmp(lhs.data(), rhs) == 0;
  }
  inline bool operator!=(const string& lhs, const char* rhs) {
    return !(lhs == rhs);
  }
  inline bool operator==(const char* lhs, const string& rhs) {
    return rhs == lhs;
  }
  inline bool operator!=(const char* lhs, const string& rhs) {
    return !(lhs == rhs);
  }

  // non-member function for output stream
  inline std::ostream& operator<<(std::ostream& os, const string& str) 
  {
    if (str.data_ && str.size_ > 0) 
    {
      for (size_t i = 0; i < str.size_; ++i) 
      {
        os << str.data_[i];
      }
    }
    return os;
  }
  // non-member function for input stream
  inline std::istream& operator>>(std::istream& is, string& str) 
  {
    char buffer[1000];
    is >> buffer;
    delete[] str.data_;
    str.capacity_ = strlen(buffer);
    str.size_ = str.capacity_;
    if (str.size_ > 0) 
    {
      str.data_ = new char[str.capacity_];
      memcpy(str.data_, buffer, str.size_);
    }
    else 
    {
      str.data_ = nullptr;
    }
    return is;
  }
}

#endif