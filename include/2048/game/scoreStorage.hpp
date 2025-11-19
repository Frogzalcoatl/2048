#pragma once
#include <cstdint>

namespace ScoreStorage {
    std::uint64_t loadHighScore();
    void saveHighScore(std::uint64_t newScore);
}