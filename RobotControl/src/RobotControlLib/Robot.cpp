#include "Robot.h"

std::optional<std::string> Robot::go_left() {
  if (!axis_left_right.spin(true)) {
    return "Left limit reached!";
  }
  return {};
}
std::optional<std::string> Robot::go_right() {
  if (!axis_left_right.spin(false)) {
    return "Right limit reached!";
  }
  return {};
}

std::optional<std::string> Robot::go_up() {
  if (!axis_up_down.spin(true)) {
    return "Up limit reached!";
  }
  return {};
}

std::optional<std::string> Robot::go_down() {
  if (!axis_up_down.spin(false)) {
    return "Down limit reached!";
  }
  return {};
}

std::optional<std::string> Robot::open_hand() {
  if (!axis_open_close.spin(true)) {
    return "Open limit reached!";
  }
  return {};
}

std::optional<std::string> Robot::close_hand() {
  if (!axis_open_close.spin(false)) {
    return "Close limit reached!";
  }
  return {};
}

std::optional<std::string> Robot::go_forward() {
  if (!axis_fwd_back.spin(true)) {
    return "Forward limit reached!";
  }
  return {};
}

std::optional<std::string> Robot::go_back() {
  if (!axis_fwd_back.spin(false)) {
    return "Back limit reached!";
  }
  return {};
}

bool Robot::reset() {
  return axis_fwd_back.reset() && axis_left_right.reset() &&
         axis_open_close.reset() && axis_up_down.reset();
}
bool Robot::update() { return false; }
