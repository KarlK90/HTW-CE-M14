cmake_minimum_required(VERSION 3.13)

project(RobotControlLibTest)
include(GoogleTest)

# Add Valgrind to check for memory leaks while testing
find_program(MEMORYCHECK_COMMAND NAMES valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

set(SOURCES
        tests-main.cpp
        tests-control.cpp)

set(HEADERS
        )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Prevent GoogleTest from using PThreads
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

# Disable pthread support because mocked calls fail with segfault
# this is a known bug with cmake on ubuntu and we don't need the functionality.
add_definitions("-DGTEST_HAS_PTHREAD=0")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE RobotControlLib gtest::gtest)
gtest_discover_tests(${PROJECT_NAME})
