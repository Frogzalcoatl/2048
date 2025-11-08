#include <SFML/Window/Keyboard.hpp>
#include "2048/game/keyboardInput.h"
#include "2048/game/board.h"
using namespace std;

KeyboardInput keyboardInput;

void KeyboardInput::pressed(std::optional<const sf::Event::KeyPressed*> keyPressed) {
	if (!keyPressed.has_value()) {
		return;
	}
	const sf::Keyboard::Scancode scancode = keyPressed.value()->scancode;
	if (!isPressed.count(scancode)) {
		return;
	}
	if (!isPressed[scancode]) {
		runScancode(scancode);
	}
	isPressed[scancode] = true;
}

void KeyboardInput::released(std::optional<const sf::Event::KeyReleased*> keyReleased) {
	if (!keyReleased.has_value()) {
		return;
	}
	const sf::Keyboard::Scancode scancode = keyReleased.value()->scancode;
	if (!isPressed.count(scancode)) {
		return;
	}
	isPressed[scancode] = false;
}

void KeyboardInput::runScancode(const sf::Keyboard::Scancode scancode) {
	switch (scancode) {
		case sf::Keyboard::Scancode::R: {
			board.clear();
			board.populate();
		}; break;
		case sf::Keyboard::Scancode::Up:
		case sf::Keyboard::Scancode::W: {
			board.moveUp();
		}; break;
		case sf::Keyboard::Scancode::Down:
		case sf::Keyboard::Scancode::S: {
			board.moveDown();
		}; break;
		case sf::Keyboard::Scancode::Right:
		case sf::Keyboard::Scancode::D: {
			board.moveRight();
		}; break;
		case sf::Keyboard::Scancode::Left:
		case sf::Keyboard::Scancode::A: {
			board.moveLeft();
		}; break;
	}
}