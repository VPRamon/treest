file(GLOB_RECURSE UNTI_TEST_SOURCES
    lightweight_graph/test_*.cpp
    lightweight_digraph/test_*.cpp
    lightweight_tree/test_*.cpp
    smart_tree/test_*.cpp
)

add_executable(test_cpp17 ${UNTI_TEST_SOURCES})

target_link_libraries(test_cpp17 gtest_main Tree)

set_target_properties(test_cpp17 PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
gtest_discover_tests(test_cpp17 TEST_PREFIX "test_")

