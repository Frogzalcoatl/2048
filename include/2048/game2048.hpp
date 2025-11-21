#pragma once
#include "2048/game/board.hpp"
#include "2048/input/keyboard.hpp"
#include "2048/ui/screens/base.hpp"
#include "2048/ui/windowManager.hpp"
#include <memory>
#include <optional>

class Game2048 {
public:
	~Game2048();
	Game2048(size_t boardWidth, size_t boardHeight);
	void run();
	void performScreenSwitch(UIScreenTypes screen);

private:
	void draw();
	void handleKeyboardInput(sf::Keyboard::Scancode scancode);
	WindowManager2048 windowManager;
	Board board;
	KeyboardManager keyboardManager;
	std::unique_ptr<UIScreen> currentUIScreen;
	sf::Color backgroundColor;
	std::optional<UIScreenTypes> nextScreen;
	void requestScreenSwitch(UIScreenTypes screen);
};