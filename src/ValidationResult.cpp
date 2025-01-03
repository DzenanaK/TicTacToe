#include <ValidationResult.hpp>
#include <iostream>

ValidationResult::ValidationResult(GameStatus&& gs, ErrorMessage&& er)
    : gameStatus{gs}, errorMessage{er} {}

ValidationResult::operator bool() const { return !errorMessage; }

bool ValidationResult::operator!() const {
  return static_cast<bool>(errorMessage);
}

void ValidationResult::printMessage() const {
  if (errorMessage) std::cout << errorMessage.value() << std::endl;
}
