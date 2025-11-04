add_executable(test_my_standard_library
        main.cpp
        test_memory.cpp
        test_vector.cpp
        test_algorithms.cpp
        test_list.cpp
        test_utility.cpp
)

target_link_libraries(test_my_standard_library karls_standard_library)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark karls_standard_library)