#pragma once
#include <optional>
#include <unordered_map>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

class Game2048;

class KeyboardInput {
private:
	std::unordered_map<sf::Keyboard::Scancode, bool> isPressed = {
		{sf::Keyboard::Scancode::Escape, false},
	    {sf::Keyboard::Scancode::Up, false},
	    {sf::Keyboard::Scancode::W, false},
	    {sf::Keyboard::Scancode::Down, false},
	    {sf::Keyboard::Scancode::S, false},
	    {sf::Keyboard::Scancode::Right, false},
	    {sf::Keyboard::Scancode::D, false},
	    {sf::Keyboard::Scancode::Left, false},
	    {sf::Keyboard::Scancode::A, false}};

public:
	std::optional<sf::Keyboard::Scancode> pressed(const sf::Event::KeyPressed* keyPressed);
	void released(const sf::Event::KeyReleased* keyReleased);
};