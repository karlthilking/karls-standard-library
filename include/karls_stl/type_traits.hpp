#ifndef KARLS_STL_TYPE_TRAITS_HPP
#define KARLS_STL_TYPE_TRAITS_HPP

namespace karls_stl {
  // primary remove reference
  template<typename T>
  struct remove_reference {
    using type = T;
  };

  // lvalue remove reference
  template<typename T>
  struct remove_reference<T&> {
    using type = T;
  };

  // rvalue remove reference
  template<typename T>
  struct remove_reference<T&&> {
    using type = T;
  };

  // remove reference alias
  template<typename T>
  using remove_reference_t = typename remove_reference<T>::type;

  // primary remove const
  template<typename T>
  struct remove_const {
    using type = T;
  };

  // const remove const
  template<typename T>
  struct remove_const<const T> {
    using type = T;
  };

  // remove const alias
  template<typename T>
  using remove_const_t = typename remove_const<T>::type;

  // remove const and volative
  template<typename T>
  struct remove_cv {
    using type = remove_const<typename remove_volative<T>::type>::type;
  };

  // remove const and volative alias
  template<typename T>
  using remove_cv_t = typename remove_cv<T>::type;

  // primary decay
  // remove reference, const, volative, convert arrays and functions to pointers
  template<typename T>
  struct decay {
  private:
  public:
  };

  // decay alias
  template<typename T>
  using decay_t = typename decay<T>::type;
}


#endif