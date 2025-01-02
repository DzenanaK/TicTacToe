#include <gtest/gtest.h>

#include <BoardTable.hpp>
#include <GameLogic.hpp>

struct GameLogicFixture : ::testing::Test {
  BoardTable boardTable;
  GameLogic gameLogic{boardTable.board()};
  char X = 'X';

  void insert(int row, int col) { boardTable.insert(row, col, X); }
};

// Testing cases when winning by having a match in a row

TEST_F(GameLogicFixture, RowTestWhenWinningInputIsInTheEnd) {
  insert(0, 0);
  insert(0, 1);

  EXPECT_FALSE(gameLogic.winInRow(0, 2));
  insert(0, 2);
  EXPECT_TRUE(gameLogic.winInRow(0, 2));
}

TEST_F(GameLogicFixture, RowTestWhenWinningInputIsInTheMiddle) {
  insert(0, 0);
  insert(0, 2);

  EXPECT_FALSE(gameLogic.winInRow(0, 1));
  insert(0, 1);
  EXPECT_TRUE(gameLogic.winInRow(0, 1));
}

TEST_F(GameLogicFixture, RowTestWhenWinningInputIsInTheBegin) {
  insert(0, 1);
  insert(0, 2);

  EXPECT_FALSE(gameLogic.winInRow(0, 0));
  insert(0, 0);
  EXPECT_TRUE(gameLogic.winInRow(0, 0));
}

// Testing cases when winning by having a match in a column

TEST_F(GameLogicFixture, ColumnTestWhenWinningInputIsInTheEnd) {
  insert(0, 0);
  insert(1, 0);

  EXPECT_FALSE(gameLogic.winInColumn(2, 0));
  insert(2, 0);
  EXPECT_TRUE(gameLogic.winInColumn(2, 0));
}

TEST_F(GameLogicFixture, ColumnTestWhenWinningInputIsInTheMiddle) {
  insert(0, 0);
  insert(2, 0);

  EXPECT_FALSE(gameLogic.winInColumn(1, 0));
  insert(1, 0);
  EXPECT_TRUE(gameLogic.winInColumn(1, 0));
}

TEST_F(GameLogicFixture, ColumnTestWhenWinningInputIsInTheBegin) {
  insert(1, 0);
  insert(2, 0);

  EXPECT_FALSE(gameLogic.winInColumn(0, 0));
  insert(0, 0);
  EXPECT_TRUE(gameLogic.winInColumn(0, 0));
}

// Testing cases when winning by having a match in a diagonal

TEST_F(GameLogicFixture, DiagonalTestWhenWinningInputIsInTheEnd) {
  insert(0, 0);
  insert(1, 1);

  EXPECT_FALSE(gameLogic.winInDiagonal(2, 2));
  insert(2, 2);
  EXPECT_TRUE(gameLogic.winInDiagonal(2, 2));
}

TEST_F(GameLogicFixture, DiagonalTestWhenWinningInputIsInTheMiddle) {
  insert(0, 0);
  insert(2, 2);

  EXPECT_FALSE(gameLogic.winInDiagonal(1, 1));
  insert(1, 1);
  EXPECT_TRUE(gameLogic.winInDiagonal(1, 1));
}

TEST_F(GameLogicFixture, DiagonalTestWhenWinningInputIsInTheBegin) {
  insert(1, 1);
  insert(2, 2);

  EXPECT_FALSE(gameLogic.winInDiagonal(0, 0));
  insert(0, 0);
  EXPECT_TRUE(gameLogic.winInDiagonal(0, 0));
}

TEST_F(GameLogicFixture, OppositeDiagonalTestWhenWinningInputIsInTheEnd) {
  insert(0, 2);
  insert(1, 1);

  EXPECT_FALSE(gameLogic.winInDiagonal(2, 0));
  insert(2, 0);
  EXPECT_TRUE(gameLogic.winInDiagonal(2, 0));
}

TEST_F(GameLogicFixture, OppositeDiagonalTestWhenWinningInputIsInTheMiddle) {
  insert(0, 2);
  insert(2, 0);

  EXPECT_FALSE(gameLogic.winInDiagonal(1, 1));
  insert(1, 1);
  EXPECT_TRUE(gameLogic.winInDiagonal(1, 1));
}

TEST_F(GameLogicFixture, OppositeDiagonalTestWhenWinningInputIsInTheBegin) {
  insert(1, 1);
  insert(2, 0);

  EXPECT_FALSE(gameLogic.winInDiagonal(0, 2));
  insert(0, 2);
  EXPECT_TRUE(gameLogic.winInDiagonal(0, 2));
}