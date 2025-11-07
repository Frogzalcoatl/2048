#pragma once
#include <optional>
#include <unordered_map>
#include <functional>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "2048/game/board.h"

class KeyboardInput {
private:
	bool keyPressFunctionRunThisFrame = false;

	std::unordered_map<sf::Keyboard::Scancode, bool> pressedLastFrame = {
	    {sf::Keyboard::Scancode::P, false},
	    {sf::Keyboard::Scancode::Up, false},
	    {sf::Keyboard::Scancode::W, false},
	    {sf::Keyboard::Scancode::Down, false},
	    {sf::Keyboard::Scancode::S, false},
	    {sf::Keyboard::Scancode::Right, false},
	    {sf::Keyboard::Scancode::D, false},
	    {sf::Keyboard::Scancode::Left, false},
	    {sf::Keyboard::Scancode::A, false}};

	std::unordered_map<sf::Keyboard::Scancode, std::function<void()>> keyPressFunctions = {
	    {sf::Keyboard::Scancode::P, []() {
		     board.clear();
		     board.populate();
	     }},
	    {sf::Keyboard::Scancode::Up, []() { board.moveUp(); }},
	    {sf::Keyboard::Scancode::W, []() { board.moveUp(); }},
	    {sf::Keyboard::Scancode::Down, []() { board.moveDown(); }},
	    {sf::Keyboard::Scancode::S, []() { board.moveDown(); }},
	    {sf::Keyboard::Scancode::Right, []() { board.moveRight(); }},
	    {sf::Keyboard::Scancode::D, []() { board.moveRight(); }},
	    {sf::Keyboard::Scancode::Left, []() { board.moveLeft(); }},
	    {sf::Keyboard::Scancode::A, []() { board.moveLeft(); }}};

public:
	void update();
};
extern KeyboardInput keyboardInput;