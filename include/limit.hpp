#ifndef KARLS_STANDARD_LIBRARY_LIMITS_HPP
#define KARLS_STANDARD_LIBRARY_LIMITS_HPP

namespace karls_standard_library {
  template<typename T>
  class numeric_limits {
    static constexpr T min() noexcept { return T(); }
    static constexpr T lowest() noexcept { return T(); }
    static constexpr T max() noexcept { return T(); }
  };

  template<>
  class numeric_limits<int> {
  public:
    static constexpr int min() noexcept { return -2147483648; }
    static constexpr int lowest() noexcept { return -2147483648; }
    static constexpr int max() noexcept { return 2147483647; }
  };

  template<>
  class numeric_limits<double> {
  public:
    static constexpr double min() noexcept { return 2.22507e-308; }
    static constexpr double lowest() noexcept { return -1.79769e+308; }
    static constexpr double max() noexcept { return 1.79769e+308; }
  };

  template<>
  class numeric_limits<float> {
  public:
    static constexpr float min() noexcept { return 1.17549e-38; }
    static constexpr float lowest() noexcept { return -3.40282e+38; }
    static constexpr float max() noexcept { return 3.40282e+38; }
  };


}

#endif