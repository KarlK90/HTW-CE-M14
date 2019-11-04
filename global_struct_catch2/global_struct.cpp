#include "global_struct.h"

// Definitionen
Axes ROBOT_AXES;
LightSensor LIGHT_SENSOR;

// Direkter Zugriff auf ROBOT_AXES
std::int32_t Read_Axes_Global() { return ::ROBOT_AXES.right_ticks; }

// Indirektion über Repository
std::int32_t Read_Axes(Repository &repo) {
  return repo.GetAxes().right_ticks;
}
