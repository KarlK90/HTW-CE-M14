#include "Axis.h"

bool Axis::reset()
{
    if (external_limit_switch) {
        position = 0;
        return true;
    }

    external_power_motor = true;
    external_direction_motor = true;
    return false;
}

void Axis::update()
{
    position = internal_direction_motor ? position + external_counter_delta : position - external_counter_delta;
}

bool Axis::spin(bool direction)
{
    if (position < 0 || position > position_limit) {
        external_power_motor = false;
        return false;
    }

    external_power_motor = true;
    external_direction_motor = direction;
    return true;
}
