cmake_minimum_required(VERSION 3.24)
project(segment_tree)

set(CMAKE_CXX_STANDARD 14)

add_executable(segment_tree
        main.cpp segment_tree.hpp stupid.hpp)
