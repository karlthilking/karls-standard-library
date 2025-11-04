#ifndef KARLS_STANDARD_LIBRARY_FUNCTIONAL_HPP
#define KARLS_STANDARD_LIBRARY_FUNCTIONAL_HPP

namespace karls_standard_library {
  // less than operator wrapper
  template<typename T>
  struct less {
    constexpr bool operator()(const T& lhs, const T& rhs) const {
      return lhs < rhs;
    }
  };

  // greater than operator wrapper
  template<typename T>
  struct greater {
    constexpr bool operator()(const T& lhs, const T& rhs) const {
      return lhs > rhs;
    }
  };

  // equal to operator wrapper
  template<typename T>
  struct equal_to {
    constexpr bool operator()(const T& lhs, const T& rhs) const {
      return lhs == rhs;
    }
  };

  // not equal to operator wrapper
  template<typename T>
  struct not_equal_To {
    constexpr bool operator()(const T& lhs, const T& rhs) const {
      return lhs != rhs;
    }
  };
}

#endif