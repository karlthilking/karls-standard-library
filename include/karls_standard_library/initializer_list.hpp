#ifndef KARLS_STANDARD_LIBRARY_INITIALIZER_LIST_HPP
#define KARLS_STANDARD_LIBRARY_INITIALIZER_LIST_HPP

namespace karls_standard_library {
  template<typename T>
  class initializer_list {
  private:
    const T* m_ptr;
    size_t size_;

    // private constructor
    constexpr initializer_list(const T* ptr, size_t size) noexcept : m_ptr(ptr), size_(size) {}
  public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using size_type = size_t;
    using iterator = const T*;
    using const_iterator = const T*;

    // default constructor
    initializer_list() noexcept : m_ptr(nullptr), size_(0) {}
    
    // returns the size of the initializer list
    size_t size() const noexcept { return size_; }

    // return pointer to first element
    constexpr const T* begin() const noexcept {
      return m_ptr;
    }

    // return pointer to last element
    constexpr const T* end() const noexcept {
      return m_ptr + size_; 
    }
  };
}

#endif 