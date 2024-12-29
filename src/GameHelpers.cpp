#include <ConstVariables.hpp>
#include <GameHelpers.hpp>

std::pair<int, int> calculatePositions(const int& positionNumber) {
  // Substractiong 1 because computer counts from 0 and not from 1
  int position = positionNumber - 1;
  int row = (position / COL);
  int col = position % COL;
  return {row, col};
}

ErrorMessage validate(const int& positionNumber) {
  if (0 < positionNumber && positionNumber <= ROW * COL) return {};
  if (positionNumber == -1) return "Thanks for playing. Bye bye ^^";
  return "Invalid input! Try again";
}