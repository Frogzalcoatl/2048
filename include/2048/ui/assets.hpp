#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

namespace Assets2048 {
	extern sf::Font boldFont;
	extern sf::Font regularFont;
	extern sf::Image icon;
	extern std::unique_ptr<sf::Music> backgroundMusic;
	void loadAll();

	void loadMusic(const std::string& filepath);
	void playMusic();
	void stopMusic();
	bool isMusicPlaying();
};