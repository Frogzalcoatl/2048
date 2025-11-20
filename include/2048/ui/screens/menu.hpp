#pragma once
#include "2048/ui/screens/base.hpp"

class MenuScreen : public UIScreen {
public:
    MenuScreen(sf::RenderWindow& window);
    InputActionResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
};