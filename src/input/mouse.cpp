#include <SFML/Window/Mouse.hpp>
#include "2048/input/mouse.hpp"
using namespace std;

void MouseInput::update(sf::RenderWindow& window) {
	sf::Vector2i windowPos = window.getPosition();
	mousePos = sf::Mouse::getPosition();
	mousePos.x -= windowPos.x;
	mousePos.y -= windowPos.y;
	bool leftClickDownLastTick = leftClickDown;
	leftClickDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	if (leftClickDownLastTick && !leftClickDown) {
		leftClickReleased = true;
	} else {
		leftClickReleased = false;
	}
}

sf::Vector2i MouseInput::getPos() {
	return mousePos;
}

bool MouseInput::isLeftClickDown() {
	return leftClickDown;
}

bool MouseInput::wasLeftClickReleased() {
	return leftClickReleased;
}