
project(CPSC223_HW1)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0")
set(CMAKE_BUILD_TYPE Debug)

# locate gtest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# create unit test executable
add_executable(hw1_test hw1_test.cpp simple_sorts.cpp)
target_link_libraries(hw1_test ${GTEST_LIBRARIES} pthread)

# create performance executable
add_executable(hw1_perf hw1_perf.cpp util.cpp simple_sorts.cpp)



