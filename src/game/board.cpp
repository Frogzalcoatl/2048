#include <iostream>
#include "2048/game/board.h"
#include "2048/game/random.h"
using namespace std;

Board board;

void Board::clear() {
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			tiles[i][j] = 0;
		}
	}
}

bool Board::fillRandomEmptyTile(vector<array<int, 2>>& emptyTileIndexes) {
	if (emptyTileIndexes.size() == 0) {
		return false;
	}
	int randomEmptyTileIndex = getRandomInt(0, emptyTileIndexes.size() - 1);
	tiles[emptyTileIndexes[randomEmptyTileIndex][0]][emptyTileIndexes[randomEmptyTileIndex][1]] = getRandomInt(0, 19) > 3 ? 2 : 4;
	emptyTileIndexes.erase(emptyTileIndexes.begin() + randomEmptyTileIndex);
	return true;
}

bool Board::populate() {
	vector<array<int, 2>> emptyTileIndexes = {};
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] == 0) {
				emptyTileIndexes.push_back({i, j});
			}
		}
	}
	if (!Board::fillRandomEmptyTile(emptyTileIndexes)) {
		return false;
	}
	Board::fillRandomEmptyTile(emptyTileIndexes);
	return true;
}

sf::String Board::getTestString() {
	sf::String str("");
	for (int i = 0; i < tiles.size(); i++) {
		for (int j = 0; j < tiles[i].size(); j++) {
			str.insert(str.getSize(), sf::String(to_string(tiles[i][j]) + " "));
		}
		str.insert(str.getSize(), sf::String("\n"));
	}
	return str;
}

void Board::mergeLine(std::array<uint64_t, 4>& line) {
}

void Board::moveUp() {}

void Board::moveDown() {}

void Board::moveRight() {}

void Board::moveLeft() {
	for (auto& line : tiles) {
		mergeLine(line);
	}
}
