#include <array>
#include <iostream>
#include <optional>
#include <string>

const uint8_t COL = 5;
const uint8_t ROW = 3;

// TODO make this struct

using Board = std::array<std::array<char, COL>, ROW>;
void initializeBoard(Board&);
void printBoard(const Board& b);

struct Player {
  std::string_view name;
  char value;
};

void startMessage();
using ErrorMessage = std::string;
std::optional<ErrorMessage> switchTurn(Board&, const Player&);
void printError(const ErrorMessage&);

int main(int argc, char const* argv[]) {
  //
  Board b;
  initializeBoard(b);
  startMessage();

  const Player playerX{"Player X", 'X'}, playerO{"Player O", 'O'};
  Player currentPlayer = playerX;
  bool continuePlay{true};
  do {
    auto err = switchTurn(b, currentPlayer);

    // error handling
    if (err) {
      printError(*err);
      return 1;
    }

    // changePlayer
    currentPlayer = currentPlayer.name == playerX.name ? playerO : playerX;

  } while (continuePlay);

  return 0;
}

void startMessage() {
  std::cout << "Wellcome to Tic Tac Toe game. " << std::endl;
  std::cout << "You will play on the following board. " << std::endl;
  Board b;
  initializeBoard(b);
  printBoard(b);
}

void printError(const ErrorMessage& error) { std::cout << error << std::endl; }

// TODO improve error handling!
std::optional<ErrorMessage> validate(const int& position) {
  if (0 < position && position <= ROW * COL) return {};
  if (position == -1) return "Thanks for playing. Bye bye ^^";
  return "Invalid input!";
}

// TODO move to validation
std::pair<int, int> calculatePositions(const int& positionValue) {
  // Substractiong 1 because computer counts from 0 and not from 1
  int position = positionValue - 1;
  int row = (position / COL);
  int col = position % COL;
  return {row, col};
}

std::optional<ErrorMessage> checkPositions(Board& board, char value,
                                           const int& positionValue) {
  const auto [row, col] = calculatePositions(positionValue);

  // TODO additional validation!
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

  printBoard(board);
  // TODO check if limits are ok!!
  // TODO check GAME OVER is missing;

  return {};
}

std::optional<ErrorMessage> switchTurn(Board& board, const Player& player) {
  std::cout << player.name
            << "'s turn. Choose your position by typing the letter or type -1 "
               "to quit."
            << std::endl;

  int position = 0;
  std::cin >> position;

  auto r = validate(position);
  if (r) return r;

  auto finished = checkPositions(board, player.value, position);
  if (finished) return finished;

  return {};
}

void emptyLine() {
  // TODO
  for (int i = 0; i < COL; ++i) std::cout << "---";
  std::cout << std::endl;
}

void initializeBoard(Board& board) {
  uint8_t counter = 0;
  for (uint8_t i = 0; i < ROW; ++i) {
    for (uint8_t j = 0; j < COL; ++j) {
      ++counter;
      board[i][j] = 'Q';
    }
  }
}

// TODO improve
void printBoard(const Board& board) {
  int counter = 0;
  for (uint8_t i = 0; i < ROW; ++i) {
    emptyLine();
    for (uint8_t j = 0; j < COL; ++j) {
      // edz improve printing!
      if (counter < 9) {
        std::cout << "| ";
      } else
        std::cout << "|";
      ++counter;
      if (board[i][j] == 'Q')
        std::cout << counter;
      else
        std::cout << board[i][j];
    }
    std::cout << "|" << std::endl;
  }
  emptyLine();
}