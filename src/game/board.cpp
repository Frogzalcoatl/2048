#include <algorithm>
#include "2048/game/board.hpp"
#include "2048/game/random.hpp"
#include "2048/game/scoreStorage.hpp"
using namespace std;

Board::Board(size_t width, size_t height) : width(width), height(height) {
	tiles.resize(width * height, 0);
}

size_t Board::populate() {
	static vector<size_t> emptyIndexes;
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

Board::Board(size_t width, size_t height, size_t prefill) : width(width), height(height), prefill(prefill) {
	tiles.resize(width * height, 0);
	doPrefill();
}

void Board::reset() {
	gameOverStatus = false;
	fill(tiles.begin(), tiles.end(), 0);
	doPrefill();
}

const vector<uint64_t>& Board::getTiles() const {
	return tiles;
}

vector<uint64_t> Board::mergeLine(const vector<uint64_t>& line) {
	vector<uint64_t> output;
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

vector<uint64_t> Board::getRow(size_t i) {
	vector<uint64_t> output;
	output.reserve(width);
	size_t startIndex = i * width;
	for (size_t j = 0; j < width; j++) {
		output.push_back(tiles[startIndex + j]);
	}
	return output;
}

vector<uint64_t> Board::getColumn(size_t i) {
	vector<uint64_t> output;
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
		vector<uint64_t> line;
		if (direction == Direction::Up || direction == Direction::Down) {
			line = getColumn(i);
		} else {
			line = getRow(i);
		}
		if (direction == Direction::Down || direction == Direction::Right) {
			reverse(line.begin(), line.end());
		}
		vector<uint64_t> mergedLine = mergeLine(line);
		if (direction == Direction::Down || direction == Direction::Right) {
			reverse(mergedLine.begin(), mergedLine.end());
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
	ScoreStorage::saveHighScore(getScore());
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