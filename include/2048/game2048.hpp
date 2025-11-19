#pragma once
#include "2048/game/board.hpp"
#include "2048/input/keyboard.hpp"
#include "2048/input/mouse.hpp"
#include "2048/ui/screens/base.hpp"
#include "2048/ui/windowManager.hpp"
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
	void handleInputResult(InputActionResult result);
	WindowManager2048 windowManager;
	Board board;
	KeyboardInput keyboardInput;
	MouseInput mouseInput;
	std::unique_ptr<UIScreen> currentUIScreen;
	sf::Color backgroundColor;
};