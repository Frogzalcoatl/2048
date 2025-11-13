#pragma once
#include <SFML/Graphics.hpp>

namespace Graphics2048 {
	class TileButton {
	public:
		static const sf::Color textColor;
		sf::Font* font;
		std::string text;
		sf::Color backgroundColor;
	};
};