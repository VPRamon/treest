file(GLOB_RECURSE UNTI_TEST_SOURCES
    #lightweight_graph/test_*.cpp
    #lightweight_digraph/test_*.cpp
    #lightweight_tree/test_*.cpp
    smart_tree/test_*.cpp
)

add_executable(test_cpp11 ${UNTI_TEST_SOURCES})

target_link_libraries(test_cpp11 gtest_main Tree)
set_target_properties(test_cpp11 PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES)
gtest_discover_tests(test_cpp11 TEST_PREFIX "test_")
