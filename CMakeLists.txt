cmake_minimum_required(VERSION 3.14)
project(FirstLab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(main src/main.cpp src/removingVowels.cpp)

add_executable(run_test tests/test.cpp src/removingVowels.cpp)

target_link_libraries(run_test GTest::gtest_main)

target_include_directories(run_test PRIVATE src)