#pragma once
#include <optional>
#include <unordered_map>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "2048/game/board.h"

class KeyboardInput {
private:
	std::unordered_map<sf::Keyboard::Scancode, bool> isPressed = {
	    {sf::Keyboard::Scancode::R, false},
	    {sf::Keyboard::Scancode::Up, false},
	    {sf::Keyboard::Scancode::W, false},
	    {sf::Keyboard::Scancode::Down, false},
	    {sf::Keyboard::Scancode::S, false},
	    {sf::Keyboard::Scancode::Right, false},
	    {sf::Keyboard::Scancode::D, false},
	    {sf::Keyboard::Scancode::Left, false},
	    {sf::Keyboard::Scancode::A, false}};

	void runScancode(const sf::Keyboard::Scancode scancode);

public:
	void pressed(std::optional<const sf::Event::KeyPressed*> keyPressed);
	void released(std::optional<const sf::Event::KeyReleased*> keyReleased);
};
extern KeyboardInput keyboardInput;