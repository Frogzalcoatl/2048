#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "2048/ui/element.hpp"
#include "2048/input/inputAction.hpp"
#include <memory>

class UIScreenAbstract {
public:
    virtual ~UIScreenAbstract() = default;

	virtual void draw(sf::RenderWindow& window) = 0;
    virtual InputActionResult handleKeyboardInput(sf::Keyboard::Scancode scancode) = 0;
	virtual InputActionResult handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;
    std::vector<std::unique_ptr<UIElement>> elements;
};