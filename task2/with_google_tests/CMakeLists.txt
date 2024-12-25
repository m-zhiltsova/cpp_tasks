cmake_minimum_required(VERSION 3.10)
project(Universe)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Universe main.cpp Universe.cpp Universe.h)

add_executable(runTests test.cpp Universe.cpp Universe.h)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

enable_testing()

add_test(NAME UniverseTest COMMAND runTests)

