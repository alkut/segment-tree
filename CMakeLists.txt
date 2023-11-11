cmake_minimum_required(VERSION 3.28)
project(segment_tree)

set(CMAKE_CXX_STANDARD 23)

include(cmake/Environment.cmake)
include(cmake/FindGTest.cmake)

add_subdirectory(examples)
add_subdirectory(tests)
