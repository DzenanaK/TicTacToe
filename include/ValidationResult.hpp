#pragma once

#include <ErrorMessage.hpp>
#include <GameStatus.hpp>

class ValidationResult {
 public:
  ValidationResult(GameStatus&& = GameStatus::NextPlayer, ErrorMessage&& = {});

  operator bool() const;
  bool operator!() const;

  GameStatus status() const;
  void printMessage() const;

 private:
  GameStatus gameStatus_;
  ErrorMessage errorMessage_;
};