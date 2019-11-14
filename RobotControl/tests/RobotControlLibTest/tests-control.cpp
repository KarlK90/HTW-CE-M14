#include "RobotControl.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

ui_in_struct ui_in;
ui_out_struct ui_out;
robot_in_struct robot_in;
robot_out_struct robot_out;

TEST(Control, ExampleTest)
{
    // Arrange
    ui_in.fwd = true;
    ui_in.back = true;

    // Act
    control();

    // Assert
    ASSERT_EQ(ui_out.line2, "forward and back pressed at same time! ");
}
