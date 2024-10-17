 cmake_minimum_required(VERSION 3.10)
 project(MyProject)
  
 find_package(GTest REQUIRED)
 include_directories(${GTEST_INCLUDE_DIRS})
  
 add_executable(runTests example_test.cpp)
 target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
