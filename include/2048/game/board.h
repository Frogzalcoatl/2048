#pragma once
#include <array>
#include <vector>
#include <SFML/System/String.hpp>

class Board {
public:
	bool populate();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	sf::String getTestString();
	void clear();

private:
	std::array<std::array<uint64_t, 4>, 4> tiles = {{
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	}};
	bool fillRandomEmptyTile(std::vector<std::array<int, 2>>& emptyTileIndexes);
};
extern Board board;