#include <ConstVariables.hpp>
#include <PositionValidator.hpp>

PositionValidator::PositionValidator(const Board& b) : board_{b} {};

ValidationResult PositionValidator::validate(const int& newPosition) const {
  if (0 < newPosition && newPosition <= TTT::ROW * TTT::COL) return {};

  if (newPosition == TTT::END_GAME_POSITION)
    return {GameStatus::End, "Thanks for playing. Bye bye ^^"};

  return {GameStatus::RepeatMove,
          "Position is out of scope. Please, try again."};
}

ValidationResult PositionValidator::validate(const int& row, const int& col,
                                             char value) const {
  // Board is populated with DEF_VAL by default (in init method). In case it
  // stores other value than DEF_VAL, it means that that field is already
  // populated and shouldn't be changed.
  if (board_[row][col] != TTT::DEF_VAL) {
    return {GameStatus::RepeatMove,
            "Field is already populated. Please try again."};
  }

  return {};
}