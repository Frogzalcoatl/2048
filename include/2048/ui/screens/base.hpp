#pragma once
#include "2048/ui/screens/abstract.hpp"

class UIScreen : public UIScreenAbstract {
public:
	virtual ScreenResult draw(MouseInput& mouseInput, sf::RenderWindow& window) override;
    virtual ScreenResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override = 0;
};