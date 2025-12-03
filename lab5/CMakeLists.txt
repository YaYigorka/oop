cmake_minimum_required(VERSION 3.16)
project(CustomAllocatorList)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(allocator_tests
    tests/allocator_tests.cpp
)

target_include_directories(allocator_tests PRIVATE include inline)
target_link_libraries(allocator_tests
    GTest::gtest
    GTest::gtest_main
)

add_executable(main
    src/main.cpp
)
target_include_directories(main PRIVATE include inline)

include(GoogleTest)
gtest_discover_tests(allocator_tests)