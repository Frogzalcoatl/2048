#pragma once
#include "2048/ui/assets.hpp"
#include "2048/ui/screens/base.hpp"
#include "2048/input/mouse.hpp"
#include "2048/ui/button.hpp"

class MenuScreen : public UIScreen {
public:
    MenuScreen(sf::RenderWindow& window);
    InputActionResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
};