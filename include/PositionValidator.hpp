#pragma once

#include <Board.hpp>
#include <ValidationResult.hpp>

class PositionValidator {
 public:
  PositionValidator(const Board&);

  // Validating the user input value (aka position). Represents basic
  // validation, before continuing to calculate actual positions in the board.
  ValidationResult validate(const int& newPosition) const;

  // Validating coordinates in the board. Represents validation before inputing
  // the value in to the board. It ensures that existing values aren't overriden
  // by new attempts.
  ValidationResult validate(const int& row, const int& col, char value) const;

 private:
  const Board& board_;
};
