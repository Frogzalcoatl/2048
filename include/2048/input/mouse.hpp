#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MouseInput {
private:
	bool leftClickDown = false;
	bool leftClickReleased = false;
	sf::Vector2i mousePos = {0, 0};

public:
	void update(sf::RenderWindow& window);
	sf::Vector2i getPos();
	bool isLeftClickDown();
	bool wasLeftClickReleased();
};