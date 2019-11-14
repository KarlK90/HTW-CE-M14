cmake_minimum_required(VERSION 3.13)

project(RobotControl)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# CONFIG option is important so that CMake doesnt search for modules into the default modules directory
find_package(imgui CONFIG)
find_package(glfw CONFIG)
find_package(glew CONFIG)
find_package(gtest CONFIG)

# Dependencies
add_subdirectory(external/imgui-bindings)

# Libaries
add_subdirectory(src/RobotControlLib)
add_subdirectory(src/RobotSimulateLib)

# Application
add_subdirectory(apps/SoftwareUi)

# Unit Tests
enable_testing()
add_subdirectory(tests/RobotControlLibTest)
