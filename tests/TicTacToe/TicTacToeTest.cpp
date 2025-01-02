#include <gtest/gtest.h>

#include <ConstVariables.hpp>
#include <TicTacToe.hpp>

struct TicTacToeFixture : ::testing::Test, TicTacToe {
  int setNewPosition;

 private:
  int newPosition() const override { return setNewPosition; }
};

// NOTE: Ensuring that test requirements are met. However, application does not
// require these values. This is only for testing purposes. In case ROW/COL are
// set to other values these tests will not be valid any more.
TEST_F(TicTacToeFixture, ExpectThatConsVariablesAreProperlyDefined) {
  EXPECT_EQ(TTT::ROW, 3);
  EXPECT_EQ(TTT::COL, 3);
}

// Testing calculation of coordinates

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom1) {
  auto [row, col] = calculateCoordinates(1);
  EXPECT_EQ(row, 0);
  EXPECT_EQ(col, 0);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom2) {
  auto [row, col] = calculateCoordinates(2);
  EXPECT_EQ(row, 0);
  EXPECT_EQ(col, 1);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom3) {
  auto [row, col] = calculateCoordinates(3);
  EXPECT_EQ(row, 0);
  EXPECT_EQ(col, 2);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom4) {
  auto [row, col] = calculateCoordinates(4);
  EXPECT_EQ(row, 1);
  EXPECT_EQ(col, 0);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom5) {
  auto [row, col] = calculateCoordinates(5);
  EXPECT_EQ(row, 1);
  EXPECT_EQ(col, 1);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom6) {
  auto [row, col] = calculateCoordinates(6);
  EXPECT_EQ(row, 1);
  EXPECT_EQ(col, 2);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom7) {
  auto [row, col] = calculateCoordinates(7);
  EXPECT_EQ(row, 2);
  EXPECT_EQ(col, 0);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom8) {
  auto [row, col] = calculateCoordinates(8);
  EXPECT_EQ(row, 2);
  EXPECT_EQ(col, 1);
}

TEST_F(TicTacToeFixture, ExpectToProperlyCalculateCoordinatesFrom9) {
  auto [row, col] = calculateCoordinates(9);
  EXPECT_EQ(row, 2);
  EXPECT_EQ(col, 2);
}

// Testing the move logic

TEST_F(TicTacToeFixture, ExpectToContinueWithNextPlayerWhenValidInput) {
  setNewPosition = 1;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::NextPlayer);
  EXPECT_TRUE(valResult);
  EXPECT_FALSE(valResult.errorMessage());
}

TEST_F(TicTacToeFixture, ExpectToEndGameWhenManuallyChosen) {
  setNewPosition = TTT::END_GAME_POSITION;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::End);
  EXPECT_FALSE(valResult);
  EXPECT_TRUE(valResult.errorMessage());
  EXPECT_EQ(valResult.errorMessage().value(),
            std::string{"Thanks for playing. Bye bye ^^"});
}

TEST_F(TicTacToeFixture, ExpectToRepeatMoveWhenNegative) {
  setNewPosition = -8;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::SamePlayer);
  EXPECT_FALSE(valResult);
  EXPECT_TRUE(valResult.errorMessage());
  EXPECT_EQ(valResult.errorMessage().value(),
            std::string{"Position is out of scope. Please, try again."});
}

TEST_F(TicTacToeFixture, ExpectToRepeatMoveWhenGreaterThanNumberOfCells) {
  setNewPosition = TTT::ROW * TTT::COL + 1;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::SamePlayer);
  EXPECT_FALSE(valResult);
  EXPECT_TRUE(valResult.errorMessage());
  EXPECT_EQ(valResult.errorMessage().value(),
            std::string{"Position is out of scope. Please, try again."});
}

TEST_F(TicTacToeFixture, ExpectToRepeatMoveWhenDuplicate) {
  setNewPosition = 1;
  // First attempt when newPosition == 1
  EXPECT_TRUE(nextMove());
  // Second attempt when newPosition == 1
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::SamePlayer);
  EXPECT_FALSE(valResult);
  EXPECT_TRUE(valResult.errorMessage());
  EXPECT_EQ(valResult.errorMessage().value(),
            std::string{"Field is already populated. Please try again."});
}

// Testing proper application of final checks

TEST_F(TicTacToeFixture, ExpectToRecognizeWinWhenThreeInARow) {
  setNewPosition = 1;
  EXPECT_TRUE(nextMove());
  setNewPosition = 2;
  EXPECT_TRUE(nextMove());

  setNewPosition = 3;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::Winner);
  EXPECT_TRUE(valResult);
}

TEST_F(TicTacToeFixture, ExpectToRecognizeWinWhenThreeInAColumn) {
  setNewPosition = 1;
  EXPECT_TRUE(nextMove());

  setNewPosition = TTT::COL + 1;
  EXPECT_TRUE(nextMove());

  setNewPosition = TTT::COL * 2 + 1;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::Winner);
  EXPECT_TRUE(valResult);
}

TEST_F(TicTacToeFixture, ExpectToRecognizeWinWhenThreeInADiagonal) {
  setNewPosition = 1;
  EXPECT_TRUE(nextMove());
  setNewPosition = TTT::COL + 2;
  EXPECT_TRUE(nextMove());
  setNewPosition = TTT::COL * 2 + 3;

  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::Winner);
  EXPECT_TRUE(valResult);
}

TEST_F(TicTacToeFixture, ExpectToEndGameWhenNoMoreMovesLeft) {
  for (auto i = 1; i < 8; ++i) {
    setNewPosition = i;
    EXPECT_TRUE(nextMove());
    switchPlayer();
  }

  // It's turn for the playerO. He needs to stop playerX from winning so the
  // move is 9.
  setNewPosition = 9;
  nextMove();
  switchPlayer();

  // Last move (playerX)
  setNewPosition = 8;
  auto valResult = nextMove();

  EXPECT_EQ(valResult.status(), GameStatus::GameOver);
  EXPECT_TRUE(valResult);
}