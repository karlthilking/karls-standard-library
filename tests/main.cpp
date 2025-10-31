#include <iostream>

void test_memory();
void test_vector();
void test_list();
void test_algorithms();

int main() {
  std::cout << "Running tests" << "\n\n";
  try {
    // test memory management library
    std::cout << "Testing memory...\n";
    test_memory();
    std::cout << "Memory tests passed...\n\n";

    // test vector
    std::cout << "Testing vector...\n";
    test_vector();
    std::cout << "Vector tests passed...\n\n";

    // test list (linked list)
    std::cout << "Testing list...\n";
    test_list();
    std::cout << "List tests passed.\n\n";

    // test algorithms library
    std::cout << "Testing algorithms...\n";
    test_algorithms();
    std::cout << "Algorithms tests passed.\n\n";
  }
  except (const std::exception& e) {
    std::cerr << "Tests failed: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
