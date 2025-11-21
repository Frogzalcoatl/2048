#include "2048/game/board.hpp"
#include "2048/game/random.hpp"
#include "2048/game/stringToInt.hpp"
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <string>
#include <sstream>
#include <iostream>

const std::string FOLDER_NAME = "data";
const std::string TILES_FILE_NAME = "tiles.txt";
const auto TILES_FILE_PATH = std::filesystem::path(FOLDER_NAME) / TILES_FILE_NAME;
const std::string HIGHSCORE_FILE_NAME = "highscore.txt";
const auto HIGHSCORE_FILE_PATH = std::filesystem::path(FOLDER_NAME) / HIGHSCORE_FILE_NAME;

uint64_t Board::getHighScore() const {
	return std::max(getScore(), cachedHighScore);
}

void Board::saveHighScoreToFile() const {
    std::ofstream file(HIGHSCORE_FILE_PATH);
    if (file.is_open()) {
        file << cachedHighScore;
    }
}

std::string vectorToString(const std::vector<uint64_t>& vec) {
	std::string str;
	for (size_t i = 0; i < vec.size(); i++) {
		str += std::to_string(vec[i]);
		if (i + 1 < vec.size()) {
			str += ",";
		}
	}
	return str;
}

std::vector<uint64_t> stringToVector(const std::string& s) {
	std::vector<uint64_t> vec;
	// Allows string tokenization between commas ","
	std::stringstream ss(s);
	std::string token;
	while (std::getline(ss, token, ',')) {
		if (token.empty()) continue;
		vec.push_back(stringToUInt64(token));
	}
	return vec;
}

bool Board::isValidTilesVector(const std::vector<uint64_t> tilesVector) const {
	if (tilesVector.size() != width * height) {
		return false;
	}
	for (const auto& num : tilesVector) {
		// & is the bitwise AND operator: it keeps a 1 only if both numbers have a 1 in that bit.
		// ex: 4 = 0100, & 7 = 1111, 4 & 7  = 0100
		// (num & (num - 1)) == 0 is true for powers of two AND zero.
		// ex: 8 = 1000, 8 - 1 = 0111, 8 & 7 = 0000
		if ((num & (num - 1)) != 0) {
			return false;
		}
	}
	return true;
}

void Board::loadBoardFromFile() {
	tiles.resize(width * height, 0);
    if (!std::filesystem::exists(TILES_FILE_PATH)) {
		doPrefill();
		saveBoardToFile();
		return;
    }
	std::ifstream file(TILES_FILE_PATH);
    std::string fileContent;
	file >> fileContent;
	std::vector<uint64_t> loadedTiles = stringToVector(fileContent);
	if (!isValidTilesVector(loadedTiles)) {
		doPrefill();
		saveBoardToFile();
		return;
	}
	tiles = loadedTiles;
	size_t emptyTileCount = 0;
	for (size_t i = 0; i < tiles.size(); i++) {
		if (tiles[i] == 0) {
			emptyTileCount++;
		}
	}
	updateGameOverStatus(emptyTileCount);
	if (gameOverStatus) {
		reset();
	}
}

void Board::saveBoardToFile() const {
	if (!std::filesystem::exists(FOLDER_NAME)) {
        std::filesystem::create_directory(FOLDER_NAME);
    }
	std::ofstream file(TILES_FILE_PATH);
	if (file.is_open()) {
		file << vectorToString(tiles);
	}
}

void Board::saveData() {
	uint64_t currentScore = getScore();
    if (currentScore > cachedHighScore) {
        cachedHighScore = currentScore;
    }
	saveBoardToFile();
	saveHighScoreToFile();
}

size_t Board::populate() {
	static std::vector<size_t> emptyIndexes;
	emptyIndexes.clear();
	for (size_t i = 0; i < tiles.size(); i++) {
		if (tiles[i] == 0) {
			emptyIndexes.push_back(i);
		}
	}
	if (emptyIndexes.size() == 0) {
		return 0;
	}
	const size_t i = emptyIndexes[getRandomInt(0, emptyIndexes.size() - 1)];
	tiles[i] = getRandomInt(0, 19) > 3 ? 2 : 4;
	return emptyIndexes.size() - 1;
}

