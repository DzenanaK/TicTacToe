#pragma once
#include <BoardTable.hpp>
#include <Player.hpp>
#include <ValidationResult.hpp>

class TicTacToe {
 public:
  static const Player playerX;
  static const Player playerO;
  const Player* currentPlayer = &playerX;
  BoardTable boardTable;

 public:
  ValidationResult nextMove();
  void switchPlayer();

 private:
  ValidationResult validate(const int& newPosition) const;
  std::pair<int, int> calculatePositions(const int& newPosition) const;
  GameStatus checkPositions(const int& row, const int& col) const;
};
