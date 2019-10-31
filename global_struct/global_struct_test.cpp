#include "global_struct.h"
#include "test/catch.hpp"
#include "test/catch2/trompeloeil.hpp"
#include <exception>

// Fake Implementierung für Testzwecke
class Repository_Mock : public Repository {
public:
  MAKE_MOCK0(GetAxes, Axes &(), override);
};

TEST_CASE("Read_Axes_Global: Return Correct Ticks") {
  // --- Setup ---
  ::ROBOT_AXES.right_ticks = 10000;

  // --- Act ---
  std::int32_t result = Read_Axes_Global();

  // --- Assert ---
  REQUIRE(result == 10000);
}

TEST_CASE("Read_Axes: Return Correct Ticks") {
  // --- Setup ---
  // Designated initializers sind Teil des C++20 Standards
  Axes axes{.right_ticks = 10000,
            .left_ticks = 0,
            .right_button = 0,
            .left_button = 0};

  trompeloeil::sequence
      seq; // Ermöglicht die Aufrufreihenfolge mit IN_SEQUENCE zu testen

  Repository_Mock repo; // Konkretes Fake Repository

  // repo.GetAxes() liefert nun Referenz auf locales axes struct und nicht das
  // Globale ROBOT_AXES
  REQUIRE_CALL(repo, GetAxes()).IN_SEQUENCE(seq).LR_RETURN(axes);

  // --- Act ---
  std::int32_t result = Read_Axes(repo);

  // --- Assert ---
  REQUIRE(result == 10000);
}
