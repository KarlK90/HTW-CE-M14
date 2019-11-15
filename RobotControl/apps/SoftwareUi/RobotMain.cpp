// dear imgui-bindings: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui-bindings, see examples/README.txt and documentation at the top of imgui-bindings.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

// clang-format off
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
// clang-format on
#include <cstdio>

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h> // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h> // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h> // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include "RobotControl.h"
#include "RobotInput.h"
#include "RobotOutput.h"
#include "RobotSimulate.h"

ui_in_struct ui_in;
ui_out_struct ui_out;
robot_in_struct robot_in;
robot_out_struct robot_out;

bool is_running = true;

void render_ui();
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

        // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "CE M14 Roboter Simulator", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    //reset();
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("CE M14 Roboter Simulation v.Funky Shit"); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        process_input(io.KeysDown);

        if (is_running) {
            control();
            process_output();
            render_ui();
            if (step_size > 0) {
                simulate_robot();
                step_size = 0;
            }
        }
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void render_ui()
{
    auto colored_text_by_flag = [](const char* fmt, bool flag) {
        if (flag) {
            ImGui::TextColored(ImColor(0.0f, 1.0f, 0.0f, 1.0f), "%s", fmt);
        } else {
            ImGui::TextDisabled("%s", fmt);
        }
    };

    if (ImGui::CollapsingHeader("User Input", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2);
        colored_text_by_flag("Left", ui_in.left);
        ImGui::NextColumn();
        colored_text_by_flag("Right", ui_in.right);
        ImGui::NextColumn();
        colored_text_by_flag("Up", ui_in.up);
        ImGui::NextColumn();
        colored_text_by_flag("Down", ui_in.down);
        ImGui::NextColumn();
        colored_text_by_flag("Forward", ui_in.fwd);
        ImGui::NextColumn();
        colored_text_by_flag("Back", ui_in.back);
        ImGui::NextColumn();
        colored_text_by_flag("Open", ui_in.open);
        ImGui::NextColumn();
        colored_text_by_flag("Close", ui_in.close);
        ImGui::NextColumn();
        colored_text_by_flag("Mode 1", ui_in.mode1);
        ImGui::NextColumn();
        colored_text_by_flag("Mode 2", ui_in.mode2);
        ImGui::Columns(1);
    }

    if (ImGui::CollapsingHeader("User Output", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::TreeNodeEx("Status Display", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("%s", ui_out.line1.c_str());
            ImGui::TextColored(ImColor(1.0f, 0.0f, 0.0f, 1.0f), "%s", ui_out.line2.c_str());
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Status Leds", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Columns(3);
            colored_text_by_flag("Ready", ui_out.op_led);
            ImGui::NextColumn();
            colored_text_by_flag("Failure", ui_out.failure_led);
            ImGui::NextColumn();
            colored_text_by_flag("Operating", ui_out.ready_led);
            ImGui::Columns(1);
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Robot Input", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::TreeNodeEx("Deltas", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Columns(4);
            ImGui::Text("Left-Right");
            ImGui::NextColumn();
            ImGui::Text("%i", robot_in.delta_left_right);
            ImGui::NextColumn();
            ImGui::Text("Up-Down");
            ImGui::NextColumn();
            ImGui::Text("%i", robot_in.delta_up_down);
            ImGui::NextColumn();
            ImGui::Text("Forward-Back");
            ImGui::NextColumn();
            ImGui::Text("%i", robot_in.delta_fdw_back);
            ImGui::NextColumn();
            ImGui::Text("Open-Close");
            ImGui::NextColumn();
            ImGui::Text("%i", robot_in.delta_open_close);
            ImGui::Columns(1);
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Limit Switches", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Columns(4);
            colored_text_by_flag("Left", robot_in.limit_left);
            ImGui::NextColumn();
            colored_text_by_flag("Down", robot_in.limit_down);
            ImGui::NextColumn();
            colored_text_by_flag("Back", robot_in.limit_back);
            ImGui::NextColumn();
            colored_text_by_flag("Close", robot_in.limit_close);
            ImGui::Columns(1);
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Robot Output", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2);
        colored_text_by_flag("Direction Left", robot_out.motor_dir_left);
        ImGui::NextColumn();
        colored_text_by_flag("Power Left-Right", robot_out.motor_left_right);
        ImGui::NextColumn();
        colored_text_by_flag("Direction Up", robot_out.motor_dir_up);
        ImGui::NextColumn();
        colored_text_by_flag("Power Up-Down", robot_out.motor_up_down);
        ImGui::NextColumn();
        colored_text_by_flag("Direction Forward", robot_out.motor_dir_fwd);
        ImGui::NextColumn();
        colored_text_by_flag("Power Forward-Back", robot_out.motor_fwd_back);
        ImGui::NextColumn();
        colored_text_by_flag("Direction Close", robot_out.motor_dir_close);
        ImGui::NextColumn();
        colored_text_by_flag("Power Open-Close", robot_out.motor_open_close);
        ImGui::Columns(1);
    }
}