#include "RobotControl.h"
#include "RobotSimulate.h"

// step_size defines how many steps the motor turns in one cycle
int step_size = 0;

// 2*16 Zeilen Display

// for each axis, the control commands (1st two parameters) are used 
// to compute the movement of the axis and the status of the limit switch (2nd two parameters)
void axis_class::perform_step(const bool motor_powered, const bool dir, bool& limit_switch, int& counter_inc)
{
	// if motor is power_motor then go one step foward or back
	counter_inc = motor_powered ? step_size : 0;
	pos = dir ? pos + counter_inc : pos - counter_inc;

	// if limit switch is reached then set position to zero and limit switch to true
	if (pos < 0) pos = 0;
	limit_switch = (pos == 0);
}


void robot_class::perform_step(const robot_out_struct robot_out, robot_in_struct& robot_in)
{
	left_right.perform_step(robot_out.motor_left_right, robot_out.motor_dir_left, robot_in.limit_left, robot_in.delta_left_right);
	up_down.perform_step(robot_out.motor_up_down, robot_out.motor_dir_up, robot_in.limit_down, robot_in.delta_up_down);
	fwd_back.perform_step(robot_out.motor_fwd_back, robot_out.motor_dir_fwd, robot_in.limit_back, robot_in.delta_fdw_back);
	open_close.perform_step(robot_out.motor_open_close, robot_out.motor_dir_close, robot_in.limit_close, robot_in.delta_open_close);
}

void simulate_robot()
{
	// simulate Robot movement
	// tbd
        robot.perform_step(robot_out, robot_in);

}