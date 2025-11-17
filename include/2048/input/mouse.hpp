#pragma once
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window.hpp>

class MouseInput {
private:
	bool leftClickDown = false;
	bool leftClickReleased = false;
	sf::Vector2i pos = {0, 0};

public:
	void update();
	sf::Vector2i getPos();
	bool isLeftClickDown();
	bool wasLeftClickReleased();
};