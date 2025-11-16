#pragma once
#include <optional>
#include <unordered_map>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "2048/game/board.hpp"

class KeyboardInput {
private:
	std::unordered_map<sf::Keyboard::Scancode, bool> isPressed = {
	    {sf::Keyboard::Scancode::F, false},
	    {sf::Keyboard::Scancode::T, false},
	    {sf::Keyboard::Scancode::R, false},
	    {sf::Keyboard::Scancode::Up, false},
	    {sf::Keyboard::Scancode::W, false},
	    {sf::Keyboard::Scancode::Down, false},
	    {sf::Keyboard::Scancode::S, false},
	    {sf::Keyboard::Scancode::Right, false},
	    {sf::Keyboard::Scancode::D, false},
	    {sf::Keyboard::Scancode::Left, false},
	    {sf::Keyboard::Scancode::A, false}};

	void runScancode(const sf::Keyboard::Scancode scancode, Board* board);

public:
	void pressed(const sf::Event::KeyPressed* keyPressed, Board* board);
	void released(const sf::Event::KeyReleased* keyReleased);
};