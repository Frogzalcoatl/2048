#pragma once
#include <array>
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
	const size_t width = 4;
	const size_t height = 4;
	Board();
	Board(size_t prefill);
	bool populate();
	void doMove(Direction direction);
	void reset();
	sf::String getTestString();

private:
	std::array<uint64_t, 16> tiles;
	std::array<uint64_t, 4> mergeLine(const std::array<uint64_t, 4>& line);
	std::array<uint64_t, 4> getRow(size_t i);
	std::array<uint64_t, 4> getColumn(size_t i);
};