#pragma once

// TODO change names for both
#include <ErrorMessage.hpp>
#include <GameStatus.hpp>

class ValidationResult {
  GameStatus gameStatus;
  ErrorMessage errorMessage;

 public:
  ValidationResult(GameStatus&& = GameStatus::NextPlayer, ErrorMessage&& = {});

  operator bool() const;
  bool operator!() const;

  GameStatus status() const;
  void printError() const;
};