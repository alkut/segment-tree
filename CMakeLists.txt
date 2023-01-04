cmake_minimum_required(VERSION 3.24)
project(segment_tree)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(segment_tree
        main.cpp segment_tree.hpp stupid.hpp)

target_link_libraries(segment_tree ${GTEST_LIBRARIES} pthread)
