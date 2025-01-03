
#include <gtest/gtest.h>

#include <BoardTable.hpp>
#include <ConstVariables.hpp>
#include <PositionValidator.hpp>

struct PositionValidatorFixture : ::testing::Test {
  BoardTable boardTable;
  PositionValidator positionValidator{boardTable.board()};
};

TEST_F(PositionValidatorFixture, TestingValidInput) {
  // Input is 1, which represents first cell
  auto valResult = positionValidator.validate(1);

  EXPECT_EQ(valResult.gameStatus, GameStatus::Continue);
  EXPECT_FALSE(valResult.errorMessage);
}

TEST_F(PositionValidatorFixture, TestingInputForManuallyEndingTheGame) {
  auto valResult = positionValidator.validate(TTT::END_GAME_POSITION);

  EXPECT_EQ(valResult.gameStatus, GameStatus::End);
  EXPECT_TRUE(valResult.errorMessage);
  EXPECT_EQ(valResult.errorMessage.value(),
            std::string{"Thanks for playing. Bye bye ^^"});
}

TEST_F(PositionValidatorFixture, TestingInvalidInput) {
  // Total number of cells is ROW * COL, so we increase the total number of
  // cells by one
  int input = TTT::ROW * TTT::COL + 1;

  // Input is out of scope, which is invalid
  auto valResult = positionValidator.validate(input);

  EXPECT_EQ(valResult.gameStatus, GameStatus::RepeatMove);
  EXPECT_TRUE(valResult.errorMessage);
  EXPECT_EQ(valResult.errorMessage.value(),
            std::string{"Position is out of scope. Please, try again."});
}

TEST_F(PositionValidatorFixture, TestingValidCoordinates) {
  auto valResult = positionValidator.validate(0, 0, 'X');

  EXPECT_EQ(valResult.gameStatus, GameStatus::Continue);
  EXPECT_FALSE(valResult.errorMessage);
}

TEST_F(PositionValidatorFixture, TestingDuplicateCoordinates) {
  // Inserting value in the first cell
  boardTable.insert(0, 0, 'X');

  // Validating already populated first cell
  auto valResult = positionValidator.validate(0, 0, 'X');

  EXPECT_EQ(valResult.gameStatus, GameStatus::RepeatMove);
  EXPECT_TRUE(valResult.errorMessage);
  EXPECT_EQ(valResult.errorMessage.value(),
            std::string{"Field is already populated. Please try again."});
}
