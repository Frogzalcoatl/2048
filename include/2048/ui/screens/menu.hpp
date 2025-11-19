#pragma once
#include "2048/ui/assets.hpp"
#include "2048/ui/screens/base.hpp"
#include "2048/input/mouse.hpp"
#include "2048/ui/button.hpp"

class MenuScreen : public UIScreen {
public:
    MenuScreen(const GameAssets& assets, sf::RenderWindow& window);
    ScreenResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
    UIElement title;
    UIElement buttonBackground;
    Button playButton;
    Button quitButton;
private:
    const sf::Vector2f buttonSize = {400.f, 75.f};
};