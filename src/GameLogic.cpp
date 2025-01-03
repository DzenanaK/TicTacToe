#include <ConstVariables.hpp>
#include <GameLogic.hpp>

GameLogic::GameLogic(const Board& b) : board_{b} {}

bool GameLogic::winInRow(const int& row, const int& col) const {
  const char value = board_[row][col];

  // Ensure that checks are applied against the X or O
  if (value == TTT::DEF_VAL) return false;

  return ((col - 1 >= 0 && value == board_[row][col - 1]) &&
          ((col - 2 >= 0 && value == board_[row][col - 2]) ||
           (col + 1 < TTT::COL && value == board_[row][col + 1]))) ||

         (col + 2 < TTT::COL && value == board_[row][col + 1] &&
          value == board_[row][col + 2]);
}

bool GameLogic::winInColumn(const int& row, const int& col) const {
  const char value = board_[row][col];
  // Ensure that checks are applied against the X or O
  if (value == TTT::DEF_VAL) return false;

  return ((row - 1 >= 0 && value == board_[row - 1][col]) &&
          ((row - 2 >= 0 && value == board_[row - 2][col]) ||
           (row + 1 < TTT::COL && value == board_[row + 1][col]))) ||

         (row + 2 < TTT::ROW && value == board_[row + 1][col] &&
          value == board_[row + 2][col]);
}

bool GameLogic::winInDiagonal(const int& row, const int& col) const {
  const char value = board_[row][col];

  // Ensure that checks are applied against the X or O
  if (value == TTT::DEF_VAL) return false;

  // Check diagonal
  return ((row - 1 >= 0 && col - 1 >= 0 && value == board_[row - 1][col - 1]) &&
          ((row - 2 >= 0 && value == board_[row - 2][col - 2]) ||
           (row + 1 < TTT::ROW && col + 1 < TTT::COL &&
            value == board_[row + 1][col + 1]))) ||

         (row + 2 < TTT::ROW && col + 2 < TTT::COL &&
          value == board_[row + 1][col + 1] &&
          value == board_[row + 2][col + 2]) ||

         // Check opposite diagonal
         ((row - 1 >= 0 && col + 1 < TTT::COL &&
           value == board_[row - 1][col + 1]) &&

          ((row + 1 < TTT::ROW && col - 1 >= 0 &&
            value == board_[row + 1][col - 1]) ||
           (row - 2 >= 0 && col + 2 < TTT::COL &&
            value == board_[row - 2][col + 2]))) ||

         (row + 2 < TTT::ROW && col - 2 >= 0 &&
          value == board_[row + 1][col - 1] &&
          value == board_[row + 2][col - 2]);
}