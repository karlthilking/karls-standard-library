#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "karls_standard_library/vector.hpp"
#include "karls_standard_library/string.hpp"

using namespace karls_standard_library;

class vector_test : public testing::Test 
{
protected:
  void SetUp() override
  {
    vector<int> empty;
    vector<int> filled(5, 1);
    vector<int> init{1, 2, 3, 4, 5};
    vector<string> copied_from{"copy", "me"};
    vector<string> copied_to(copied_from);
    vector<string> moved_from{"move", "me"};
    vector<string> moved_to(move(moved_from));
  }
  vector<int> empty;
  vector<int> filled;
  vector<int> init;
  vector<string> copied_to;
  vector<string> moved_to;
};

// evaluate properties of default constructed vector
TEST_F(vector_test, default_constructor)
{
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.capacity(), 0);
}

// evaluate properties of fill constructed vector
TEST_F(vector_test, fill_constructor)
{
  EXPECT_FALSE(filled.empty());
  EXPECT_EQ(filled.size(), 5);
  EXPECT_GE(filled.capacity(), filled.size());
  for (auto it = filled.begin(); it != filled.end(); ++it)
  {
    EXPECT_EQ(*it, 1);
  }
}

TEST_F(vector_test, initializer_list_constructor)
{
  EXPECT_FALSE(initializer_list_constructed.empty());
  EXPECT_EQ(initializer_list_constructed.size(), 5);
  EXPECT_GE(initializer_list_constructed.capacity(), initializer_list_constructed.size());
  
}

int main()
{
  return RUN_ALL_TESTS();
}
