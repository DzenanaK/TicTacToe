#pragma once

#include <ErrorMessage.hpp>
#include <utility>

std::pair<int, int> calculatePositions(const int& positionValue);

// Basic validation of limits
ErrorMessage validate(const int& positionNumber);