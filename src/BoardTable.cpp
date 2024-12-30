#include <BoardTable.hpp>
#include <ValidationResult.hpp>
#include <iostream>
#include <string>

using namespace TTT;

BoardTable::BoardTable() : filledFields_{0}, logic_{board_} {
  for (auto& row : board_) row.fill(DEF_VAL);
}

const Board& BoardTable::board() const { return board_; }

void emptyLine() { std::cout << "-----------------" << std::endl; }

void BoardTable::print() const {
  int counter = 1;

  for (uint8_t i = 0; i < ROW; ++i) {
    emptyLine();
    for (uint8_t j = 0; j < COL; ++j) {
      std::cout << '|';
      if (counter < 10 || board_[i][j] != DEF_VAL) std::cout << ' ';
      if (board_[i][j] == DEF_VAL)
        std::cout << counter;
      else
        std::cout << board_[i][j];
      ++counter;
    }
    std::cout << "|" << std::endl;
  }

  emptyLine();
}

void BoardTable::insert(const int& row, const int& col, char value) {
  // Insert the value in the board
  board_[row][col] = value;
  // Increase counter of populated fields
  ++filledFields_;
}

bool BoardTable::full() const { return filledFields_ == ROW * COL; }

bool BoardTable::win(const int& row, const int& col) const {
  return logic_.winInColumn(row, col) || logic_.winInRow(row, col) ||
         logic_.winInDiagonal(row, col);
}