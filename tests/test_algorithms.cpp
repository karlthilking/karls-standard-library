#include <iostream>
#include <stdexcept>
#include <climits>
#include <iterator>
#include <gtest/gtest.h>
#include "karls_standard_library/algorithm.hpp"
#include "karls_standard_library/string.hpp"
#include "karls_standard_library/vector.hpp"

using namespace karls_standard_library;

class algorithms_test : public testing::Test
{
protected:
  algorithms_test() = default;
  ~algorithms_test() = default;

  void SetUp() override
  {
    x = 42;
    y = 100;
    s1 = "test1";
    s2 = "test1";
    s3 = "test2";
    vec1 = vector{1, 2, 3, 4, 5};
    vec2 = vector{4, 4, 4, 4, 4};
  }
  int x;
  int y;
  string s1;
  string s2;
  string s3;
  vector<int> vec1;
  vector<int> vec2;

  struct is_odd
  {
    bool operator()(const int& x) { return x % 2; }
  };
  struct is_even
  {
    bool operator()(const int& x) { return !(x % 2); }
  };
};

TEST_F(algorithms_test, min)
{
  EXPECT_EQ(min(x, y), x);
  EXPECT_EQ(min(0, 1), 0);
  EXPECT_EQ(min(INT_MAX, 248), 248);
}

TEST_F(algorithms_test, max)
{
  EXPECT_EQ(max(x, y), y);
  EXPECT_EQ(max(100, 24), 100);
  EXPECT_EQ(max(INT_MIN, 66), 66);
}

TEST_F(algorithms_test, equal)
{
  EXPECT_EQ(equal(s1.begin(), s1.end(), s2.begin()), true);
  EXPECT_EQ(equal(s1.begin(), s1.end(), s3.begin()), false);
}

TEST_F(algorithms_test, three_way_comparison)
{
  EXPECT_TRUE(
    lexicographical_compare_three_way(
      s1.begin(), s1.end(),
      s2.begin(), s2.end()
    ) == std::strong_ordering::equal
  );

  EXPECT_FALSE(
    lexicographical_compare_three_way(
      s1.begin(), s1.end(),
      s3.begin(), s3.end()
    ) == std::strong_ordering::equal
  );

  EXPECT_TRUE(
    lexicographical_compare_three_way(
      s1.begin(), s1.end(),
      s3.begin(), s3.end()
    ) == std::strong_ordering::less
  );
}

TEST_F(algorithms_test, find_tests)
{
  // test find, find_if, and find_if_not
  auto it1 = find(vec1.begin(), vec1.end(), 3);
  size_t ix1 = 2;
  EXPECT_TRUE(it1 != vec1.end());
  EXPECT_EQ(std::distance(vec1.begin(), it1), ix1);
  
  auto it2 = find_if(vec1.begin(), vec1.end(), is_odd());
  size_t ix2 = 0;
  EXPECT_TRUE(it2 != vec1.end());
  EXPECT_EQ(std::distance(vec1.begin(), it2), ix2);

  auto it3 = find_if_not(vec1.begin(), vec1.end(), is_even());
  size_t ix3 = 0;
  EXPECT_TRUE(it3 != vec1.end());
  EXPECT_EQ(std::distance(vec1.begin(), it3), ix3);
}

TEST_F(algorithms_test, all_of)
{
  bool result1 = all_of(vec2.begin(), vec2.end(), is_even());
  EXPECT_EQ(result1, true);

  auto equals_four = [](const int& x) -> bool { return x == 4; };
  bool result2 = all_of(vec2.begin(), vec2.end(), equals_four);
  EXPECT_EQ(result2, true);

  bool result3 = all_of(vec2.begin(), vec2.end(), is_odd());
  EXPECT_NE(result3, true);
}

TEST_F(algorithms_test, any_of)
{
  bool result1 = any_of(vec1.begin(), vec1.end(), is_odd());
  EXPECT_EQ(result1, true);

  bool result2 = any_of(vec1.begin(), vec1.end(), is_even());
  EXPECT_EQ(result2, true);

  auto equals_hundred = [](const int& x) -> bool { return x == 100; };
  bool result3 = any_of(vec2.begin(), vec2.end(), equals_hundred);
  EXPECT_NE(result3, true);
}

TEST_F(algorithms_test, none_of)
{
  bool result1 = none_of(vec1.begin(), vec1.end(), is_odd());
  EXPECT_NE(result1, true);

  bool result2 = none_of(vec2.begin(), vec2.end(), is_odd());
  EXPECT_EQ(result2, true);

  auto equals_5 = [](const int& x) -> bool { return x == 5; };
  bool result3 = none_of(vec2.begin(), vec2.end(), equals_5);
  EXPECT_EQ(result3, true);
}

TEST_F(algorithms_test, count_tests)
{
  // test count and count if
  size_t result1 = count(vec2.begin(), vec2.end(), 4);
  EXPECT_EQ(result1, 5);

  size_t result2 = count(vec1.begin(), vec1.end(), 3);
  EXPECT_EQ(result2, 1);

  size_t result3 = count_if(vec2.begin(), vec2.end(), is_even());
  EXPECT_EQ(result3, 5);

  size_t result4 = count_if(
    vec2.begin(), vec2.end(), 
    [](const int& x) -> bool { return x == 1; }
  );
  EXPECT_EQ(result4, 0);
}