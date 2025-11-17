#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "2048/ui/element.hpp"
#include "2048/input/mouse.hpp"

enum class ScreenAction {
	None,
	ChangeScreen,
	ExitGame,
	ResetGame
};

enum UIScreenTypes {
	Menu,
	Game
};

struct ScreenResult {
	ScreenAction action = ScreenAction::None;
	std::optional<UIScreenTypes> type = std::nullopt;
};

class UIScreenAbstract {
public:
    virtual ~UIScreenAbstract() = default;

	virtual ScreenResult draw(MouseInput& mouseInput, sf::RenderWindow& window) = 0;
    virtual ScreenResult handleKeyboardInput(sf::Keyboard::Scancode scancode) = 0;
    std::vector<std::unique_ptr<UIElement>> elements;
};