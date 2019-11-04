#include "global_struct.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <exception>

using ::testing::ReturnRef;

int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

// Fake Implementierung für Testzwecke
class Repository_Mock : public Repository {
public:
  MOCK_METHOD(Axes &, GetAxes, (), (override));
};

TEST(Read_Axes_Global, Return_Correct_Ticks) {
  // --- Setup ---
  ::ROBOT_AXES.right_ticks = 10000;

  // --- Act ---
  std::int32_t result = Read_Axes_Global();

  // --- Assert ---
  EXPECT_EQ(result, 10000);
}

TEST(Read_Axes, Return_Correct_Ticks) {
  // --- Setup ---
  // Designated initializers sind Teil des C++20 Standards
  Axes axes{.right_ticks = 10000,
            .left_ticks = 0,
            .right_button = 0,
            .left_button = 0};

  testing::Sequence
      seq; // Ermöglicht die Aufrufreihenfolge mit InSequence zu testen

  Repository_Mock repo; // Konkretes Fake Repository

  // repo.GetAxes() liefert nun Referenz auf locales axes struct und nicht das
  // Globale ROBOT_AXES
  EXPECT_CALL(repo, GetAxes()).InSequence(seq).WillOnce(ReturnRef(axes));

  // --- Act ---
  std::int32_t result = Read_Axes(repo);

  // --- Assert ---
  EXPECT_EQ(result, 10000);
}
