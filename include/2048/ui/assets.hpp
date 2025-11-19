#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>




struct GameAssets {
	sf::Font boldFont;
	sf::Font regularFont;
	sf::Image icon;

	std::unique_ptr<sf::Music> backgroundMusic;
	void loadAll();

	void loadMusic(const std::string& filepath);
	void playMusic();
	void stopMusic();
	bool isMusicPlaying() const;
};