#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"
#include "2048/ui/screens/menu.hpp"
#include "2048/ui/screens/game.hpp"
#include "2048/ui/cursorManager.hpp"

Game2048::~Game2048() {
	board.saveData();
}

Game2048::Game2048(size_t boardWidth, size_t boardHeight)
    : board{boardWidth, boardHeight, 2}, backgroundColor{0xFAF8EFFF},
	windowManager{} {
	windowManager.applyWindowSettings();
	performScreenSwitch(UIScreenTypes::Menu);
	// Assets2048::loadMusic("./assets/music/moog_city.ogg");
	// Assets2048::playMusic();
}

void Game2048::run() {
	while (windowManager.window.isOpen()) {
		while (const std::optional event = windowManager.window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				windowManager.window.close();
			} else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				handleKeyboardInput(keyPressed->scancode);
			} else if (const auto resized = event->getIf<sf::Event::Resized>()) {
				windowManager.handleResize();
			}
			if (currentUIScreen) {
				currentUIScreen->handleEvent(*event, windowManager.window);
			}
		}
		if (nextScreen.has_value()) {
			performScreenSwitch(*nextScreen);
			nextScreen = std::nullopt;
		}
		windowManager.window.clear(backgroundColor);
		draw();
		windowManager.window.display();
	}
}

void Game2048::requestScreenSwitch(UIScreenTypes screen) {
	nextScreen = screen;
}

void Game2048::performScreenSwitch(UIScreenTypes screen) {
	switch (screen) {
		case UIScreenTypes::Menu: {
			currentUIScreen = std::make_unique<MenuScreen>(
				windowManager.window,
				// play button
				[this]() {
					this->requestScreenSwitch(UIScreenTypes::Game);
					this->windowManager.window.setMouseCursor(CursorManager::getCursor(sf::Cursor::Type::Arrow));
				},
				// quit button
				[this]() {
					this->windowManager.window.close();
				}
			);
		}; break;
		case UIScreenTypes::Game: {
			currentUIScreen = std::make_unique<GameScreen>(
				windowManager.window, board,
				// back button
				[this]() {
					this->requestScreenSwitch(UIScreenTypes::Menu);
					this->windowManager.window.setMouseCursor(CursorManager::getCursor(sf::Cursor::Type::Arrow));
				},
				// new game button
				[this]() {
					this->requestScreenSwitch(UIScreenTypes::Game);
					this->board.reset();
				}
			);
		}; break;
	}
}

void Game2048::draw() {
	if (currentUIScreen) {
		currentUIScreen->draw(windowManager.window);
	}
}

void Game2048::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
	if (scancode == sf::Keyboard::Scancode::F11) {
		windowManager.toggleFullScreen();
		return;
	}
	if (currentUIScreen) {
		currentUIScreen->handleKeyboardInput(scancode);
	}
}