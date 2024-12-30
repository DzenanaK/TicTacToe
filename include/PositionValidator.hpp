#pragma once

#include <Board.hpp>
#include <ValidationResult.hpp>

class PositionValidator {
 public:
  PositionValidator(const Board&);

  // Validation of the input value (aka position)
  ValidationResult validate(const int& newPosition) const;

  // Validation of the positions in the board
  ValidationResult validate(const int& row, const int& col, char value) const;

 private:
  const Board& board_;
};
