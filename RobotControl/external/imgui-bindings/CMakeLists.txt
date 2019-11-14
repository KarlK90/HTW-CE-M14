PROJECT(ImGuiBindings)

set(SOURCES
        imgui_impl_glfw.cpp
        imgui_impl_opengl3.cpp
        )

set(HEADERS
        imgui_impl_glfw.h
        imgui_impl_opengl3.h
        )

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Make sure the compiler can find include files for our library
# when other libraries or executables link to it
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} imgui::imgui glfw::glfw glew::glew)