#pragma once
#include <BoardTable.hpp>
#include <Player.hpp>
#include <PositionValidator.hpp>
#include <ValidationResult.hpp>

class TicTacToe {
 public:
  TicTacToe();
  virtual ~TicTacToe();

  void play();

  // Protected and virtual for testing purposes only
 protected:
  std::pair<int, int> calculateCoordinates(const uint8_t& newPosition) const;
  virtual int getPosition() const;
  ValidationResult playMove();
  void switchPlayer();

 private:
  static const Player playerX;
  static const Player playerO;

  const Player* currentPlayer_;
  BoardTable boardTable_;
  PositionValidator validator_;

  void startMessage() const;
  void gameOver(bool& continueGame, std::string&& message) const;
};
