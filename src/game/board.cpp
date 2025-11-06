#include <array>
using namespace std;

class Board {
    public:
	array<array<uint64_t, 4>, 4> tiles = {{
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	}};

	void moveRight() {
		for (int i = 0; i < 4; i++) {
			for (int j = 3; j >= 0; j--) {
				if (tiles[i][j] != 0) {
					int k = j;
				}
			}
		}
	}
    void moveLeft() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] != 0) {
                    int k = j;
                }
            }
        }
    }
    void moveUp() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] != 0) {
                    int k = j;
                }
            }
        }
    }
    void moveDown() {
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {
                if (tiles[i][j] != 0) {
                    int k = j;
                }
            }
        }
    }

    void addRandomTile() {
        int emptyTiles = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] == 0) {
                    emptyTiles++;
                }
            }
        }
        if (emptyTiles == 0) {
            return;
        }
        int randomTile = rand() % emptyTiles;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] == 0) {
                    randomTile--;
                    if (randomTile == 0) {
                        tiles[i][j] = 2;
                        return;
                    }
                }
            }
        }
        tiles[rand() % 4][rand() % 4] = 2;
    }
    bool checkGameOver() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
    bool checkGameWon() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (tiles[i][j] == 2048) {
                    return true;
                }
            }
        }
    }
};