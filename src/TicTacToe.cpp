#include <TicTacToe.hpp>
#include <iostream>

const Player TicTacToe::playerX = {"Player X", 'X'};
const Player TicTacToe::playerO = {"Player O", 'O'};

TicTacToe::TicTacToe()
    : currentPlayer{&playerX},
      validator_{boardTable_.board()},
      calculator_{boardTable_.board()} {}

void TicTacToe::switchPlayer() {
  boardTable_.print();
  currentPlayer = (currentPlayer == &playerX ? &playerO : &playerX);
}

ValidationResult TicTacToe::nextMove() {
  const auto position = newPosition();

  auto validationPassed = validator_.validate(position);
  if (!validationPassed) return validationPassed;

  const auto [row, col] = calculator_.calculate(position);

  auto canInsert = validator_.validate(row, col, currentPlayer->value);
  if (!canInsert) return canInsert;

  boardTable_.insert(row, col, currentPlayer->value);

  if (boardTable_.win(row, col))
    return GameStatus::Winner;
  else if (boardTable_.full())
    return GameStatus::GameOver;

  return GameStatus::NextPlayer;
}

int TicTacToe::newPosition() const {
  std::cout << currentPlayer->name
            << "'s turn. Choose your position by typing the letter or type -1 "
               "to quit."
            << std::endl;

  int position = 0;
  std::cin >> position;
  return position;
}
