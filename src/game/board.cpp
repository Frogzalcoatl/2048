#include <iostream>
#include "2048/game/board.hpp"
#include "2048/game/random.hpp"
using namespace std;

Board::Board() {
	tiles.fill(0);
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

Board::Board(size_t prefill) {
	tiles.fill(0);
	for (size_t i = 0; i < prefill; i++) {
		populate();
	}
}

void Board::reset() {
	tiles.fill(0);
}

sf::String Board::getTestString() {
	sf::String str("");
	for (size_t i = 0; i < tiles.size(); i++) {
		if (i % 4 == 0 && i != 0) {
			str.insert(str.getSize(), sf::String("\n"));
		}
		str.insert(str.getSize(), sf::String(to_string(tiles[i]) + " "));
	}
	return str;
}

array<uint64_t, 4> Board::mergeLine(const array<uint64_t, 4>& line) {
	array<uint64_t, 4> output;
	output.fill(0);
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

void reverseArray(std::array<uint64_t, 4>& arr) {
	for (size_t i = 0; i < arr.size() / 2; i++) {
		swap(arr[i], arr[arr.size() - i - 1]);
	}
}

std::array<uint64_t, 4> Board::getRow(size_t i) {
	std::array<uint64_t, 4> output;
	size_t startIndex = i * width;
	for (size_t i = 0; i < 4; i++) {
		output[i] = tiles[startIndex + i];
	}
	return output;
}

std::array<uint64_t, 4> Board::getColumn(size_t i) {
	array<uint64_t, 4> output;
	for (size_t j = 0; j < height; j++) {
		output[j] = tiles[j * width + i];
	}
	return output;
};

void Board::doMove(Direction direction) {
	bool moved = false;
	size_t size;
	if (direction == Direction::Up || direction == Direction::Down) {
		size = height;
	} else {
		size = width;
	}
	for (size_t i = 0; i < size; i++) {
		array<uint64_t, 4> line;
		if (direction == Direction::Up || direction == Direction::Down) {
			line = getColumn(i);
		} else {
			line = getRow(i);
		}
		if (direction == Direction::Down || direction == Direction::Right) {
			reverseArray(line);
		}
		array<uint64_t, 4> mergedLine = mergeLine(line);
		if (direction == Direction::Down || direction == Direction::Right) {
			reverseArray(mergedLine);
		}
		for (size_t j = 0; j < size; j++) {
			size_t index;
			if (direction == Direction::Up || direction == Direction::Down) {
				index = j * width + i;
			} else {
				index = i * width + j;
			}
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
