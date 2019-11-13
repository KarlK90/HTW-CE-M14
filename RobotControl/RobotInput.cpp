#include "RobotControl.h"
#include "imgui.h"

using namespace std;

void process_input(const bool keys[512])
{
    ui_in.left = keys[ImGui::GetKeyIndex(ImGuiKey_LeftArrow)];
    ui_in.right = keys[ImGui::GetKeyIndex(ImGuiKey_RightArrow)];
    ui_in.up = keys[ImGui::GetKeyIndex(ImGuiKey_UpArrow)];
    ui_in.down = keys[ImGui::GetKeyIndex(ImGuiKey_DownArrow)];
    ui_in.fwd = keys[ImGui::GetKeyIndex(ImGuiKey_X)];
    ui_in.back = keys[ImGui::GetKeyIndex(ImGuiKey_Y)];
    ui_in.open = keys[ImGui::GetKeyIndex(ImGuiKey_V)];
    ui_in.close = keys[ImGui::GetKeyIndex(ImGuiKey_C)];
    ui_in.mode1 = keys[ImGui::GetKeyIndex(ImGuiKey_Backspace)];
    ui_in.mode2 = keys[ImGui::GetKeyIndex(ImGuiKey_Space)];
}
