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

  // primary remove volatile
  template<typename T>
  struct remove_volatile {
    using type = T;
  };

  // volatile remove volatile
  template<typename T>
  struct remove_volatile<volatile T> {
    using type = T;
  };

  // remove volatile alias
  template<typename T>
  using remove_volatile_t = typename remove_volatile<T>::type;

  // remove const and volatile
  template<typename T>
  struct remove_cv {
    using type = typename remove_const<typename remove_volatile<T>::type>::type;
  };

  template<typename T>
  using remove_cv_t = typename remove_cv<T>::type;

  // integral constant implementation
  template<typename T, T v>
  struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
  };

  // boolean aliases for integral constant
  using true_type = integral_constant<bool, true>;
  using false_type = integral_constant<bool, false>;

  // primary is_array
  template<typename T>
  struct is_array : false_type {};

  // checks for an unbounded array
  template<typename T>
  struct is_array<T[]> : true_type {};

  // checks for a bounded array
  template<typename T, size_t N>
  struct is_array<T[N]> : true_type {};

  // alias for is_array
  template<typename T>
  constexpr bool is_array_v = is_array<T>::value;

  // primary is_pointer
  template<typename T>
  struct is_pointer : false_type {};

  // checks if the type is a pointer to T
  template<typename T>
  struct is_pointer<T*> : true_type{};

  // specialized is_pointer for a const pointer to T
  template<typename T>
  struct is_pointer<T* const> : true_type {};

  // specialized is_pointer for a volatile pointer to T
  template<typename T>
  struct is_pointer<T* volatile> : true_type {};

  // specialized is_pointer for a const volatile pointer to T
  template<typename T>
  struct is_pointer<T* const volatile> : true_type {};

  // is_pointer alias
  template<typename T>
  constexpr bool is_pointer_v = is_pointer<T>::value;

  //
  template<bool B, typename T, typename F>
  struct conditional {
    using type = T;
  };

  //
  template<typename T, typename F>
  struct conditional<false, T, F> {
    using type = F;
  };

  // conditional alias
  template<bool B, typename T, typename F>
  using conditional_t = conditional<B,T,F>::type;

  namespace detail {
    template<typename T>
    struct type_identity { using type = T };

    template<typename T>
    struct try_add_pointer
  }

  // adds a pointer if T is a referencable type
  template<typename T>
  struct add_pointer : decltype(detail::try_add_pointer<T>(0)) {};

  template<typename T>
  using add_pointer_t = typename add_pointer<T>::type;

  // primary decay
  // remove reference, const, volatile
  // convert arrays and functions to pointers
  template<typename T>
  struct decay {
  private:
    using U = typename remove_reference_t<T>::type;
  public:
    using type = typename remove_cv_t<U>::type;
  };

  // decay alias
  template<typename T>
  using decay_t = typename decay<T>::type;
}


#endif