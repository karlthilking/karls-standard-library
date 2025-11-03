#ifndef KARLS_STANDARD_LIBRARY_VECTOR_HPP
#define KARLS_STANDARD_LIBRARY_VECTOR_HPP

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
      deallocate(m_ptr + capacity);
      m_ptr = new_ptr;
      capacity = new_cap;
    }
  public:
    // default constructor
    Vector() : m_ptr(nullptr), size(0), capacity(0) {}

    // destructor
    ~Vector() : 

    // copy assignment operator
    Vector& operator=(const Vector& other) {
      
    }

    // list initialization assignment 
    Vector& operator=(initializer_list<T> list) {

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

    void pop_back() {
      if (size > 0) {
        --size;
      }
    }

    // reserve new capacity
    void reserve(size_t new_cap) {
      if (new_cap > capacity) {
        T* new = allocate(new_cap);
        for (size_t i = 0; i < size; ++i) {
          construct(new + i, move(m_ptr[i]));
          destroy(m_ptr + i);
          
        }
        deallocate(m_ptr + capacity);
        m_ptr = new;
        capacity = new_cap;
      }

    }

    // resize vector to new size with optional value
    void resize(size_t count, const T& value = T{}) {
      if (count == size) {
        return;
      }
      else if (size > count) {
        T* new = allocate(count);
        for (size_t i = 0; i < count; i++) {
          construct(new, m_ptr[i]);
          destroy(m_ptr + i);
        }
        deallocate(m_ptr + capacity);
        m_ptr = new;
        capacity = count;
        size = count; 
      }

    }

    template<typename ...Args>
    void emplace_back(Args&&... args) {

    }
  };
}

#endif