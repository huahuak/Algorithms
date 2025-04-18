cmake_minimum_required(VERSION 3.10.0)
project(algorithms_test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# google test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include(CTest)
enable_testing()

add_executable(algorithms_test 
    heap_test.cpp
)
add_compile_options("-g")

target_link_libraries(
    algorithms_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(algorithms_test)