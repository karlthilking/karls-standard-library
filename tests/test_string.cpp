#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "karls_standard_library/string.hpp"
#include "karls_standard_library/utility.hpp"

using namespace karls_standard_library;

class string_test : public testing::Test 
{
protected:
  void SetUp() override
  {
    string default_constructed;
    string cstr_constructed("cstr");
    string cstr_fill_constructed("cstr_filled", 11);
    string fill_constructed(5, 'f');
    string initializer_list_constructed{'i', 'n', 'i', 't'};
    string copied_from("copy me");
    string copy_constructed(copied_from);
    string moved_from("move me");
    string move_constructed(move(moved_from));
  }
  string default_constructed;
  string cstr_constructed;
  string cstr_fill_constructed;
  string fill_constructed;
  string initializer_list_constructed;
  string copy_constructed;
  string move_constructed;
};

// test default constructed string
TEST_F(string_test, default_constructor)
{
  EXPECT_TRUE(default_constructed.empty());
  EXPECT_EQ(default_constructed.size(), 0);
  EXPECT_EQ(default_constructed.capacity(), 0);
}

// test cstr constructed string
TEST_F(string_test, cstr_constructor)
{
  EXPECT_TRUE(!cstr_constructed.empty());
  EXPECT_EQ(cstr_constructed.size(), 4);
  EXPECT_EQ(cstr_constructed.capacity(), 4);
}

TEST_F(string_test, cstr_fill_constructor)
{
  EXPECT_TRUE(!cstr_fill_constructed.empty());
  EXPECT_EQ(cstr_fill_constructed.size(), 11);
  EXPECT_EQ(cstr_fill_constructed.capacity(), 11);
}

int main()
{
  return RUN_ALL_TESTS();
}


