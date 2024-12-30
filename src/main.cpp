#include <BoardTable.hpp>
#include <GameStatus.hpp>
#include <Player.hpp>
#include <TicTacToe.hpp>
#include <ValidationResult.hpp>
#include <iostream>
#include <optional>
#include <string>

extern const uint8_t COL;
extern const uint8_t ROW;

void startMessage();
void gameOver(bool& continueGame, std::string&& message);

int main(int argc, char const* argv[]) {
  startMessage();

  TicTacToe game;
  bool continuePlay{true};
  do {
    auto valResult = game.nextMove();

    // GameStatus handling
    if (valResult.status() == GameStatus::NextPlayer) {
      game.switchPlayer();
    } else if (valResult.status() == GameStatus::SamePlayer) {
      valResult.printMessage();
    } else if (valResult.status() == GameStatus::Winner) {
      gameOver(continuePlay, "Game over: we have the winner. Congratulations!");
    } else if (valResult.status() == GameStatus::GameOver) {
      gameOver(continuePlay, "Game over: no more moves left.");
    } else {
      // case status == End
      gameOver(continuePlay, "Thank you for playing.");
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

void gameOver(bool& continueGame, std::string&& message) {
  continueGame = false;
  std::cout << message << std::endl;
}