#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class MouseInput {
private:
	bool leftClickDown = false;
	bool leftClickReleased = false;
	sf::Vector2i mousePos = {0, 0};
	sf::Cursor::Type currentCursorType = sf::Cursor::Type::Arrow;
	sf::Cursor::Type requestedCursorType = sf::Cursor::Type::Arrow;
	void resetCursorRequest();
	sf::Cursor& getSystemCursor(sf::Cursor::Type type);

public:
	void update(sf::RenderWindow& window);
	sf::Vector2i getPos();
	bool isLeftClickDown();
	bool wasLeftClickReleased();
	void requestCursor(const sf::Cursor::Type cursorType);
};