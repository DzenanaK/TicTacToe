#include <ValidationResult.hpp>
#include <iostream>

ValidationResult::ValidationResult(GameStatus&& gs, ErrorMessage&& er)
    : gameStatus_{gs}, errorMessage_{er} {}

ValidationResult::operator bool() const { return !errorMessage_; }

bool ValidationResult::operator!() const {
  return static_cast<bool>(errorMessage_);
}

GameStatus ValidationResult::status() const { return gameStatus_; }

void ValidationResult::printMessage() const {
  if (errorMessage_) std::cout << errorMessage_.value() << std::endl;
}
