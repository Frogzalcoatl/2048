#pragma once
#include <SFML/Graphics.hpp>

struct GameAssets {
	sf::Font boldFont;
	sf::Font regularFont;
	sf::Image icon;
	void loadAll();
};