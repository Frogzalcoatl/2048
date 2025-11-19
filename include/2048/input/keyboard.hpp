#pragma once
#include <optional>
#include <unordered_map>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game2048;

class KeyboardInput {
private:
	std::unordered_map<sf::Keyboard::Scancode, bool> isPressed;

public:
	std::optional<sf::Keyboard::Scancode> pressed(const sf::Event::KeyPressed* keyPressed);
	void released(const sf::Event::KeyReleased* keyReleased);
};