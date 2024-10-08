add_subdirectory(external/googletest)

file(GLOB_RECURSE UNTI_TEST_SOURCES
    lightweight_graph/test_*.cpp
    #digraph/test_*.cpp
    #test_*.cpp
)


add_executable(test_tree ${UNTI_TEST_SOURCES})

target_link_libraries(test_tree gtest_main Tree)

include(GoogleTest)
gtest_discover_tests(test_tree TEST_PREFIX "test_")
