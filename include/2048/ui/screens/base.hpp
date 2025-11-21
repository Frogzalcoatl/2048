#pragma once
#include "2048/ui/screens/abstract.hpp"

class UIScreen : public UIScreenAbstract {
public:
	virtual void draw(sf::RenderWindow& window) override;
    virtual void handleKeyboardInput(sf::Keyboard::Scancode scancode) override {};
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
};