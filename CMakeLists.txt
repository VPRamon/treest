cmake_minimum_required(VERSION 3.10)
project(TreeLibrary)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/iterators
)

add_library(Tree INTERFACE)

target_include_directories(Tree INTERFACE ${PROJECT_SOURCE_DIR}/include)

install(DIRECTORY include/ DESTINATION include)

enable_testing()
add_subdirectory(tests)
