#pragma once
#include <vector>
#include <cstdint>

enum Direction {
	Up,
	Down,
	Right,
	Left
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
	const std::vector<std::uint64_t>& getTiles() const;
	void updateGameOverStatus();
	bool getGameOverStatus();
	std::uint64_t getScore();

private:
	bool gameOverStatus = false;
	std::vector<std::uint64_t> tiles;
	std::vector<std::uint64_t> mergeLine(const std::vector<std::uint64_t>& line);
	std::vector<std::uint64_t> getRow(size_t i);
	std::vector<std::uint64_t> getColumn(size_t i);
};