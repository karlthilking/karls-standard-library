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

  string def;
  string cstr = string("hello");
  string fill = string(5, 'a');
  string cstr_f = string("hello123", 5);
  string init_list{'a', 'b', 'c'};

};


// basic constructor tests
TEST_F(string_test, default_constructor)
{
  EXPECT_EQ(def.size(), 0);
  EXPECT_TRUE(def.empty());
  EXPECT_EQ(def.capacity(), 0);
}

TEST_F(string_test, cstring_constructor)
{
  EXPECT_TRUE(!cstr.empty());
  EXPECT_EQ(cstr.size(), 5);
  EXPECT_GE(cstr.capacity(), 5);
  EXPECT_EQ(cstr[0], 'h');
}

TEST_F(string_test, fill_constructor)
{
  EXPECT_TRUE(!fill.empty());
  EXPECT_EQ(fill.size(), 5);
  EXPECT_GE(fill.capacity(), 5);
  EXPECT_EQ(fill[0], 'a');
}

TEST_F(string_test, cstring_fill_constructor)
{
  EXPECT_TRUE(!cstr_f.empty());
  EXPECT_EQ(cstr_f.size(), 5);
  EXPECT_GE(cstr_f.capacity(), 5);
  EXPECT_EQ(cstr_f[0], 'h');
}

TEST_F(string_test, intializer_list_constructor)
{
  EXPECT_TRUE(!init_list.empty());
  EXPECT_EQ(init_list.size(), 3);
  EXPECT_GE(init_list.size(), 3);
  EXPECT_EQ(init_list[0], 'a');
}

TEST_F(string_test, copy_constructor)
{

}

TEST_F(string_test, move_constructor)
{

}



