#include "RobotControl.h"
#include "imgui.h"
#include <iostream>

using namespace std;


void process_output()
{

    if (ImGui::CollapsingHeader("User Input", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2);
        ImGui::Checkbox("Left", (bool*)&ui_in.left);
        ImGui::NextColumn();
        ImGui::Checkbox("Right", (bool*)&ui_in.right);
        ImGui::NextColumn();
        ImGui::Checkbox("Up", (bool*)&ui_in.up);
        ImGui::NextColumn();
        ImGui::Checkbox("Down", (bool*)&ui_in.down);
        ImGui::NextColumn();
        ImGui::Checkbox("Forward", (bool*)&ui_in.fwd);
        ImGui::NextColumn();
        ImGui::Checkbox("Back", (bool*)&ui_in.back);
        ImGui::NextColumn();
        ImGui::Checkbox("Open", (bool*)&ui_in.open);
        ImGui::NextColumn();
        ImGui::Checkbox("Close", (bool*)&ui_in.close);
        ImGui::NextColumn();
        ImGui::Checkbox("Mode 1", (bool*)&ui_in.mode1);
        ImGui::NextColumn();
        ImGui::Checkbox("Mode 2", (bool*)&ui_in.mode2);
        ImGui::Columns(1);
    }

    if (ImGui::CollapsingHeader("User Output", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::TreeNodeEx("Status Display", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Text("%s", ui_out.line1.c_str());
            ImGui::Text("%s", ui_out.line2.c_str());
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Status Leds", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Columns(3);
            ImGui::Checkbox("Ready", (bool*)&ui_out.op_led);
            ImGui::NextColumn();
            ImGui::Checkbox("Failure", (bool*)&ui_out.failure_led);
            ImGui::NextColumn();
            ImGui::Checkbox("Operating", (bool*)&ui_out.ready_led);
            ImGui::Columns(1);
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Robot Input"), ImGuiTreeNodeFlags_DefaultOpen) {
        if (ImGui::TreeNodeEx("Deltas", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Columns(2);
            ImGui::InputInt("Left-Right", &robot_in.delta_left_right);
            ImGui::NextColumn();
            ImGui::InputInt("Up-Down", &robot_in.delta_up_down);
            ImGui::NextColumn();
            ImGui::InputInt("Forward-Back", &robot_in.delta_fdw_back);
            ImGui::NextColumn();
            ImGui::InputInt("Open-Close", &robot_in.delta_open_close);
            ImGui::Columns(1);
            ImGui::TreePop();
        }
        if (ImGui::TreeNodeEx("Limit Switches", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Columns(4);
            ImGui::Checkbox("Left", (bool*)&robot_in.limit_left);
            ImGui::NextColumn();
            ImGui::Checkbox("Down", (bool*)&robot_in.limit_down);
            ImGui::NextColumn();
            ImGui::Checkbox("Back", (bool*)&robot_in.limit_back);
            ImGui::NextColumn();
            ImGui::Checkbox("Close", (bool*)&robot_in.limit_close);
            ImGui::Columns(1);
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Robot Output", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2);
        ImGui::Checkbox("Direction Left", (bool*)&robot_out.motor_dir_left);
        ImGui::NextColumn();
        ImGui::Checkbox("Power Left-Right", (bool*)&robot_out.motor_left_right);
        ImGui::NextColumn();
        ImGui::Checkbox("Direction Up", (bool*)&robot_out.motor_dir_up);
        ImGui::NextColumn();
        ImGui::Checkbox("Power Up-Down", (bool*)&robot_out.motor_up_down);
        ImGui::NextColumn();
        ImGui::Checkbox("Direction Forward", (bool*)&robot_out.motor_dir_fwd);
        ImGui::NextColumn();
        ImGui::Checkbox("Power Forward-Back", (bool*)&robot_out.motor_fwd_back);
        ImGui::NextColumn();
        ImGui::Checkbox("Direction Close", (bool*)&robot_out.motor_dir_close);
        ImGui::NextColumn();
        ImGui::Checkbox("Power Open-Close", (bool*)&robot_out.motor_open_close);
        ImGui::Columns(1);
    }
}
