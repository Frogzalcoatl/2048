#include <SFML/Graphics.hpp>
#include "2048/game2048.hpp"
#include "2048/ui/screens/menu.hpp"
#include "2048/ui/screens/game.hpp"
using namespace std;

static void resizeView(const sf::Window& window, sf::View& view) {
    float windowRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    float viewRatio = 1920.f / 1080.f; // Target 16:9
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
}

Game2048::Game2048(size_t boardWidth, size_t boardHeight)
    : window{sf::VideoMode::getDesktopMode(), "2048", sf::Style::Default}, board{boardWidth, boardHeight, 2},
	backgroundColor{0xFAF8EFFF}, keyboardInput{}, mouseInput{} {
	assets.loadAll();
	window.setIcon(assets.icon);
	window.setVerticalSyncEnabled(true);
	sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
    resizeView(window, view);
    window.setView(view);
	setUIScreen(UIScreenTypes::Menu);
	//assets.loadMusic("./assets/music/moog_city.ogg");
	//assets.playMusic();
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
				sf::View view = window.getView();
                resizeView(window, view);
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