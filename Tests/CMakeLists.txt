cmake_minimum_required(VERSION 3.14)
project(tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TEST_MODE_ON "Test mode on" ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE test_src 
  "Mock_Socket.h"
  "../Common/Protocol/*.cpp"
  "../Common/Protocol/*.h"
  "../Common/DTO/*.cpp"
  "../Common/DTO/*.h"
  "../Server/src/Protocol/*.cpp"
  "../Server/src/Protocol/*.h"
  "../Client/src/Protocol/*.cpp"
  "../Client/src/Protocol/*.h")

enable_testing()

add_executable(
  tests
  tests.cpp
  ${test_src}
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
