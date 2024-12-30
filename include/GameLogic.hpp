#pragma once

#include <Board.hpp>

class GameLogic {
 public:
  GameLogic(const Board&);

  bool winInRow(const int& row, const int& col) const;
  bool winInColumn(const int& row, const int& col) const;
  bool winInDiagonal(const int& row, const int& col) const;

 private:
  const Board& board_;
};