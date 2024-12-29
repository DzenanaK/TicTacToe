#pragma once

#include <cstdint>

enum class GameStatus : uint8_t {
  NextPlayer = 0,
  SamePlayer,
  Winner,
  GameOver
};