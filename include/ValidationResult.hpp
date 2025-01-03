#pragma once

#include <ErrorMessage.hpp>
#include <GameStatus.hpp>

struct ValidationResult {
  // Members
  GameStatus gameStatus;
  ErrorMessage errorMessage;

  // Methods
  ValidationResult(GameStatus&& = GameStatus::Continue, ErrorMessage&& = {});

  operator bool() const;
  bool operator!() const;

  void printMessage() const;
};