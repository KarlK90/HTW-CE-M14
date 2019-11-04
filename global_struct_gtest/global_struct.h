#pragma once
#include <cstdint>

struct Axes {
  std::int32_t left_ticks;
  std::uint8_t left_button;
  std::int32_t right_ticks;
  std::uint8_t right_button;
};

struct LightSensor {
  std::uint32_t level;
};

// Deklerationen
extern Axes ROBOT_AXES;
extern LightSensor LIGHT_SENSOR;

class Repository {
public:
  // Reale Implementierungen die im Programm genutzt werden
  virtual Axes &GetAxes() { return ::ROBOT_AXES; };
  virtual LightSensor &GetLightSensor() { return ::LIGHT_SENSOR; }
};

std::int32_t Read_Axes_Global();
std::int32_t Read_Axes(Repository &repo);