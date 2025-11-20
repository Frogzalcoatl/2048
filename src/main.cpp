#include "2048/game2048.hpp"
#include <iostream>

using namespace std;

int main() {
	Game2048* game = nullptr;
	try {
		game = new Game2048{4, 4};
		game->run();
	} catch (runtime_error& e) {
		cerr << e.what() << endl;
		if (game) {
			delete game;
		}
		return 1;
	} catch (...) {
		cerr << "Unknown error occured." << endl;
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
