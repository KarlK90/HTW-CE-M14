#pragma once
#include "RobotControl.h"

class axis_class {
public:
    void perform_step(const bool motor_powered, const bool dir, bool& limit_switch, int& counter_inc);

private:
    int pos = 0;
};

class robot_class {
public:
    void perform_step(const robot_out_struct robot_out, robot_in_struct& robot_in);

private:
    axis_class left_right;
    axis_class up_down;
    axis_class fwd_back;
    axis_class open_close;
};

extern int step_size;

static robot_class robot;

void simulate_robot();
