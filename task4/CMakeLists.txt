cmake_minimum_required(VERSION 3.10)
project(CSVParser)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(CSVParser main.cpp CSVParser.h)

add_executable(runTests test.cpp CSVParser.h)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

enable_testing()

add_test(NAME CSVParserTest COMMAND runTests)

