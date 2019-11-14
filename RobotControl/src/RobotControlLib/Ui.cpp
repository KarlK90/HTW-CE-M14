#include "Ui.h"

Ui::operation_mode Ui::get_current_operation_mode() {
  if (!ui_in.mode1 && !ui_in.mode2) {
    mode = operation_mode::Manual;
  }

  if (!ui_in.mode1 && ui_in.mode2) {
    mode = operation_mode::Teach_in;
  }

  if (ui_in.mode1 && !ui_in.mode2) {
    mode = operation_mode::Replay;
  }

  if (ui_in.mode1 && ui_in.mode2) {
    mode = operation_mode::Towers_of_Hanoi;
  }

  return mode;
}

std::pair<std::deque<Ui::command>, std::deque<std::string>>
Ui::read_commands() {
  std::deque<std::string> errors;

  std::deque<command> commands;
  auto add_mutually_exclusive_cmd = [&](bool cmd_1, Ui::command cmd_1_ui,
                                        bool cmd_2, Ui::command cmd_2_ui,
                                        const std::string &error) {
    if (cmd_1 && cmd_2) {
      errors.emplace_back(error);
    } else {
      if (cmd_1) {
        commands.push_back(cmd_1_ui);
      }
      if (cmd_2) {
        commands.push_back(cmd_2_ui);
      }
    }
  };

  add_mutually_exclusive_cmd(ui_in.left, command::Left, ui_in.right,
                             command::Right,
                             "left and right pressed at same time!");

  add_mutually_exclusive_cmd(ui_in.up, command::Up, ui_in.down, command::Down,
                             "up and down pressed at same time!");

  add_mutually_exclusive_cmd(ui_in.close, command::CloseHand, ui_in.open,
                             command::OpenHand,
                             "open and close pressed at same time!");

  add_mutually_exclusive_cmd(ui_in.fwd, command::Forward, ui_in.back,
                             command::Back,
                             "forward and back pressed at same time!");
  return std::make_pair(commands, errors);
}

void Ui::update_user_ui(const std::deque<std::string>& errors) {
  std::string error;
  for (const auto &err : errors) {
    error.append(err);
    error.push_back(' ');
  }

  switch (mode) {
  case operation_mode::Manual:
    ui_out.line1 = "Manual";
    break;
  case operation_mode::Teach_in:
    ui_out.line1 = "Teach-in";
    break;
  case operation_mode::Replay:
    ui_out.line1 = "Replay";
    break;
  case operation_mode::Towers_of_Hanoi:
    ui_out.line1 = "Towers of Hanoi";
    break;
  }

  ui_out.line2 = error;
}

