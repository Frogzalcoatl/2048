#pragma once
#include <SFML/Graphics.hpp>

class WindowManager2048 {
public:
    sf::RenderWindow window;
    WindowManager2048();
    void applyWindowSettings();
	void toggleFullScreen();
    void handleResize();
private:
    bool isFullscreen = false;
	sf::Vector2u windowResolutionBeforeFullscreen = {0, 0};
	sf::Vector2i windowPositionBeforeFullscreen = {0, 0};
};