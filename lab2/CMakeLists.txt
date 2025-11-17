cmake_minimum_required(VERSION 3.10)
project(SecondLab)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Автоматическая загрузка и сборка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

set(SOURCES
    src/DynamicArray.cpp
    src/Eleven.cpp
    src/MyErrors.cpp
)

set(TEST_SOURCES
    tests/tests.cpp
)

add_library(ElevenLib ${SOURCES})
add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(
    run_tests
    ElevenLib
    gtest_main
    gmock
    pthread
)