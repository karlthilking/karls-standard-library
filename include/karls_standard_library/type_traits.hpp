#ifndef KARLS_STANDARD_LIBRARY_TYPE_TRAITS_HPP 
#define KARLS_STANDARD_LIBRARY_TYPE_TRAITS_HPP

namespace karls_standard_library {
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

  // primary is_function
  template<typename T>
  struct is_function : false_type {};

  // basic function type
  template<typename R, typename... Args>
  struct is_function<R(Args...)> : true_type {};

  // noexcept function
  template<typename R, typename... Args>
  struct is_function<R(Args...) noexcept> : true_type {};

  // const function
  template<typename R, typename... Args>
  struct is_function<R(Args...) const> : true_type {};

  // volatile function
  template<typename R, typename... Args>
  struct is_function<R(Args...) volatile> : true_type {};

  // const volatile function
  template<typename R, typename... Args>
  struct is_function<R(Args...) const volatile> : true_type {};

  // noexcept const function
  template<typename R, typename... Args>
  struct is_function<R(Args...) const noexcept> : true_type {};

  // noexcept volatile function
  template<typename R, typename... Args>
  struct is_function<R(Args...) volatile noexcept> : true_type {};

  // noexcept const volatile function
  template<typename R, typename... Args>
  struct is_function<R(Args...) const volatile noexcept> : true_type {};

  // alias for is_function
  template<typename T>
  inline constexpr bool is_function_v = is_function<T>::value;

  // primary is_lvalue_reference for non-lvalues
  template<typename T>
  struct is_lvalue_reference : false_type {};

  // binds to lvalues
  template<typename T>
  struct is_lvalue_reference<T&> : true_type {};

  // alias for is_lvalue_reference
  template<typename T>
  inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

  // primary is_rvalue_reference
  template<typename T>
  struct is_rvalue_reference : false_type {};

  // binds to rvalues
  template<typename T>
  struct is_rvalue_reference<T&&> : true_type {};

  // alias for is_rvalue_reference
  template<typename T>
  inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

  // primary remove_extent
  template<typename T>
  struct remove_extent {
    using type = T;
  };

  // remove_extent for bounded arrays
  template<typename T, size_t N>
  struct remove_extent<T[N]> {
    using type = T;
  };

  // remove_extent for unbounded array
  template<typename T>
  struct remove_extent<T[]> {
    using type = T;
  };

  template<typename T>
  using remove_extent_t = typename remove_extent<T>::type;

  // primary is_pointer for non pointer types
  template<typename T>
  struct is_pointer : false_type {};

  // for pointer types
  template<typename T>
  struct is_pointer<T*> : true_type {};

  // pointer to const
  template<typename T>
  struct is_pointer<T* const> : true_type {};

  // pointer to volatile
  template<typename T>
  struct is_pointer<T* volatile> : true_type {};

  // pointer to const volatile
  template<typename T>
  struct is_pointer<T* const volatile> : true_type {};

  // is_pointer alias
  template<typename T>
  inline constexpr bool is_pointer_v = is_pointer<T>::value;

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
  using conditional_t = typename conditional<B,T,F>::type;

  namespace detail {
    template<typename T>
    struct type_identity {
      using type = T;
    };
    
    // tries to add a pointer for referenceable type
    template<typename T>
    auto try_add_pointer(int) -> type_identity<typename remove_reference<T>::type*>;
    
    // tries to add a pointer for types that cannot be referenced
    template<typename T>
    auto try_add_pointer(...) -> type_identity<T>;
    
    //
    template<typename T>
    auto try_add_lvalue_reference(int) -> type_identity<T&>;

    template<typename T>
    auto try_add_lvalue_reference(...) -> type_identity<T>;

    template<typename T>
    auto try_add_rvalue_reference(int) -> type_identity<T&&>;

    template<typename T>
    auto try_add_rvalue_reference(...) -> type_identity<T>;

    // primary is_unbounded_array_v for non array types
    template<typename>
    constexpr bool is_unbounded_array_v = false;

    // for unbounded array types
    template<typename T>
    constexpr bool is_unbounded_array_v<T[]> = true;

    // is_bounded_array_v primary
    template<typename>
    constexpr bool is_bounded_array_v = false;

