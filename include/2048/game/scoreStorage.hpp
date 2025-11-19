#pragma once
#include <cstdint>
#include "2048/game/board.hpp"

namespace ScoreStorage {
    std::uint64_t loadHighScore(Board& board);
    void saveHighScore(std::uint64_t newScore);
}