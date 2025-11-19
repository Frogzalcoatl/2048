#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"
#include "2048/ui/screens/menu.hpp"
#include "2048/ui/screens/game.hpp"
using namespace std;

Game2048::Game2048(size_t boardWidth, size_t boardHeight)
    : window{sf::VideoMode::getDesktopMode(), "2048", sf::Style::Titlebar | sf::Style::Close}, board{boardWidth, boardHeight, 2},
	backgroundColor{0xFAF8EFFF}, keyboardInput{}, mouseInput{} {
	assets.loadAll();
	window.setIcon(assets.icon);
	window.setVerticalSyncEnabled(true);
	setUIScreen(UIScreenTypes::Menu);
	assets.loadMusic("./assets/music/moog_city.ogg");
	assets.playMusic();
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
			} else if (const auto resized = event->getIf<sf::Event::Resized>()) {
    			const sf::Vector2f designResolution(1920.f, 1080.f);
    			float windowWidth = static_cast<float>(resized->size.x);
    			float windowHeight = static_cast<float>(resized->size.y);
    			float designAspectRatio = designResolution.x / designResolution.y;
    			float windowAspectRatio = windowWidth / windowHeight;
    			float viewportX = 0.f;
    			float viewportY = 0.f;
    			float viewportWidth = 1.f;
    			float viewportHeight = 1.f;
    			if (windowAspectRatio > designAspectRatio) {
    			    viewportWidth = designAspectRatio / windowAspectRatio;
    			    viewportX = (1.f - viewportWidth) / 2.f;
    			} else if (windowAspectRatio < designAspectRatio) {
    			    viewportHeight = windowAspectRatio / designAspectRatio;
    			    viewportY = (1.f - viewportHeight) / 2.f;
    			}
    			sf::View view(designResolution / 2.f, designResolution);
    			view.setViewport(sf::FloatRect({viewportX, viewportY}, {viewportWidth, viewportHeight}));
    			window.setView(view);
			}
		}
		mouseInput.update(window);
		window.clear(backgroundColor);
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
	GameScreen* gameScreen = dynamic_cast<GameScreen*>(currentUIScreen.get());
	if (result.action == ScreenAction::ExitGame) {
		window.close();
	}
	if (result.action == ScreenAction::ChangeScreen && result.type.has_value()) {
		setUIScreen(*result.type);
		if (GameScreen* gameScreen = dynamic_cast<GameScreen*>(currentUIScreen.get())) {
			gameScreen->setScore(board.getScore());
		}
	}
	if (result.action == ScreenAction::ResetGame) {
		board.reset();
		board.populate();
		board.populate();
	}
	if (result.action == ScreenAction::UpdateScore || result.action == ScreenAction::ResetGame) {
		if (GameScreen* gameScreen = dynamic_cast<GameScreen*>(currentUIScreen.get())) {
			gameScreen->setScore(board.getScore());
		}
	}
}