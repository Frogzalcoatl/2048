#include "2048/ui/windowManager.hpp"

WindowManager2048::WindowManager2048()
    : window{sf::VideoMode{{1280, 720}}, "2048", sf::Style::Default} {}

void WindowManager2048::handleResize() {
    sf::View view = window.getView();
    float windowRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    float viewRatio = 1920.f / 1080.f;
    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX = 0.f;
    float posY = 0.f;
    if (windowRatio > viewRatio) {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }
    view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
    window.setView(view);
}

void WindowManager2048::toggleFullScreen(GameAssets& assets) {
	isFullscreen = !isFullscreen;
	if (isFullscreen) {
		windowResolutionBeforeFullscreen = window.getSize();
		windowPositionBeforeFullscreen = window.getPosition();
		window.create(sf::VideoMode::getDesktopMode(), "2048", sf::Style::None, sf::State::Fullscreen);
	} else {
		window.create(sf::VideoMode(windowResolutionBeforeFullscreen), "2048", sf::Style::Default);
		window.setPosition(windowPositionBeforeFullscreen);
	}
	applyWindowSettings(assets);
}

void WindowManager2048::applyWindowSettings(GameAssets& assets) {
	window.setIcon(assets.icon);
	window.setVerticalSyncEnabled(true);
    sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
    window.setView(view);
    handleResize();
}