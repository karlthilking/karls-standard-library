#include <iostream>
#include <stdexcept>
#include <climits>
#include <gtest/gtest.h>
#include "karls_standard_library/algorithm.hpp"
#include "karls_standard_library/string.hpp"

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
  }
  int x;
  int y;
  string s1;
  string s2;
  string s3;
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