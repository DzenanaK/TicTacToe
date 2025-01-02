#pragma once
#include <BoardTable.hpp>
#include <Player.hpp>
#include <PositionValidator.hpp>
#include <ValidationResult.hpp>

class TicTacToe {
 public:
  TicTacToe();
  virtual ~TicTacToe();

  ValidationResult nextMove();
  void switchPlayer();

  // Protected and virtual for testing purposes only
 protected:
  std::pair<int, int> calculateCoordinates(const uint8_t& newPosition) const;
  virtual int newPosition() const;

 private:
  static const Player playerX;
  static const Player playerO;

  const Player* currentPlayer_;
  BoardTable boardTable_;
  PositionValidator validator_;
};
