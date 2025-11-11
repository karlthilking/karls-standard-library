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

  void SetUp() override
  {
    cstr_constructed = string("hello");
    cstr_fill_constructed = string("hello123", 5);
    fill_constructed = string(5, 'a');
    init_list_constructed = string{'w', 'o', 'r', 'd'};

    copy_dummy1 = string("copy test 1");
    copy_dummy2 = string("copy test 2");

    move_dummy1 = string("move test 1");
    move_dummy2 = string("move test 2");
  }

  string default_constructed;
  string cstr_constructed;
  string cstr_fill_constructed;
  string fill_constructed;
  string init_list_constructed;

  string copy_dummy1;
  string copy_dummy2;

  string move_dummy1;
  string move_dummy2;
};

TEST_F(string_test, default_constructor)
{
  EXPECT_TRUE(default_constructed.empty());
  EXPECT_EQ(default_constructed.size(), 0);
  EXPECT_EQ(default_constructed.capacity(), 0);
}

TEST_F(string_test, cstr_constructors)
{
  EXPECT_TRUE(!cstr_constructed.empty());
  EXPECT_EQ(cstr_constructed.size(), 5);
  EXPECT_GE(cstr_constructed.capacity(), 5);

  EXPECT_TRUE(!cstr_fill_constructed.empty());
  EXPECT_EQ(cstr_fill_constructed.size(), 5);
  EXPECT_GE(cstr_fill_constructed.capacity(), 5);

  EXPECT_TRUE(cstr_constructed == cstr_fill_constructed);
  EXPECT_TRUE(cstr_constructed == "hello");
}

TEST_F(string_test, fill_constructor)
{
  EXPECT_EQ(fill_constructed.size(), 5);
  EXPECT_TRUE(fill_constructed == "aaaaa");
  EXPECT_EQ(fill_constructed.capacity(), 5);
}

TEST_F(string_test, copy_operations)
{
  string temp1(copy_dummy1);
  EXPECT_EQ(temp1, copy_dummy1);
  EXPECT_EQ(temp1, "copy test 1");

  string temp2;
  temp2 = copy_dummy2;
  EXPECT_EQ(temp2, copy_dummy2);
  EXPECT_EQ(temp2, "copy test 2");
}

TEST_F(string_test, move_operations)
{
  string temp1(move(move_dummy1));
  EXPECT_EQ(temp1, "move test 1");
  EXPECT_FALSE(temp1 == move_dummy1);


  string temp2;
  temp2 = move(move_dummy2);
  EXPECT_EQ(temp2, "move test 2");
  EXPECT_FALSE(temp2 == move_dummy2);
}
