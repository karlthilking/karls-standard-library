#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "karls_standard_library/string.hpp"
#include "karls_standard_library/utility.hpp"

using namespace karls_standard_library;

class string_test : public testing::Test 
{
protected:
  string_test() = default;
  ~string_test() = default;
};

TEST_F(string_test, default_constructor)
{
  string s1;
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s1.size(), 0);
  EXPECT_THROW(s1.at(0), std::out_of_range);
}

TEST_F(string_test, move_operations)
{
  string s1("test");
  string s2(move(s1));
  EXPECT_EQ(s2, "test");

  string s3("test2");
  string s4;
  s4 = move(s3);
  EXPECT_EQ(s4, "test2");
}
