#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>
#include "karls_standard_library/utility.hpp"
#include "karls_standard_library/vector.hpp"
#include "karls_standard_library/string.hpp"

using namespace karls_standard_library;
/*
class vector_test : public testing::Test 
{
protected:
  vector<int> empty;
  vector<int> filled = vector<int>(5, 1);
  vector<int> init{1, 2, 3, 4, 5};

  void SetUp() override
  {

  }
};

// evaluate default constructed vector
TEST_F(vector_test, default_constructor)
{
  EXPECT_TRUE(empty.empty());
  EXPECT_EQ(empty.size(), 0);
  EXPECT_EQ(empty.capacity(), 0);
}

// evaluate fill constructed vector
TEST_F(vector_test, fill_constructor)
{
  EXPECT_TRUE(!filled.empty());
  EXPECT_EQ(filled.size(), 5);
  EXPECT_GE(filled.capacity(), filled.size());
}

// evaluate initializer list constructor
TEST_F(vector_test, initializer_list_constructor)
{
  EXPECT_TRUE(!init.empty());
  EXPECT_EQ(init.size(), 5);
  EXPECT_GE(init.capacity(), init.size());
}

TEST_F(vector_test, copy_constructor)
{
  vector<string> temp{"copy", "me"};
  vector<string> copied_to(temp);
}

TEST_F(vector_test, move_constructor)
{
  vector<string> temp{"move", "me"};
  vector<string> moved_to(temp);
}

TEST_F(vector_test, copy_assignment)
{
  vector<string> temp{"copy", "me"};
  vector<string> copied_to;
  copied_to = temp;
}

TEST_F(vector_test, move_assignment)
{

}
*/