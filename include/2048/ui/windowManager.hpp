#pragma once
#include <SFML/Graphics.hpp>
#include "2048/ui/assets.hpp"

class WindowManager2048 {
public:
    sf::RenderWindow window;
    WindowManager2048();
    void applyWindowSettings(GameAssets& assets);
	void toggleFullScreen(GameAssets& assets);
    void handleResize();
private:
    bool isFullscreen = false;
	sf::Vector2u windowResolutionBeforeFullscreen = {0, 0};
	sf::Vector2i windowPositionBeforeFullscreen = {0, 0};
};