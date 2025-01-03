#include <BoardTable.hpp>
#include <ValidationResult.hpp>
#include <iostream>
#include <string>

using namespace TTT;

BoardTable::BoardTable() : filledFields_{0}, logic_{board_} {
  for (auto& row : board_) row.fill(DEF_VAL);
}

const Board& BoardTable::board() const { return board_; }

void BoardTable::print() const {
  std::string rowDelimiter;
  for (auto i = 0; i < TTT::COL; ++i) rowDelimiter += "---";
  rowDelimiter += "\n";
  // Number of the characters in the for loop
  int capacity = ROW * (rowDelimiter.size() + COL * 3 + 3);
  // Number of the characters after the for loop
  capacity += (rowDelimiter.size() + 1);
  std::string message;
  message.reserve(capacity);

  int counter = 1;
  for (uint8_t i = 0; i < ROW; ++i) {
    message += rowDelimiter;
    for (uint8_t j = 0; j < COL; ++j) {
      message += "|";
      if (counter < 10 || board_[i][j] != DEF_VAL) message += " ";
      if (board_[i][j] == DEF_VAL)
        message += std::to_string(counter);
      else
        message += board_[i][j];
      ++counter;
    }
    message += "| \n";
  }

  message += rowDelimiter;
  message += "\n";

  std::cout << message << std::endl;
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