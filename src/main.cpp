#include <BoardTable.hpp>
#include <ErrorMessage.hpp>
#include <GameHelpers.hpp>
#include <GameStatus.hpp>
#include <Player.hpp>
#include <iostream>
#include <optional>
#include <string>

extern const uint8_t COL;
extern const uint8_t ROW;

void startMessage();
GameStatus switchTurn(Board&, const Player&);
void printError(const ErrorMessage&);

int main(int argc, char const* argv[]) {
  BoardTable table;
  startMessage();

  const Player playerX{"Player X", 'X'}, playerO{"Player O", 'O'};
  Player currentPlayer = playerX;
  bool continuePlay{true};
  do {
    auto err = switchTurn(table.board, currentPlayer);

    // error handling
    if (err == GameStatus::NextPlayer) {
      table.print();
      // changePlayer
      currentPlayer = currentPlayer.name == playerX.name ? playerO : playerX;
    } else if (err == GameStatus::SamePlayer) {
      //
    }
    // Case (err == GameStatus::GameOver || err == GameStatus::Winner)
    else {
      continuePlay = false;
    }

  } while (continuePlay);

  return 0;
}

void startMessage() {
  std::cout << "Wellcome to Tic Tac Toe game. " << std::endl;
  std::cout << "You will play on the following board. " << std::endl;
  BoardTable b;
  b.print();
}

void printError(const ErrorMessage& error) {
  if (error) std::cout << error.value() << std::endl;
}

ErrorMessage checkPositions(Board& board, char value,
                            const int& positionValue) {
  const auto [row, col] = calculatePositions(positionValue);

  // TODO additional validation! // Moved to board table
  char boardValue = board[row][col];
  if (boardValue != 'Q') {
    // TODO requires additional handling, because the same player needs to play
    // again!
    return "Invalid position, field is already populated. Please try again!";
  }

  // Insert the value in the board
  board[row][col] = value;

  // TODO generalize this
  // Check if there is a match in the colon
  if (value == board[row - 1][col] &&
      (value == board[row - 2][col] || value == board[row + 1][col])) {
    return "Its a winner!";
  }
  if (value == board[row + 1][col] && value == board[row + 2][col]) {
    return "Its a winner!";
  }

  // Check if there is a match in the row
  if (value == board[row][col - 1] &&
      (value == board[row][col - 2] || value == board[row][col + 1])) {
    return "Its a winner!";
  }
  if (value == board[row][col + 1] && value == board[row][col + 2]) {
    return "Its a winner!";
  }

  // Check diagonal
  if (value == board[row - 1][col - 1] &&
      (value == board[row - 2][col - 2] || value == board[row + 1][col + 1])) {
    return "Its a winner!";
  }
  if (value == board[row + 1][col + 1] && value == board[row + 2][col + 2]) {
    return "Its a winner!";
  }

  // TODO check if limits are ok!!

  return {};
}

GameStatus switchTurn(Board& board, const Player& player) {
  std::cout << player.name
            << "'s turn. Choose your position by typing the letter or type -1 "
               "to quit."
            << std::endl;

  int position = 0;
  std::cin >> position;

  auto err = validate(position);
  if (err) {
    // TODO not good
    // TODO Error and game code should be part of one struct
    printError(err);
    return GameStatus::GameOver;
  };

  // TODO enable this
  // const auto [row, col] = calculatePositions(positionValue);
  // auto err = boardTable.insert(row, col, player.value);
  // if(err) {repeatSamePlayer();}
  //  else switchPlayers();

  auto finished = checkPositions(board, player.value, position);
  if (finished) {
    printError(finished);
    return GameStatus::GameOver;
  }

  return GameStatus::NextPlayer;
}