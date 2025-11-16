cmake_minimum_required(VERSION 3.10)
project(FigureProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

include_directories(include)

set(SOURCES
    src/dot2D.cpp
    src/coordinates_vector.cpp
    src/figure.cpp
    src/trapezoid.cpp
    src/rhombus.cpp
    src/pentagon.cpp
    src/figure_vector.cpp
)

set(TEST_SOURCES
    tests/tests.cpp
)

add_library(FigureLib ${SOURCES})

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(
    run_tests
    FigureLib
    gtest_main
    gmock
    pthread
)

enable_testing()
add_test(NAME FigureTests COMMAND run_tests)