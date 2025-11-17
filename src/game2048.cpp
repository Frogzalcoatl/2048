#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"
#include "2048/ui/screens/menu.hpp"
#include "2048/ui/screens/game.hpp"
using namespace std;

Game2048::Game2048(size_t boardWidth, size_t boardHeight)
    : window{sf::VideoMode::getDesktopMode(), "2048", sf::Style::None}, board{boardWidth, boardHeight, 2}, keyboardInput{}, mouseInput{} {
	assets.loadAll();
	window.setVerticalSyncEnabled(true);
	setUIScreen(UIScreenTypes::Menu);
}

void Game2048::run() {
	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				auto keyPressedThisTick = keyboardInput.pressed(keyPressed);
				if (keyPressedThisTick.has_value()) {
					handleKeyboardInput(*keyPressedThisTick);
				}
			} else if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>()) {
				keyboardInput.released(keyReleased);
			}
		}
		mouseInput.update();
		window.clear();
		draw();
		window.display();
	}
}

void Game2048::close() {
	window.close();
}

void Game2048::setUIScreen(UIScreenTypes screen) {
	switch (screen) {
		case UIScreenTypes::Menu: {
			currentUIScreen = make_unique<MenuScreen>(assets, window);
		}; break;
		case UIScreenTypes::Game: {
			currentUIScreen = make_unique<GameScreen>(assets, window, board);
		}; break;
	}
}

void Game2048::draw() {
	auto screen = currentUIScreen.get();
	ScreenResult result = screen->draw(mouseInput, window);
	handleScreenResult(result);
}

void Game2048::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
	ScreenResult result = currentUIScreen.get()->handleKeyboardInput(scancode);
	handleScreenResult(result);
}

void Game2048::handleScreenResult(ScreenResult result) {
	if (result.action == ScreenAction::ExitGame) {
		window.close();
	}
	if (result.action == ScreenAction::ChangeScreen && result.type.has_value()) {
		setUIScreen(*result.type);
	}
	if (result.action == ScreenAction::ResetGame) {
		board.reset();
		board.populate();
		board.populate();
	}
}