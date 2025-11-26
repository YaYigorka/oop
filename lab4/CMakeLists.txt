cmake_minimum_required(VERSION 3.16)
project(WorkFourProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(figures_main src/main.cpp)
target_include_directories(figures_main PRIVATE include inline)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(googletest)

add_executable(figures_tests
    tests/test_point.cpp
    tests/test_array.cpp
    tests/test_triangle.cpp
    tests/test_square.cpp
    tests/test_rectangle.cpp
)
target_include_directories(figures_tests PRIVATE include inline)
target_link_libraries(figures_tests GTest::gtest GTest::gtest_main)