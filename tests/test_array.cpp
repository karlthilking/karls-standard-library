#include <gtest/gtest.h>
#include <compare>
#include "karls_standard_library/utility.hpp"
#include "karls_standard_library/array.hpp"
#include "karls_standard_library/string.hpp"

using namespace karls_standard_library;

class array_test : public testing::Test
{
protected:
  array_test() = default;
  ~array_test() = default;
};

TEST_F(array_test, default_constructor)
{
  array<int, 3> arr;
  EXPECT_EQ(arr.size(), 3);
  EXPECT_TRUE(!arr.empty());
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST_F(array_test, init_list_constructor)
{
  array<int, 3> arr{1, 2, 3};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr.back(), 3);
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST_F(array_test, fill_constructor)
{
  array<int, 5> arr(42);
  EXPECT_EQ(arr.size(), 5);
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.front(), arr.back());
  EXPECT_EQ(arr[3], 42);
  EXPECT_THROW(arr.at(10), std::out_of_range);
}

TEST_F(array_test, copy_constructor)
{
  array<int, 3> arr1{1, 2, 3};
  array<int, 3> arr2(arr1);
  EXPECT_EQ(arr1[0], arr2[0]);
  EXPECT_TRUE(arr1 == arr2);
  EXPECT_EQ(arr1.at(2), arr2.at(2));
  EXPECT_EQ(arr1.size(), arr2.size());
}

TEST_F(array_test, copy_assignment)
{
  array<int, 3> arr1{1, 2, 3};
  array<int, 3> arr2;
  arr2 = arr1;
  EXPECT_EQ(arr1[0], arr2[0]);
  EXPECT_TRUE(arr1 == arr2);
  EXPECT_EQ(arr1.back(), arr2.back());
  EXPECT_EQ(arr1.size(), arr2.size());
  EXPECT_TRUE(arr1 == arr2);
}

TEST_F(array_test, move_constructor)
{
  array<string, 3> arr1{"test1", "test2", "test3"};
  array<string, 3> arr2(move(arr1));
  EXPECT_EQ(arr2[0], "test1");
  EXPECT_TRUE(!arr2.empty());
  EXPECT_EQ(arr2.back(), "test3");
}

TEST_F(array_test, move_assignment)
{
  array<string, 2> arr1{"foo", "bar"};
  array<string, 2> arr2;
  arr2 = move(arr1);
  EXPECT_EQ(arr2[0], "foo");
  EXPECT_EQ(arr2.at(1), "bar");
  EXPECT_EQ(arr2.size(), 2);
}

TEST_F(array_test, iterators)
{
  array<int, 5> arr1{1, 1, 1, 1, 1};
  for (auto it = arr1.begin(); it!= arr1.end(); ++it)
  {
    EXPECT_EQ(*it, 1);
  }
  for (const int& x : arr1)
  {
    EXPECT_EQ(x, 1);
  }
}

TEST_F(array_test, fill_function)
{
  array<int, 4> arr1{2, 4, 8, 16};
  arr1.fill(1);
  for (const int& x : arr1) EXPECT_EQ(x, 1);
  arr1.fill(42);
  for (const int& x : arr1) EXPECT_EQ(x, 42);
}

TEST_F(array_test, swap_function)
{
  array<int, 3> original1{1, 2, 3};
  array<int, 3> original2{32, 64, 128};
  auto dummy1 = original1;
  auto dummy2 = original2;
  dummy1.swap(dummy2);
  EXPECT_TRUE(dummy1 == original2);
  EXPECT_TRUE(dummy2 == original1);
  swap(dummy1, dummy2);
  EXPECT_TRUE(dummy1 == original1);
  EXPECT_TRUE(dummy2 == original2);
}

TEST_F(array_test, comparisons)
{

}

TEST_F(array_test, to_array_function)
{

}