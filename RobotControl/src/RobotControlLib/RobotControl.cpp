#include "RobotControl.h"
#include "Robot.h"
#include "Ui.h"

static Robot robot { robot_in, robot_out };
static Ui ui { ui_in, ui_out };

void control()
{
    auto mode = ui.get_current_operation_mode();
    if (mode == Ui::operation_mode::Manual) {
        auto cmds_err = ui.read_commands();
        auto exec_err = execute_commands(cmds_err.first);
        auto errs = std::deque<std::string>();
        for (const auto& err : cmds_err.second) {
            errs.emplace_back(err);
        }
        for (const auto& err : exec_err) {
            errs.emplace_back(err);
        }
        ui.update_user_ui(errs);
    } else if (mode == Ui::operation_mode::Teach_in) {
        auto cmds_err = ui.read_commands();
        ui.record_commands(cmds_err.first);
        execute_commands(cmds_err.first);
        ui.update_user_ui(cmds_err.second);
    } else if (mode == Ui::operation_mode::Replay) {
        //auto err = replay_commands(ui.get_recorded_commands());
        //ui.update_user_ui(err);
    } else if (mode == Ui::operation_mode::Towers_of_Hanoi) {
        //play_towers_of_hanoi();
    }
}

std::deque<std::string> execute_commands(std::deque<Ui::command> commands)
{
    std::deque<std::string> errors;
    auto handle_error_case = [&](std::optional<std::string> result) {
        if (result) {
            errors.push_back(result.value());
        }
    };

    while (!commands.empty()) {
        switch (commands.front()) {
        case Ui::command::Up:
            handle_error_case(robot.go_up());
            break;
        case Ui::command::Down:
            handle_error_case(robot.go_down());
            break;
        case Ui::command::Left:
            handle_error_case(robot.go_left());
            break;
        case Ui::command::Right:
            handle_error_case(robot.go_right());
            break;
        case Ui::command::OpenHand:
            handle_error_case(robot.open_hand());
            break;
        case Ui::command::CloseHand:
            handle_error_case(robot.close_hand());
            break;
        case Ui::command::Forward:
            handle_error_case(robot.go_forward());
            break;
        case Ui::command::Back:
            handle_error_case(robot.go_back());
            break;
        }
        commands.pop_front();
    }
    return errors;
}

bool reset() { return robot.reset(); }
