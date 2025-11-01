#include <iostream>
#include "utility.hpp"

// test different methods of constructing karls_stl pair
void test_pair_construction() {
  // 1. default construction
  karls_stl::pair<int, int> p1;

  // 2. value construction
  karls_stl::pair<int, int> p2(2, 4);

  // 3. copy construction
  karls_stl::pair<int, int> p3(p2);

  // 4. move construction
  karls_stl::pair<int, int> p4(karls_stl::move(p3))

  // 5. perfect forwarding construction
  std::string s = "test123";
  karls_stl::pair<long, std::string> p5(24, s);

  // 6. perfect forwarding with temporary objects
  karls_stl::pair<int, std::string> p6(10, std::string("hi"));

  // 7. converting construction from different pair types
  karls_stl::pair<short, int> p7(1, 2);
  karls_stl::pair<int, long> p8(p7);

  // 8. construction with list initialization
  karls_stl::pair<int, int> p9({10, 10});

  // 9. construction using make_pair
  auto p10 = karls_stl::make_pair(1, "1");

  // 10. construction using make_pair with move
  std::string temp = "hello";
  auto p11 = karls_stl::make_pair(1, karls_stl::move(temp));
}

// test pair assignment methods
void test_pair_assignment() {
  karls_stl::pair<int, int> test(1, 100);

  // 1. copy assignment
  karls_stl::pair<int, int> p1(4, 4);
  test = p1;

  // 2. move assignment
  karls_stl::pair<int, int> p2(32, 64);
  test = karls_stl::move(p2);

  // 3. converting assignment
  karls_stl::pair<short, short> p3(2, 2);
  test = p3;

  // 4. direct assignment
  test.first = -1;
  test.second = -1;

  // 5. self-assignment
  target = target;
}

// test pair swap functions
void test_pair_utilities() {
  karls_stl::pair<int, std::string> p1(1, "hi");
  karls_stl::pair<int, std::string> p2(2, "hello");

  // 1. member swap
  p1.swap(p2);

  // 2. non-member swap
  karls_stl::swap(p1, p2);
}

// test comparison operators
void test_pair_comparison() {
  karls_stl::pair<int, std::string> p1(1, "1");
  karls_stl::pair<int, std::string> p2(1, "2");
  karls_stl::pair<int, std::string> p3(2, "1");
  karls_stl::pair<int, std::string> p4(1, "1");

  // 1. equality comparison
  bool b1 = (p1 == p4);

  // 2. inequality comparison
  bool b2 = (p1 != p2);

}

void test_utility() {

}