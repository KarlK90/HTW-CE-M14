#pragma once
#include "Axis.h"
#include "RobotControl.h"

class Robot {
    const std::int32_t limit_right = 9000;
    const std::int32_t limit_up = 9000;
    const std::int32_t limit_forward = 9000;
    const std::int32_t limit_open = 9000;

    Axis axis_left_right;
    Axis axis_up_down;
    Axis axis_fwd_back;
    Axis axis_open_close;

public:
    Robot(robot_in_struct& robot_in, robot_out_struct& robot_out)
        : axis_left_right { robot_out.motor_left_right, robot_out.motor_dir_left,
            robot_in.limit_left, robot_in.delta_left_right,
            limit_right }
        , axis_up_down { robot_out.motor_up_down, robot_out.motor_dir_up,
            robot_in.limit_down, robot_in.delta_up_down, limit_up }
        , axis_fwd_back { robot_out.motor_fwd_back, robot_out.motor_dir_fwd,
            robot_in.limit_back, robot_in.delta_fdw_back,
            limit_forward }
        , axis_open_close { robot_out.motor_open_close, robot_out.motor_dir_close,
            robot_in.limit_close, robot_in.delta_open_close,
            limit_open }
    {
    }
    bool reset();
    bool update();
    std::optional<std::string> go_left();
    std::optional<std::string> go_right();
    std::optional<std::string> open_hand();
    std::optional<std::string> close_hand();
    std::optional<std::string> go_up();
    std::optional<std::string> go_down();
    std::optional<std::string> go_forward();
    std::optional<std::string> go_back();
};
