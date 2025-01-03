#include <TicTacToe.hpp>
#include <iostream>

const Player TicTacToe::playerX = {"Player X", 'X'};
const Player TicTacToe::playerO = {"Player O", 'O'};

TicTacToe::TicTacToe()
    : currentPlayer_{&playerX}, validator_{boardTable_.board()} {}

TicTacToe::~TicTacToe() {}

void TicTacToe::play() {
  startMessage();

  bool continuePlay{true};
  do {
    auto valResult = playMove();

    // GameStatus handling
    if (valResult.gameStatus == GameStatus::Continue) {
      switchPlayer();
    } else if (valResult.gameStatus == GameStatus::RepeatMove) {
      valResult.printMessage();
    } else if (valResult.gameStatus == GameStatus::Win) {
      std::string message{"Game over: "};
      message += currentPlayer_->name;
      message += " is the winner. Congratulations!";
      gameOver(continuePlay, std::move(message));
    } else if (valResult.gameStatus == GameStatus::GameOver) {
      gameOver(continuePlay, "Game over: no more moves left.");
    } else {
      // case status == End
      gameOver(continuePlay, "Thank you for playing.");
    }

  } while (continuePlay);
}

void TicTacToe::startMessage() const {
  std::cout << "Wellcome to the Tic Tac Toe game. " << std::endl
            << "You will play on the following board: " << std::endl;
  boardTable_.print();
}

ValidationResult TicTacToe::playMove() {
  const auto position = getPosition();

  auto validationPassed = validator_.validate(position);
  if (!validationPassed) return validationPassed;

  const auto [row, col] = calculateCoordinates(position);

  auto canInsert = validator_.validate(row, col, currentPlayer_->value);
  if (!canInsert) return canInsert;

  boardTable_.insert(row, col, currentPlayer_->value);

  if (boardTable_.win(row, col))
    return GameStatus::Win;
  else if (boardTable_.full())
    return GameStatus::GameOver;

  return GameStatus::Continue;
}

int TicTacToe::getPosition() const {
  std::cout << currentPlayer_->name << ", enter your move (1-"
            << TTT::ROW * TTT::COL << ") or -1 to quit: ";

  int position = 0;
  std::cin >> position;
  return position;
}

std::pair<int, int> TicTacToe::calculateCoordinates(
    const uint8_t& newPosition) const {
  // Subtracting 1 because computer counts from 0 and not from 1
  int position = newPosition - 1;
  int row = (position / TTT::COL);
  int col = position % TTT::COL;
  return {row, col};
}

void TicTacToe::switchPlayer() {
  boardTable_.print();
  currentPlayer_ = (currentPlayer_ == &playerX ? &playerO : &playerX);
}

void TicTacToe::gameOver(bool& continueGame, std::string&& message) const {
  continueGame = false;
  std::cout << message << std::endl;
}