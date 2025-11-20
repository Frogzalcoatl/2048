#include <SFML/Window/Keyboard.hpp>
#include "2048/input/keyboard.hpp"
using namespace std;

optional<sf::Keyboard::Scancode> KeyboardManager::pressedEvent(const sf::Event::KeyPressed* keyPressed) {
	const sf::Keyboard::Scancode scancode = keyPressed->scancode;
	bool wasPressedLastTick = isPressed[scancode];
	isPressed[scancode] = true;
	if (!wasPressedLastTick) {
		return scancode;
	} else {
		return nullopt;
	}
}

void KeyboardManager::releasedEvent(const sf::Event::KeyReleased* keyReleased) {
	const sf::Keyboard::Scancode scancode = keyReleased->scancode;
	if (isPressed.find(scancode) == isPressed.end()) {
		return;
	}
	isPressed[scancode] = false;
}