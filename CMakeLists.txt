cmake_minimum_required(VERSION 3.10)
project(TreeLibrary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_TESTS "Build tests for the project" ON)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include/tree/iterators
    ${PROJECT_SOURCE_DIR}/include/tree
    ${PROJECT_SOURCE_DIR}/include/graph
    ${PROJECT_SOURCE_DIR}/include/digraph
    ${PROJECT_SOURCE_DIR}/include/graph_impl
)

add_library(Tree INTERFACE)

include_directories(${INCLUDE_DIRS})
target_include_directories(Tree INTERFACE ${INCLUDE_DIRS})

install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
