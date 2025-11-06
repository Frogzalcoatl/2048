#include <array>
using namespace std;

class Board {
	array<array<uint64_t, 4>, 4> tiles = {{
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	    {0, 0, 0, 0},
	}};
	void populate();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};