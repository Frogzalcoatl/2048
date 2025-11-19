#pragma once
#include "2048/game/board.hpp"
#include "2048/input/keyboard.hpp"
#include "2048/input/mouse.hpp"
#include "2048/ui/assets.hpp"
#include "2048/ui/screens/base.hpp"
#include <memory>

class Game2048 {
public:
	~Game2048() {}
	Game2048(size_t boardWidth, size_t boardHeight);
	void run();
	void close();

private:
	void setUIScreen(UIScreenTypes screen);
	void draw();
	void handleKeyboardInput(sf::Keyboard::Scancode scancode);
	void handleScreenResult(InputActionResult result);
	void applyWindowSettings();
	void toggleFullScreen();
	sf::RenderWindow window;
	bool isFullscreen = false;
	sf::Vector2u windowResolutionBeforeFullscreen = {0, 0};
	sf::Vector2i windowPositionBeforeFullscreen = {0, 0};
	Board board;
	KeyboardInput keyboardInput;
	MouseInput mouseInput;
	GameAssets assets;
	std::unique_ptr<UIScreen> currentUIScreen;
	sf::Color backgroundColor;
};