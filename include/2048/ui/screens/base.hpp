#pragma once
#include "2048/ui/screens/abstract.hpp"

class UIScreen : public UIScreenAbstract {
public:
	virtual InputActionResult draw(MouseInput& mouseInput, sf::RenderWindow& window) override;
    virtual InputActionResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
};