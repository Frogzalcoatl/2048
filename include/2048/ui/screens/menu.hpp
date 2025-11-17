#pragma once
#include "2048/ui/assets.hpp"
#include "2048/ui/screens/base.hpp"
#include "2048/input/mouse.hpp"

class MenuScreen : public UIScreen {
public:
    MenuScreen(const GameAssets& assets, sf::RenderWindow& window);
    ScreenResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
};