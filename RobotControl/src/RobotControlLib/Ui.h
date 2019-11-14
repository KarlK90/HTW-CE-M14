#pragma once

#include "RobotControl.h"
#include <deque>
#include <string>
#include <vector>

class Ui {
public:
  Ui(ui_in_struct &ui_in, ui_out_struct &ui_out)
      : ui_in{ui_in}, ui_out{ui_out} {}
  enum class operation_mode { Manual, Teach_in, Replay, Towers_of_Hanoi };
  enum class command {
    Up,
    Down,
    Left,
    Right,
    OpenHand,
    CloseHand,
    Forward,
    Back
  };

  std::pair<std::deque<Ui::command>, std::deque<std::string>> read_commands();

  void record_commands(const std::deque<Ui::command> &commands) {
    recorded_commands.push_back(commands);
  }

  const std::deque<std::deque<Ui::command>> &get_recorded_commands() {
    return recorded_commands;
  }

  operation_mode get_current_operation_mode();
  void update_user_ui(const std::deque<std::string> &);

private:
  ui_in_struct &ui_in;
  ui_out_struct &ui_out;
  operation_mode mode;
  std::deque<std::deque<Ui::command>> recorded_commands;
};

std::deque<std::string> execute_commands(std::deque<Ui::command> commands);