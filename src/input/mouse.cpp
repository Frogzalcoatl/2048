#include <SFML/Window/Mouse.hpp>
#include "2048/input/Mouse.hpp"
using namespace std;

void MouseInput::update() {
	pos = sf::Mouse::getPosition();
	bool leftClickDownLastTick = leftClickDown;
	leftClickDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	if (leftClickDownLastTick && !leftClickDown) {
		leftClickReleased = true;
	} else {
		leftClickReleased = false;
	}
}

sf::Vector2i MouseInput::getPos() {
	return pos;
}

bool MouseInput::isLeftClickDown() {
	return leftClickDown;
}

bool MouseInput::wasLeftClickReleased() {
	return leftClickReleased;
}