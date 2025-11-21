#pragma once
#include <SFML/Graphics.hpp>
#include "2048/ui/element.hpp"
#include <vector>
#include <memory>

enum UIScreenTypes {
	Menu,
	Game
};

class UIScreenAbstract {
public:
    virtual ~UIScreenAbstract() = default;

	virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleKeyboardInput(sf::Keyboard::Scancode scancode) = 0;
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    std::vector<std::unique_ptr<UIElement>> elements;
};