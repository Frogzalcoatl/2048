#include "2048/game/scoreStorage.hpp"
#include "2048/game/stringToInt.hpp"
#include <fstream>
#include <string>
#include <filesystem>

const std::string FOLDER_NAME = "data";
const std::filesystem::path FILE_PATH = std::filesystem::path(FOLDER_NAME) / "highscore.txt";

uint64_t ScoreStorage::loadHighScore(Board& board) {
    if (!std::filesystem::exists(FILE_PATH)) {
        uint64_t currentScore = board.getScore();
        saveHighScore(currentScore);
        return currentScore;
    }
    std::ifstream file(FILE_PATH);
    std::string fileContent;
    file >> fileContent;
    return stringToUInt64(fileContent);
}

void ScoreStorage::saveHighScore(uint64_t newScore) {
    if (!std::filesystem::exists(FOLDER_NAME)) {
        std::filesystem::create_directory(FOLDER_NAME);
    }
    std::ofstream file(FILE_PATH);
    if (file.is_open()) {
        file << newScore;
    }
}