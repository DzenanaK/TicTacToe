#include <PositionCalculator.hpp>

PositionCalculator::PositionCalculator(const Board& board) : board_{board} {}

std::pair<int, int> PositionCalculator::calculate(
    const int& newPosition) const {
  // Substractiong 1 because computer counts from 0 and not from 1
  int position = newPosition - 1;
  int row = (position / TTT::COL);
  int col = position % TTT::COL;
  return {row, col};
}