#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"
#include "2048/ui/screens/menu.hpp"
#include "2048/ui/screens/game.hpp"
using namespace std;

Game2048::Game2048(size_t boardWidth, size_t boardHeight)
    : board{boardWidth, boardHeight, 2}, backgroundColor{0xFAF8EFFF},
	windowManager{}, keyboardInput{}, mouseInput{} {
	assets.loadAll();
	windowManager.applyWindowSettings(assets);
	setUIScreen(UIScreenTypes::Menu);
	//assets.loadMusic("./assets/music/moog_city.ogg");
	//assets.playMusic();
}

void Game2048::run() {
	while (windowManager.window.isOpen()) {
		while (const optional event = windowManager.window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				windowManager.window.close();
			} else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				auto keyPressedThisTick = keyboardInput.pressed(keyPressed);
				if (keyPressedThisTick.has_value()) {
					handleKeyboardInput(*keyPressedThisTick);
				}
			} else if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>()) {
				keyboardInput.released(keyReleased);
			} else if (const auto resized = event->getIf<sf::Event::Resized>()) {
				windowManager.handleResize();
			}
		}
		mouseInput.update(windowManager.window);
		windowManager.window.clear(backgroundColor);
		draw();
		windowManager.window.display();
	}
}

void Game2048::close() {
	windowManager.window.close();
}

void Game2048::setUIScreen(UIScreenTypes screen) {
	switch (screen) {
		case UIScreenTypes::Menu: {
			currentUIScreen = make_unique<MenuScreen>(assets, windowManager.window);
		}; break;
		case UIScreenTypes::Game: {
			currentUIScreen = make_unique<GameScreen>(assets, windowManager.window, board);
		}; break;
	}
}

void Game2048::draw() {
	auto screen = currentUIScreen.get();
	InputActionResult result = screen->draw(mouseInput, windowManager.window);
	handleInputResult(result);
}

void Game2048::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
	InputActionResult result = currentUIScreen.get()->handleKeyboardInput(scancode);
	handleInputResult(result);
}

void Game2048::handleInputResult(InputActionResult result) {
	GameScreen* gameScreen = dynamic_cast<GameScreen*>(currentUIScreen.get());
	if (result.action == InputAction::ExitGame) {
		windowManager.window.close();
	}
	if (result.action == InputAction::ChangeScreen && result.screenType.has_value()) {
		setUIScreen(*result.screenType);
		if (GameScreen* gameScreen = dynamic_cast<GameScreen*>(currentUIScreen.get())) {
			gameScreen->setScore(board.getScore());
		}
	}
	if (result.action == InputAction::ResetGame) {
		board.reset();
		board.populate();
		board.populate();
	}
	if (result.action == InputAction::UpdateScore || result.action == InputAction::ResetGame) {
		if (GameScreen* gameScreen = dynamic_cast<GameScreen*>(currentUIScreen.get())) {
			gameScreen->setScore(board.getScore());
		}
	}
	if (result.action == InputAction::ToggleFullscreen) {
		windowManager.toggleFullScreen(assets);
	}
}