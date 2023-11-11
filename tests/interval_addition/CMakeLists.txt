project(IntervalAddition-Test)

add_executable(IntervalAddition-Test main.cpp)

target_link_libraries(IntervalAddition-Test PRIVATE GTest::gtest GTest::gtest_main)