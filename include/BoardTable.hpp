#pragma once

#include <Board.hpp>
#include <GameLogic.hpp>

class BoardTable {
 public:
  BoardTable();

  const Board& board() const;

  void insert(const int& row, const int& col, char value);
  void print() const;

  bool full() const;
  bool win(const int& row, const int& col) const;

 private:
  Board board_;
  uint8_t filledFields_;
  GameLogic logic_;
};
