#pragma once
#include <BoardTable.hpp>
#include <Player.hpp>
#include <PositionCalculator.hpp>
#include <PositionValidator.hpp>
#include <ValidationResult.hpp>

class TicTacToe {
 public:
  TicTacToe();

  ValidationResult nextMove();
  void switchPlayer();

 private:
  static const Player playerX;
  static const Player playerO;

  const Player* currentPlayer;
  BoardTable boardTable_;
  PositionValidator validator_;
  PositionCalculator calculator_;

  int newPosition() const;
};
