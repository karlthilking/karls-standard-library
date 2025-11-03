#ifndef KARLS_STANDARD_LIBRARY_MEMORY_HPP
#define KARLS_STANDARD_LIBRARY_MEMORY_HPP

namespace karls_standard_library {
  // primary default delete
  template<typename T>
  struct default_delete {
    // default constructor
    constexpr default_delete() noexcept = default;

    // allow conversion from default_delete<U> to default_delete<T>
    // if U* can be converted to T*
    template<typename U>
    default_delete(const default_delete<U>&) noexcept {}

    // function call operator
    void operator()(T* ptr) const {
      static_assert(!is_void_v<T>);
      static_assert(sizeof(T) > 0);
      delete ptr;
    }
  };

  // default delete for arrays
  template<typename T>
  struct default_delete<T[]> {
    // default constructor
    constexpr default_delete<T[]>() noexcept = default;

    // conversion
    template<typename U>
    default_delete(const default_delete<U[]>&) noexcept {}

    // function call operator
    void operator()(T* ptr) const {
      static_assert(sizeof(T) > 0);
      delete[] ptr;
    }
  };

  template<typename T>
  class unique_ptr {
  private:
    // underlying pointer
    T* m_ptr;
  public:
    // default constructor
    unique_ptr() : m_ptr(nullptr) {}

    // raw pointer construction
    explicit unique_ptr(T* ptr) : m_ptr(ptr) {}

    // copy constructor (delete)
    unique_ptr(const unique_ptr& other) = delete;

    // copy assignment operator (delete)
    unique_ptr& operator=(const unique_ptr& other) = delete;

    // move constructor
    unique_ptr(unique_ptr&& other) : m_ptr(other.release()) {}

    // move assignment operator
    unique_ptr& operator=(unique_ptr&& other) {
      if (this != &other) {
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
      }
      return *this;
    }

    // release ownership of underlying pointer
    T* release() noexcept {
      T* old = m_ptr;
      m_ptr = nullptr;
      return old;
    }

    // take ownership of new ptr, delete original ptr
    void reset(T* ptr) noexcept {
      T* old = m_ptr;
      m_ptr = ptr;
      if (old) {
        delete old;
      }
    }

    // check if m_ptr owns anything
    explicit operator bool() const noexcept {
      return static_cast<bool>(m_ptr);
    }

    // return underlying pointer
    T* get() const noexcept { return m_ptr; }

    // arrow operator
    T* operator->() const noexcept { return m_ptr; }

    // dereference operator
    T& operator*() const noexcept { return *m_ptr; }
  };

  // make unique non member function
  template<typename T, typename... Args>
  unique_ptr<T> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }
  
}

#endif