#include <BoardTable.hpp>
#include <iostream>
#include <string>

inline const char DEF_VAL = DEF_VAL;

BoardTable::BoardTable() { init(); }

void BoardTable::init() {
  filledFields = 0;

  for (uint8_t i = 0; i < ROW; ++i) {
    for (uint8_t j = 0; j < COL; ++j) {
      board[i][j] = DEF_VAL;
    }
  }
}

void emptyLine() { std::cout << "-----------------" << std::endl; }

void BoardTable::print() {
  int counter = 1;

  for (uint8_t i = 0; i < ROW; ++i) {
    emptyLine();
    for (uint8_t j = 0; j < COL; ++j) {
      std::cout << '|';
      if (counter < 10 || board[i][j] != DEF_VAL) std::cout << ' ';
      if (board[i][j] == DEF_VAL)
        std::cout << counter;
      else
        std::cout << board[i][j];
      ++counter;
    }
    std::cout << "|" << std::endl;
  }

  emptyLine();
}

ErrorMessage BoardTable::insert(const int& row, const int& col, char value) {
  char& boardValue = board[row][col];

  // Board is populated with DEF_VAL by default (in init method)
  if (boardValue != DEF_VAL) {
    return "Invalid position, field is already populated. Please try again!";
  }

  // Insert the value in the board
  board[row][col] = value;
  // Increase counter of populated fields
  ++filledFields;
  return {};
}

bool BoardTable::gameOver() const { return filledFields == ROW * COL; }