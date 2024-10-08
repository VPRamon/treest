cmake_minimum_required(VERSION 3.10)
project(TreeLibrary)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_TESTS "Build tests for the project" ON)

set(INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include/graph
    ${PROJECT_SOURCE_DIR}/include/graph/lightweight
    ${PROJECT_SOURCE_DIR}/include/lightweight_digraph
    ${PROJECT_SOURCE_DIR}/include/tree
    ${PROJECT_SOURCE_DIR}/include/tree/lightweight
    ${PROJECT_SOURCE_DIR}/include/tree/smart
    ${PROJECT_SOURCE_DIR}/include/tree/iterators
)

add_library(Tree INTERFACE)

include_directories(${INCLUDE_DIRS})
target_include_directories(Tree INTERFACE ${INCLUDE_DIRS})

install(DIRECTORY include/ DESTINATION include)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
