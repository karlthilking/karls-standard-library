add_executable(test_my_standard_library
    main.cpp
    test_memory.cpp
    test_vector.cpp
    test_string.cpp
    test_algorithms.cpp
    test_list.cpp
    test_utility.cpp
)

target_include_directories(test_my_standard_library PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(test_my_standard_library
    karls_standard_library
    gtest_main
)

gtest_discover_tests(test_my_standard_library)