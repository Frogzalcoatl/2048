#pragma once
#include "2048/ui/screens/base.hpp"
#include <functional>

class MenuScreen : public UIScreen {
private:
    std::function<void()> onQuit;

public:
    MenuScreen(sf::RenderWindow& window, std::function<void()> onPlay, std::function<void()> onQuit);
    void handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
};