#include <iostream>
#include "2048/game/board.hpp"
#include "2048/game/random.hpp"
using namespace std;

Board::Board(size_t width, size_t height) : width(width), height(height) {
	tiles.resize(width * height, 0);
}

bool Board::populate() {
	vector<size_t> emptyIndexes;
	for (size_t i = 0; i < tiles.size(); i++) {
		if (tiles[i] == 0) {
			emptyIndexes.push_back(i);
		}
	}
	if (emptyIndexes.size() == 0) {
		return false;
	}
	const size_t i = emptyIndexes[getRandomInt(0, emptyIndexes.size() - 1)];
	tiles[i] = getRandomInt(0, 19) > 3 ? 2 : 4;
	return true;
}

Board::Board(size_t width, size_t height, size_t prefill) : width(width), height(height) {
	tiles.resize(width * height, 0);
	for (size_t i = 0; i < prefill; i++) {
		populate();
	}
}

void Board::reset() {
	fill(tiles.begin(), tiles.end(), 0);
}

sf::String Board::getDebugString() {
	sf::String str{""};
	for (size_t i = 0; i < tiles.size(); i++) {
		if (i % width == 0 && i != 0) {
			str.insert(str.getSize(), sf::String("\n"));
		}
		str.insert(str.getSize(), sf::String(to_string(tiles[i]) + " "));
	}
	return str;
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
		populate();
	}
}
