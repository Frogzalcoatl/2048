#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"
#include <iostream>

using namespace std;

int main() {
	try {
		Game2048 game{4, 4};
		game.run();
	} catch (runtime_error& e) {
		cerr << e.what() << endl;
		return 1;
	} catch (...) {
		cerr << "Unknown error occured." << endl;
		return 1;
	}
}
