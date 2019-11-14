PROJECT("RobotSoftwareUI")

set(SOURCES
        RobotMain.cpp
        RobotInput.cpp
        RobotOutput.cpp
        )

set(HEADERS
        RobotInput.h
        RobotOutput.h
        )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(${PROJECT_NAME} RobotControlLib RobotSimulateLib ImGuiBindings imgui::imgui glfw::glfw glew::glew)