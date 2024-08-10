add_subdirectory(external/googletest)

add_executable(test_tree test_tree.cpp)

target_link_libraries(test_tree gtest_main Tree)

include(GoogleTest)
gtest_discover_tests(test_tree)
