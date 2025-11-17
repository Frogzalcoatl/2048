#include "2048/ui/assets.hpp"
#include <iostream>

void GameAssets::loadAll() {
	if (
		!boldFont.openFromFile("./assets/fonts/ClearSans-Bold.ttf") ||
		!regularFont.openFromFile("./assets/fonts/ClearSans-Regular.ttf") ||
		!icon.loadFromFile("./assets/images/2048.png")
	) {
		// Terminates the program if the two fonts dont load.
		// This realistically should never happen unless the assets directory is deleted for whatever reason.
		exit(1);
	}
}

void GameAssets::loadMusic(const std::string& filePath) {
	backgroundMusic = std::make_unique<sf::Music>();
	if (!backgroundMusic->openFromFile(filePath)) {
		std::cerr << "Warning: Could not load music from " << filePath << std::endl;
		backgroundMusic.reset();
	}
}

void GameAssets::playMusic() {
	if (backgroundMusic) {
		backgroundMusic->setLooping(true);
		backgroundMusic->play();
	}
}

void GameAssets::stopMusic() {
	if (backgroundMusic) {
		backgroundMusic->stop();
	}
}

bool GameAssets::isMusicPlaying() const {
	return backgroundMusic && backgroundMusic->getStatus() == sf::SoundSource::Status::Playing;
}