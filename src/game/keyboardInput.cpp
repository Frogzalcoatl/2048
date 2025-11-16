#include <SFML/Window/Keyboard.hpp>
#include "2048/game/keyboardInput.hpp"
#include <iostream>
using namespace std;

void KeyboardInput::pressed(const sf::Event::KeyPressed* keyPressed, Board* board) {
	const sf::Keyboard::Scancode scancode = keyPressed->scancode;
	if (!isPressed.count(scancode)) {
		return;
	}
	if (!isPressed[scancode]) {
		runScancode(scancode, board);
	}
	isPressed[scancode] = true;
}

void KeyboardInput::released(const sf::Event::KeyReleased* keyReleased) {
	const sf::Keyboard::Scancode scancode = keyReleased->scancode;
	if (!isPressed.count(scancode)) {
		return;
	}
	isPressed[scancode] = false;
}

void KeyboardInput::runScancode(const sf::Keyboard::Scancode scancode, Board* board) {
	switch (scancode) {
		case sf::Keyboard::Scancode::F: {
			board->testFill();
			cout << "testFill run" << endl;
		}; break;
		case sf::Keyboard::Scancode::T: {
			cout << boolalpha << board->isGameOver() << endl;
		}; break;
		case sf::Keyboard::Scancode::R: {
			board->reset();
			board->populate();
			board->populate();
		}; break;
		case sf::Keyboard::Scancode::Up:
		case sf::Keyboard::Scancode::W: {
			board->doMove(Direction::Up);
		}; break;
		case sf::Keyboard::Scancode::Down:
		case sf::Keyboard::Scancode::S: {
			board->doMove(Direction::Down);
		}; break;
		case sf::Keyboard::Scancode::Right:
		case sf::Keyboard::Scancode::D: {
			board->doMove(Direction::Right);
		}; break;
		case sf::Keyboard::Scancode::Left:
		case sf::Keyboard::Scancode::A: {
			board->doMove(Direction::Left);
		}; break;
	}
}