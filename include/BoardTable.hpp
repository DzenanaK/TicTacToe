#pragma once

#include <ConstVariables.hpp>
#include <ErrorMessage.hpp>
#include <array>
#include <cstdint>
#include <optional>

using Board = std::array<std::array<char, COL>, ROW>;

struct BoardTable {
  Board board;
  uint8_t filledFields;

  BoardTable();

  // Inserts element into the board. It expects proper position. In case the
  // field is already populated it returns error.
  ErrorMessage insert(const int& row, const int& col, char value);
  void print();
  bool gameOver() const;

 private:
  void init();
};
