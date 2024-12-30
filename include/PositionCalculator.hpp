#pragma once

#include <Board.hpp>
#include <utility>

class PositionCalculator {
 public:
  PositionCalculator(const Board&);

  std::pair<int, int> calculate(const int& newPosition) const;

 private:
  const Board& board_;
};
