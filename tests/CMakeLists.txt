add_executable(test_mystl
        main.cpp
        test_memory.cpp
        test_vector.cpp
        test_algorithms.cpp
        test_list.cpp
        test_utility.cpp
)

target_link_libraries(test_mystl karls_stl)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark karls_stl)