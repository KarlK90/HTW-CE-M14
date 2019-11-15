#pragma once
#include <cinttypes>
#include <optional>
#include <string>

class Axis {
public:
    Axis(bool& power_motor, bool& direction_motor, bool& limit_switch,
        std::int32_t& counter_delta, const std::int32_t limit)
        : external_power_motor { power_motor }
        , external_direction_motor { direction_motor }
        , external_limit_switch { limit_switch }
        , external_counter_delta { counter_delta }
        , position_limit { limit }
    {
    }
    bool spin(bool direction);
    bool reset();
    void update();

private:
    std::int32_t position = 0;
    bool& external_power_motor;
    bool& external_direction_motor;
    bool& external_limit_switch;
    std::int32_t& external_counter_delta;
    const std::int32_t position_limit;
    bool internal_direction_motor;
    bool internal_power_motor;
};
