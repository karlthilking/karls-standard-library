#ifndef KARLS_STANDARD_LIBRARY_MEMORY_HPP
#define KARLS_STANDARD_LIBRARY_MEMORY_HPP

#include "utility.hpp"
#include <type_traits>
#include <compare>
#include <functional>

namespace karls_standard_library
{
  template<typename T>
  class unique_ptr
  {
  public:
    using value_type = T;
    using pointer = value_type*;
  private:
    T* data_;
  public:
    // default constructor
    constexpr unique_ptr() noexcept : data_(nullptr) {}

    // destructor 
    ~unique_ptr() { delete data_; }

    // nullptr constructor and assignment operator
    constexpr unique_ptr(nullptr_t) : data_(nullptr) {}
    unique_ptr& operator=(nullptr_t)
    {
      delete data_;
      data_ = nullptr;
      return *this;
    }

    // copy constructor and assignment operator
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    // raw pointer constructor
    explicit unique_ptr(pointer p) : data_(p) {}

    // move constructor and assignment operator
    unique_ptr(unique_ptr&& other) noexcept : data_(other.release()) {}
    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
      if (this != &other)
      {
        reset(other.release());
      }
      return *this;
    }

    // modifiers
    pointer release() noexcept
    {
      pointer old = data_;
      data_ = nullptr;
      return old;
    }
    void reset(pointer p = nullptr) noexcept
    {
      if (data_ != p)
      {
        delete[] data_;
        data_ = p;
      }
    }
    void swap(unique_ptr& other) noexcept 
    {
      swap(data_, other.data_);
    }

    // observers
    pointer get() const noexcept { return data_; }
    constexpr operator bool() const noexcept { return data_ != nullptr; }

    pointer operator->() const noexcept { return data_; }
    std::add_lvalue_reference_t<T> operator*() noexcept(noexcept(*std::declval<pointer>())) { return *data_; }

    // equality operators
    template<typename U>
    constexpr bool operator==(const unique_ptr<U>& other) const noexcept { return data_ == other.data_; }
    constexpr bool operator==(nullptr_t) const noexcept { return data_ == nullptr; }

    // three way comparison operators
    template<typename U>
    std::strong_ordering operator<=>(const unique_ptr<U>& other) const noexcept
    {
      using common_type = std::common_type_t<typename unique_ptr<T>::pointer, typename unique_ptr<U>::pointer>;
      return std::less<common_type>{}(data_, other.data_) ? std::strong_ordering::less :
             std::less<common_type>{}(other.data_, data_) ? std::strong_ordering::greater :
             std::strong_ordering::equal;
    }
    std::strong_ordering operator<=>(nullptr_t) const noexcept
    {
      return data_ == nullptr ? std::strong_ordering::equal : std::strong_ordering::greater;
    }
  };

  template<typename T>
  class unique_ptr<T[]>
  {
  public:
    using element_type = T;
    using reference = element_type&;
    using pointer = element_type*;
  private:
    pointer data_;
  public:
    // default constructor and destructor
    constexpr unique_ptr() noexcept : data_(nullptr) {}
    ~unique_ptr() { delete[] data_; }

    // null pointer constructor and assignment
    constexpr unique_ptr(nullptr_t) noexcept : data_(nullptr) {}
    unique_ptr& operator=(nullptr_t)
    {
      delete[] data_;
      data_ = nullptr;
      return *this;
    }

    // raw pointer constructor
    template<typename U>
    explicit unique_ptr(pointer p) noexcept(std::is_same_v<pointer, U> || std::is_same_v<nullptr_t, U>) :
      data_(p) {}
    
    // explicitly delete copy constructor and copy assignment
    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr& operator=(const unique_ptr& other) = delete;

    // move constructor and move assignment
    unique_ptr(unique_ptr&& other) noexcept : data_(other.release()) {}
    unique_ptr& operator=(unique_ptr&& other) noexcept
    {
      if (this != &other)
      {
        reset(other.release());
      }
      return *this;
    }

    // modifiers
    pointer release() noexcept
    {
      pointer old = data_;
      data_ = nullptr;
      return old;
    }
    void reset(pointer p = nullptr) noexcept
    {
      if (data_ != p)
      {
        delete[] data_;
        data_ = p;
      }
    }
    void swap(unique_ptr& other) noexcept
    {
      swap(data_, other.data_);
    }

    // observers
    pointer get() const noexcept { return data_; }
    explicit operator bool() const noexcept { return data_ != nullptr; }
    reference operator[](size_t index) const noexcept { return data_[index]; }

    // equality operators
    template<typename U>
    constexpr bool operator==(const unique_ptr<U>& other) const noexcept { return data_ == other.data_; }
    constexpr bool operator==(nullptr_t) const noexcept { return data_ == nullptr; }

    // three way comparison operators
    template<typename U>
    std::strong_ordering operator<=>(const unique_ptr<U>& other) const noexcept
    {
      using common_type = std::common_type_t<typename unique_ptr<T[]>::pointer, typename unique_ptr<U>::pointer>;
      return std::less<common_type>{}(data_, other.data_) ? std::strong_ordering::less :
             std::less<common_type>{}(other.data_, data_) ? std::strong_ordering::greater : 
             std::strong_ordering::equal;
    }
    std::strong_ordering operator<=>(nullptr_t) const noexcept
    {
      return data_ == nullptr ? std::strong_ordering::equal : std::strong_ordering::greater;
    }
  };

  // make unique for both non-array and array types
  template<typename T, typename... Args>
  constexpr unique_ptr<T> make_unique(Args&&... args)
  {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
  template<typename T>
  constexpr unique_ptr<T> make_unique(size_t size)
  {
    return unique_ptr<T>(new std::remove_extent_t<T>[size]());
  }
  
  // specialize swap algorithm for unique pointers
  template<typename T>
  void swap(unique_ptr<T>& lhs, unique_ptr<T>& rhs) noexcept { lhs.swap(rhs); }

}

#endif