    // for bounded arrays
    template<typename T, size_t N>
    constexpr bool is_bounded_array_v<T[N]> = true;

  }

  // adds a pointer if T* is a valid type
  template<typename T>
  struct add_pointer : decltype(detail::try_add_pointer<T>(0)) {};

  // alias for add_pointer
  template<typename T>
  using add_pointer_t = typename add_pointer<T>::type;

  // creates an lvalue reference of type T
  template<typename T>
  struct add_lvalue_reference : 
    decltype(detail::try_add_lvalue_reference<T>(0)) {};

  // alias for add_lvalue_reference
  template<typename T>
  using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

  // creates an rvalue reference of type T
  template<typename T>
  struct add_rvalue_reference :
    decltype(detail::try_add_rvalue_reference<T>(0)) {};

  // alias for add_rvalue_reference
  template<typename T>
  using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

  template<typename T>
  add_rvalue_reference_t<T> declval() noexcept;

  // primary is_same for different types
  template<typename T, typename U>
  struct is_same : false_type {};

  // same type
  template<typename T>
  struct is_same<T, T> : true_type {};

  // alias for is_same
  template<typename T, typename U>
  inline constexpr bool is_same_v = is_same<T, U>::value;

  // check if T is a void type
  template<typename T>
  struct is_void : is_same<void, typename remove_cv<T>::type> {};

  // alias for is_void
  template<typename T>
  inline constexpr bool is_void_v = is_void<T>::value;

  // primary decay
  // remove reference, const, volatile
  // convert arrays and functions to pointers
  template<typename T>
  struct decay {
  private:
    using U = typename remove_reference_t<T>::type;
  public:
    using type = typename conditional 
      is_array<U>::value,
      typename remove_extent<U>::type*,
      typename conditional
        is_function<U>::value,
        typename add_pointer<U>::type,
        typename remove_cv<U>::type
      >::type
    >::type;
  };

  // decay alias
  template<typename T>
  using decay_t = typename decay<T>::type;

  // returns true if T is constructible with Args, false otherwise
  template<typename T, typename... Args>
  struct is_constructible {
    static constexpr bool value = __is_constructible(T, Args...);
  };
  // alias for is_constructible
  template<typename T, typename... Args>
  inline constexpr bool is_constructible_v = is_constructible<T, Args...>::value;

  // returns true if is constructible and the variable definition does not call any non trivial operations
  template<typename T, typename... Args>
  struct is_trivially_constructible {
    static constexpr bool value = __is_trivially_constructible(T, Args...);
  };
  // alias for is_trivially constructible
  template<typename T, typename... Args>
  inline constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;

  // returns true if T is constructible with Args and the definition is noexcept
  template<typename T, typename... Args>
  struct is_nothrow_constructible {
    static constexpr bool value = __is_nothrow_constructible(T, Args...);
  };
  // alias for is_nothrow_constructible
  template<typename T, typename... Args>
  inline constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;

  // returns true if T has a move constructor or if T has a copy constructor that acceps const T&
  template<typename T>
  struct is_move_constructible {
    static constexpr bool value = is_constructible<T, typename add_rvalue_reference_t<T>>;
  };
  // alias for is_move_constructible
  template<typename T>
  inline constexpr bool is_move_constructible_v = is_move_constructible<T>::value;

  // returns true if T has a move constructor and no non-trivial operations occur
  template<typename T>
  struct is_trivially_move_constructible {
    static constexpr bool value = is_trivially_constructible<T, typename add_rvalue_reference_t<T>>;
  };
  // alias for is_trivially_move_constructible
  template<typename T>
  inline constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;

  // returns true if T has a move constructor that is noexcept
  template<typename T>
  struct is_nothrow_move_constructible {
    static constexpr bool value = is_nothrow_constructible<T, typename add_rvalue_reference_t<T>>;
  };
  // alias for is_nothrow_move_constructible
  template<typename T>
  inline constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;

  // if true, enable_if contains the type otherwise it will not
  template<bool B, typename T = void>
  struct enable_if {};

  template<typename T>
  struct enable_if<true, T> {
    using type = T;
  };

  // enable_if alias
  template<bool B, typename T>
  using enable_if_t = typename enable_if<B, T>::type;
}


#endif