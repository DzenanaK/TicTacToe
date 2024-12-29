#include <TicTacToe.hpp>
#include <iostream>

const Player TicTacToe::playerX = {"Player X", 'X'};
const Player TicTacToe::playerO = {"Player O", 'O'};

void TicTacToe::switchPlayer() {
  boardTable.print();
  currentPlayer = (currentPlayer == &playerX ? &playerO : &playerX);
}

ValidationResult TicTacToe::nextMove() {
  std::cout << currentPlayer->name
            << "'s turn. Choose your position by typing the letter or type -1 "
               "to quit."
            << std::endl;

  int position = 0;
  std::cin >> position;

  auto validationPassed = validate(position);
  if (!validationPassed) {
    return validationPassed;
  };

  const auto [row, col] = calculatePositions(position);
  // TODO move operator?
  ValidationResult inserted = boardTable.insert(row, col, currentPlayer->value);

  if (!inserted) {
    return inserted;
  } else if (boardTable.full())
    return {GameStatus::GameOver};

  auto gameStatus = checkPositions(row, col);
  // TODO WIP
  boardTable.print();
  return {std::move(gameStatus)};
}

// TODO change with validation
ValidationResult TicTacToe::validate(const int& newPosition) const {
  if (0 < newPosition && newPosition <= ROW * COL) return {};
  if (newPosition == -1)
    return {GameStatus::End, "Thanks for playing. Bye bye ^^"};
  return {GameStatus::SamePlayer, "Invalid input! Try again"};
}

std::pair<int, int> TicTacToe::calculatePositions(
    const int& newPosition) const {
  // Substractiong 1 because computer counts from 0 and not from 1
  int position = newPosition - 1;
  int row = (position / COL);
  int col = position % COL;
  return {row, col};
}

GameStatus TicTacToe::checkPositions(const int& row, const int& col) const {
  const Board& board = boardTable.board;
  char value = currentPlayer->value;

  // TODO generalize this
  // Check if there is a match in the colon
  if (value == board[row - 1][col] &&
      (value == board[row - 2][col] || value == board[row + 1][col])) {
    return GameStatus::Winner;
  }
  if (value == board[row + 1][col] && value == board[row + 2][col]) {
    return GameStatus::Winner;
  }

  // Check if there is a match in the row
  if (value == board[row][col - 1] &&
      (value == board[row][col - 2] || value == board[row][col + 1])) {
    return GameStatus::Winner;
  }
  if (value == board[row][col + 1] && value == board[row][col + 2]) {
    return GameStatus::Winner;
  }

  // Check diagonal
  if (value == board[row - 1][col - 1] &&
      (value == board[row - 2][col - 2] || value == board[row + 1][col + 1])) {
    return GameStatus::Winner;
  }
  if (value == board[row + 1][col + 1] && value == board[row + 2][col + 2]) {
    return GameStatus::Winner;
  }

  // TODO check if limits are ok!!

  return GameStatus::NextPlayer;
}
