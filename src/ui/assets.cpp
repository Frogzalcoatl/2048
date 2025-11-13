#include "2048/ui/assets.hpp"

void GameAssets::loadAll() {
	if (!boldFont.openFromFile(".\\assets\\fonts\\ClearSans-Bold.ttf") || !regularFont.openFromFile(".\\assets\\fonts\\ClearSans-Regular.ttf")) {
		// Terminates the program if the two fonts dont load.
		exit(1);
	}
}