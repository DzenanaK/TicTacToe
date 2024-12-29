#pragma once

#include <ConstVariables.hpp>
#include <ErrorMessage.hpp>
#include <array>
#include <cstdint>
#include <optional>

// TODO check structs and classes, add forward declarations
struct ValidationResult;

using Board = std::array<std::array<char, COL>, ROW>;

struct BoardTable {
  Board board;
  uint8_t filledFields;

  BoardTable();

  // Inserts element into the board. It expects proper position. In case the
  // field is already populated it returns error.
  ValidationResult insert(const int& row, const int& col, char value);
  void print();
  // TODO probably part of the game struct
  bool full() const;

 private:
  void init();
};
