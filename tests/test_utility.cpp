#include <iostream>
#include <type_traits>
#include <gtest/gtest.h>
#include "karls_standard_library/utility.hpp"

using namespace karls_standard_library;

class forward_test : public testing::Test
{
protected:
  class Object
  {
  public:
    static int constructions;
    static int copies;
    static int moves;
    static int destructions;
    int value;

    Object(int v) : value(v) { ++constructions; }

    Object(const Object& other) : value(other.value) { ++copies; }

    Object(Object&& other) : value(other.value) 
    {
      other.value = -1;
      ++moves;
    }

    ~Object() { ++destructions; }

    Object& operator=(const Object& other) = delete;
    Object& operator=(Object&& other) = delete;
  };
  void SetUp() override
  {
    Object::constructions = 0;
    Object::copies = 0;
    Object::moves = 0;
    Object::destructions = 0;
  }
};

int forward_test::Object::constructions = 0;
int forward_test::Object::copies = 0;
int forward_test::Object::moves = 0;
int forward_test::Object::destructions = 0;


