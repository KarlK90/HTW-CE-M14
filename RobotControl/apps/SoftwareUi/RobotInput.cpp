#include "RobotControl.h"
#include "imgui.h"

using namespace std;

const std::uint16_t Key_W = 0x57;
const std::uint16_t Key_S = 0x53;
const std::uint16_t Key_A = 0x41;
const std::uint16_t Key_D = 0x44;
const std::uint16_t Key_1 = 0x31;
const std::uint16_t Key_2 = 0x32;

void process_input(const bool keys[512])
{
    ui_in.left = keys[ImGui::GetKeyIndex(ImGuiKey_LeftArrow)];
    ui_in.right = keys[ImGui::GetKeyIndex(ImGuiKey_RightArrow)];
    ui_in.up = keys[ImGui::GetKeyIndex(ImGuiKey_UpArrow)];
    ui_in.down = keys[ImGui::GetKeyIndex(ImGuiKey_DownArrow)];
    ui_in.fwd = keys[Key_W];
    ui_in.back = keys[Key_S];
    ui_in.open = keys[Key_A];
    ui_in.close = keys[Key_D];
    ui_in.mode1 = keys[Key_1];
    ui_in.mode2 = keys[Key_2];
}
