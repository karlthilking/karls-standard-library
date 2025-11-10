#include <iostream>
#include <chrono>
#include "karls_standard_library/vector.hpp"
#include "karls_standard_library/string.hpp"
#include "karls_standard_library/utility.hpp"
#include "karls_standard_library/memory.hpp"

using namespace karls_standard_library;

struct foo
{
  int x, y;
  foo(int x, int y) : x(x), y(y) {}
};

int main()
{
  unique_ptr<foo> pr = make_unique<foo>(0, 100);
  int number = (pr->x) + (pr->y);
  std::cout << number << "\n";
  return 0;
}