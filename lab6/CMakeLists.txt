cmake_minimum_required(VERSION 3.10)
project(GameProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main
    src/dragon.cpp
    src/factory.cpp
    src/knight_errant.cpp
    src/main.cpp
    src/npc.cpp
    src/observer.cpp
    src/princess.cpp
    src/visitor.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/test_main.cpp
    tests/test_npc.cpp
    tests/test_factory.cpp
    tests/test_visitor.cpp
    tests/test_observer.cpp

    src/dragon.cpp
    src/factory.cpp
    src/knight_errant.cpp
    src/npc.cpp
    src/observer.cpp
    src/princess.cpp
    src/visitor.cpp
)

target_include_directories(tests PRIVATE include)
target_link_libraries(tests PRIVATE gtest_main)