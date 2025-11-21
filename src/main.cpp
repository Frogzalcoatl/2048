#include "2048/game2048.hpp"
#include <iostream>

int main() {
	Game2048* game = nullptr;
	try {
		game = new Game2048{4, 4};
		game->run();
	} catch (std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		if (game) {
			delete game;
		}
		return 1;
	} catch (...) {
		std::cerr << "Unknown error occured." << std::endl;
		if (game) {
			delete game;
		}
		return 1;
	}
	if (game) {
		delete game;
	}
	return 0;
}
