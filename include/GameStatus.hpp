#pragma once

#include <cstdint>

enum class GameStatus : uint8_t {
  Continue = 0,
  RepeatMove,
  Win,
  GameOver,
  End
};