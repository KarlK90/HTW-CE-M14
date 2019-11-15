#pragma once

#include <deque>
#include <string>

// user interface
struct ui_in_struct {
    // direction pushbuttons on user interface
    volatile bool left;
    volatile bool right;
    volatile bool up;
    volatile bool down;
    volatile bool fwd;
    volatile bool back;
    volatile bool open;
    volatile bool close;

    // mode pushbuttons on user interface
    volatile bool mode1;
    volatile bool mode2;
};

struct ui_out_struct {
    // indication led on user interface
    bool op_led; // red led
    bool ready_led; // green led
    bool failure_led; // yellow led

    // 2-line text display
    std::string line1; // upper text line
    std::string line2; // lower text line
};

// interface to Robot hardware

struct robot_in_struct {
    // limit switches at axes
    // true indicated limit switch pressed
    /* volatile */ bool limit_left;
    /* volatile */ bool limit_down;
    /* volatile */ bool limit_back;
    /* volatile */ bool limit_close;

    // delta counters at axes
    // counters indicate the number of ticks since last cycle
    /* volatile */ int delta_left_right;
    /* volatile */ int delta_up_down;
    /* volatile */ int delta_fdw_back;
    /* volatile */ int delta_open_close;
};

struct robot_out_struct {
    // motor power commands
    // true forces to turn
    bool motor_left_right;
    bool motor_up_down;
    bool motor_fwd_back;
    bool motor_open_close;

    // motor direction commands
    // true sets turn direction as indicated; false sets opposite direction
    bool motor_dir_left;
    bool motor_dir_up;
    bool motor_dir_fwd;
    bool motor_dir_close;
};

extern bool is_running;

extern ui_in_struct ui_in;
extern ui_out_struct ui_out;
extern robot_in_struct robot_in;
extern robot_out_struct robot_out;

// control function that computes outputs as a function of inputs
void control();
bool reset();
