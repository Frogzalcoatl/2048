#pragma once
#include <vector>
#include <SFML/System/String.hpp>

enum Direction {
	Up = 1,
	Down = 2,
	Right = 3,
	Left = 4
};

class Board {
public:
	const size_t width;
	const size_t height;
	Board(size_t width, size_t height);
	Board(size_t width, size_t height, size_t prefill);
	bool populate();
	void doMove(Direction direction);
	void reset();
	const std::vector<uint64_t>& getTiles() const;
	bool isGameOver();
	sf::String getDebugString();
	void testFill();

private:
	std::vector<uint64_t> tiles;
	std::vector<uint64_t> mergeLine(const std::vector<uint64_t>& line);
	std::vector<uint64_t> getRow(size_t i);
	std::vector<uint64_t> getColumn(size_t i);
};