void Board::doPrefill() {
	for (size_t i = 0; i < prefill; i++) {
		populate();
	}
}

Board::Board(size_t width, size_t height, size_t prefill) : width{width}, height{height}, prefill{prefill} {
	loadBoardFromFile();
	std::ifstream file(HIGHSCORE_FILE_PATH);
    if (file.is_open()) {
        std::string content;
        file >> content;
        cachedHighScore = stringToUInt64(content);
    }
}

void Board::reset() {
	uint64_t currentScore = getScore();
    if (currentScore > cachedHighScore) {
        cachedHighScore = currentScore;
    }
	gameOverStatus = false;
	fill(tiles.begin(), tiles.end(), 0);
	doPrefill();
}

const std::vector<uint64_t>& Board::getTiles() const {
	return tiles;
}

std::vector<uint64_t> Board::mergeLine(const std::vector<uint64_t>& line) {
	std::vector<uint64_t> output;
	output.resize(line.size(), 0);
	uint64_t j = 0;
	uint64_t jValue = 0;
	for (size_t i = 0; i < line.size(); i++) {
		uint64_t currentValue = line[i];
		if (currentValue == 0) {
			continue;
		}
		if (currentValue == jValue) {
			output[j - 1] *= 2;
			jValue = 0;
		} else {
			jValue = currentValue;
			output[j] = currentValue;
			j++;
		}
	}
	return output;
}

std::vector<uint64_t> Board::getRow(size_t i) {
	std::vector<uint64_t> output;
	output.reserve(width);
	size_t startIndex = i * width;
	for (size_t j = 0; j < width; j++) {
		output.push_back(tiles[startIndex + j]);
	}
	return output;
}

std::vector<uint64_t> Board::getColumn(size_t i) {
	std::vector<uint64_t> output;
	output.reserve(height);
	for (size_t j = 0; j < height; j++) {
		output.push_back(tiles[j * width + i]);
	}
	return output;
};

void Board::doMove(Direction direction) {
	bool moved = false;
	bool isVertical = direction == Direction::Up || direction == Direction::Down;
	size_t size = isVertical ? height : width;
	for (size_t i = 0; i < size; i++) {
		std::vector<uint64_t> line;
		if (direction == Direction::Up || direction == Direction::Down) {
			line = getColumn(i);
		} else {
			line = getRow(i);
		}
		if (direction == Direction::Down || direction == Direction::Right) {
			std::reverse(line.begin(), line.end());
		}
		std::vector<uint64_t> mergedLine = mergeLine(line);
		if (direction == Direction::Down || direction == Direction::Right) {
			std::reverse(mergedLine.begin(), mergedLine.end());
		}
		for (size_t j = 0; j < size; j++) {
			size_t index = isVertical ? j * width + i : i * width + j;
			if (tiles[index] != mergedLine[j]) {
				moved = true;
				tiles[index] = mergedLine[j];
			}
		}
	}
	if (moved) {
		updateGameOverStatus(populate());
	}
}

void Board::updateGameOverStatus(size_t emptyCount) {
	if (emptyCount > 0) {
		gameOverStatus = false;
		return;
	}
	size_t sizeOfTiles = tiles.size();
	for (size_t i = 0; i < sizeOfTiles; i++) {
		size_t belowIndex = i + width;
		if (belowIndex < sizeOfTiles && tiles[i] == tiles[belowIndex]) {
			gameOverStatus = false;
			return;
		}
		if (i % width != width - 1 && (i + 1) < sizeOfTiles && tiles[i] == tiles[i + 1]) {
			gameOverStatus = false;
			return;
		}
	}
	gameOverStatus = true;
	saveBoardToFile();
}

uint64_t Board::getScore() const {
	uint64_t score = 0;
	for (auto& value : tiles) {
		score += value;
	}
	return score;
}

bool Board::getGameOverStatus() const {
	return gameOverStatus;
}