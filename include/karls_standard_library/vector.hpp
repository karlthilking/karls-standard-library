#ifndef KARLS_STANDARD_LIBRARY_VECTOR_HPP
#define KARLS_STANDARD_LIBRARY_VECTOR_HPP

#include <stdexcept>
#include "utility.hpp"

namespace karls_standard_library {
  // vector implementation
  template<typename T>
  class Vector {
  private:
    T* m_ptr;
    size_t size;
    size_t capacity;
    
    // helper function to increase vector capacity
    void grow() {
      size_t new_cap = (capacity == 0) ? 1 : 2 * capacity;
      T* new_ptr = allocate(new_cap);
      for (size_t i = 0; i < size; ++i) {
        construct(new_ptr + i, move(m_ptr[i]));
        destroy(m_ptr + i);
      }
      deallocate(m_ptr, capacity);
      m_ptr = new_ptr;
      capacity = new_cap;
    }
  public:
    // default constructor
    Vector() : m_ptr(nullptr), size(0), capacity(0) {}

    // destructor
    ~Vector() {
      for (size_t i = 0; i < size; ++i) {
        destroy(m_ptr + i);
      }
      deallocate(m_ptr, capacity);
      m_ptr = nullptr;
      size = 0;
      capacity = 0;
    }

    // constructor with intitialize size and capacity, and optional value
    explicit Vector(size_t count, const T& value = T{}) : m_ptr(nullptr), size(count), capacity(count) {
      resize(count, value);
    }

    // range constructor with iterators
    template<typename Iterator>
    Vector(Iterator first, Iterator last) : m_ptr(nullptr), size(0), capacity(0) {
      for (auto it = first; it != last; ++it) {
        push_back(*it);
      }
    }

    // copy constructor
    Vector(const Vector& other) : m_ptr(nullptr), size(0), capacity(0) {
      reserve(other.size);
      for (size_t i = 0; i < other.size; ++i) {
        push_back(other[i]);
      }
    }

    // copy assignment operator
    Vector& operator=(const Vector& other) {
      if (this != &other) {
        clear();
        reserve(other.size);
        for (size_t i = 0; i < other.size; ++i) {
          push_back(other[i]);
        }
      }
      return *this;
    }

    // list initialization assignment 
    Vector& operator=(initializer_list<T> list) : m_ptr(nullptr), size(0), capacity(0) {
      reserve(list.size());
      for (const auto& item : list) {
        push_back(item);
      }
    }

    // move constructor
    Vector(Vector&& other) : m_ptr(other.m_ptr), size(other.size), capacity(other.capacity) {
      other.m_ptr = nullptr;
      other.size = 0;
      other.capacity = 0;
    } 

    // move assignment operator
    Vector& operator=(Vector&& other) {
      if (this != &other) {
        for (size_t i = 0; i < size; ++i) {
          destroy(m_ptr + i);
        }
        deallocate(m_ptr, capacity);
        m_ptr = other.m_ptr;
        size = other.size;
        capacity = other.capacity;
        other.m_ptr = nullptr;
        other.size = 0;
        other.capacity = 0;
      }
      return *this;
    }

    // assign 
    void assign(size_t count, const T& value) {

    }

    // return element at index with bounds checking
    T& at(size_t index) {
      if (index >= size) {
        throw std::out_of_range("index out of range");
      }
      return m_ptr[index];
    }
    const T& at(size_t index) const {
      if (index >= size) {
        throw std::out_of_range("index out of range");
      }
      return m_ptr[index];
    }

    // return element at specific index with direct access 
    T& operator[](size_t index) {
      return m_ptr[index];
    }
    const T& operator[](size_t index) const {
      return m_ptr[index];
    }
    
    // return first element
    const T& front() const {
      if (!empty()) {
        return m_ptr[0];
      }
    }

    // return last element
    const T& back() const {
      if (!empty()) {
        return m_ptr[size - 1];
      }
    }

    // return true if vector is empty, false otherwise
    bool empty() const {
      return size == 0;
    }

    // return size of the vector
    size_t size() const {
      return size;
    }
    
    // return capacity of the vector
    size_t capacity() const {
      return capacity;
    }

    // reduce capacity to size; remove unused capacity
    void shrink_to_fit() {
      while (capacity > size) {
        --capacity;
      }
    }

    // add element to back of vector
    void push_back(const T& value) {
      if (size == capacity) {
        grow();
      }
      construct(m_ptr + size, value);
      ++size;
    }
    void push_back(T&& value) {
      if (size == capacity) {
        grow();
      }
      construct(m_ptr + size, move(value));
      ++size;
    }

    // remove last element from the vector
    void pop_back() {
      if (size > 0) {
        --size;
      }
    }

    // reserve new capacity
    void reserve(size_t new_cap) {
      if (new_cap <= capacity) {
        return;
      }
      T* new_ptr = allocate(new_cap);
      for (size_t i = 0; i < size; ++i) {
        construct(new_ptr + i, move(m_ptr[i]));
        destroy(m_ptr + i);
      }
      deallocate(m_ptr, capacity);
      m_ptr = new_ptr;
      capacity = new_cap;
    }
    // resize vector
    void resize(size_t count) {
      if (count == size) {
        return;
      }
      else if (size > count) {
        for (size_t i = count; i < size; ++i) {
          destroy(m_ptr + i);
        }
        size = count;
      }
      else { // size < count
        for (size_t i = size; i < count; ++i) {
          construct(m_ptr + i, T{});
        }
        size = count;
        if (capacity < size) : capacity = count;
      }
    }

    // resize vector to new size with optional value
    void resize(size_t count, const T& value = T{}) {
      if (count == size) {
        return;
      }
      else if (size > count) {

      }
      else {

      }
    }

    // erase all elements from vector, maintain capacity
    void clear() {
      for(size_t i = 0; i < size; ++i) {
        destroy(m_ptr + i);
      }
      size = 0;
    }

    // construct object in place and add to vector
    template<typename ...Args>
    void emplace_back(Args&&... args) {
      if (size == capacity) {
        grow();
      }
      construct(m_ptr + size, forward<Args>(args)..);
      ++size;
    }

    // swap contents with other vector
    void swap(const Vector& other) noexcept {
      swap(m_ptr, other.m_ptr);
      swap(size, other.size);
      swap(capacity, other.capacity);
    }
  };

  // non member swap function
  template<typename T>
  void swap(Vector<T>& lhs, Vector<T>& rhs) noexcept {
    lhs.swap(rhs);
  }
}

#endif