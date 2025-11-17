#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"

using namespace std;

int main() {
	Game2048 game{4, 4};
	game.run();
}
