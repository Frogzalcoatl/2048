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
	size_t prefill = 0;
	Board(size_t width, size_t height);
	Board(size_t width, size_t height, size_t prefill);
	// Returns amount of empty indexes in tiles.
	size_t populate();
	void doPrefill();
	void doMove(Direction direction);
	void reset();
	const std::vector<uint64_t>& getTiles() const;
	bool getGameOverStatus() const;
	uint64_t getScore() const;

private:
	bool gameOverStatus = false;
	std::vector<uint64_t> tiles;
	std::vector<uint64_t> mergeLine(const std::vector<uint64_t>& line);
	std::vector<uint64_t> getRow(size_t i);
	std::vector<uint64_t> getColumn(size_t i);
	void updateGameOverStatus(size_t emptyCount);
};