#pragma once
#include <vector>
#include <cstdint>
#include <string>

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
	Board(size_t width, size_t height, size_t prefill = 0);
	// Returns amount of empty indexes in tiles.
	size_t populate();
	void doPrefill();
	void doMove(Direction direction);
	void reset();
	const std::vector<uint64_t>& getTiles() const;
	bool getGameOverStatus() const;
	uint64_t getScore() const;
	uint64_t getHighScore() const;
	void saveData();

private:
	bool gameOverStatus = false;
	std::vector<uint64_t> tiles;
	std::vector<uint64_t> mergeLine(const std::vector<uint64_t>& line);
	std::vector<uint64_t> getRow(size_t i);
	std::vector<uint64_t> getColumn(size_t i);
	void updateGameOverStatus(size_t emptyCount);
	void loadBoardFromFile();
	bool isValidTilesVector(const std::vector<uint64_t> tilesVector) const;
	void saveHighScoreToFile() const;
	void saveBoardToFile() const;
	uint64_t cachedHighScore = 0;
};