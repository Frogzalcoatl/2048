#include "2048/game/scoreStorage.hpp"
#include "2048/game/stringToInt.hpp"
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

const string FOLDER_NAME = "data";
const std::filesystem::path FILE_PATH = std::filesystem::path(FOLDER_NAME) / "highscore.txt";

uint64_t ScoreStorage::loadHighScore(Board& board) {
    if (!filesystem::exists(FILE_PATH)) {
        uint64_t currentScore = board.getScore();
        saveHighScore(currentScore);
        return currentScore;
    }
    ifstream file(FILE_PATH);
    string fileContent;
    file >> fileContent;
    return stringToUInt64(fileContent);
}

void ScoreStorage::saveHighScore(uint64_t newScore) {
    if (!filesystem::exists(FOLDER_NAME)) {
        filesystem::create_directory(FOLDER_NAME);
    }
    ofstream file(FILE_PATH);
    if (file.is_open()) {
        file << newScore;
    }
}