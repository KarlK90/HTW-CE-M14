cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

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

set(ROBOT_UI_SOURCES
        RobotMain.cpp
        bindings/imgui_impl_glfw.cpp
        bindings/imgui_impl_opengl3.cpp
        RobotControl.cpp
        RobotInput.cpp
        RobotOutput.cpp
        RobotSimulate.cpp
        Axis.cpp
        Robot.cpp
        Ui.cpp
        )

set(ROBOT_UI_HEADERS
        bindings/imgui_impl_glfw.h
        bindings/imgui_impl_opengl3.h
        Axis.h
        Robot.h
        Ui.h
        )

add_executable(RobotUi ${ROBOT_UI_SOURCES} ${ROBOT_UI_HEADERS})

target_compile_definitions(RobotUi PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(RobotUi imgui::imgui glfw::glfw glew::glew)