#include "2048/ui/assets.hpp"
#include <iostream>
using namespace std;

namespace Assets2048 {
    sf::Font boldFont;
    sf::Font regularFont;
    sf::Image icon;
    unique_ptr<sf::Music> backgroundMusic;
    void loadAll() {
        if (
            !boldFont.openFromFile("./assets/fonts/ClearSans-Bold.ttf") ||
            !regularFont.openFromFile("./assets/fonts/ClearSans-Regular.ttf") ||
            !icon.loadFromFile("./assets/images/2048.png")
        ) {
            // Throws if the two fonts dont load.
			// This realistically should never happen unless the assets directory is deleted for whatever reason.
            throw runtime_error("Unable to load assets.");
        }
    }
    void loadMusic(const string& filePath) {
        backgroundMusic = make_unique<sf::Music>();
        if (!backgroundMusic->openFromFile(filePath)) {
            cerr << "Warning: Could not load music from " << filePath << "." << endl;
            backgroundMusic.reset();
        }
    }
    void playMusic() {
        if (backgroundMusic) {
            backgroundMusic->setLooping(true);
            backgroundMusic->play();
        }
    }
    void stopMusic() {
        if (backgroundMusic) {
            backgroundMusic->stop();
        }
    }
    bool isMusicPlaying() {
        return backgroundMusic && backgroundMusic->getStatus() == sf::SoundSource::Status::Playing;
    }
}