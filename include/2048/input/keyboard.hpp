#pragma once
#include <optional>
#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game2048;

class KeyboardManager {
private:
	std::unordered_map<sf::Keyboard::Scancode, bool> isPressed;

public:
	std::optional<sf::Keyboard::Scancode> pressedEvent(const sf::Event::KeyPressed* keyPressed);
	void releasedEvent(const sf::Event::KeyReleased* keyReleased);
};