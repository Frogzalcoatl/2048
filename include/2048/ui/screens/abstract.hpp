#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "2048/ui/element.hpp"
#include "2048/input/mouse.hpp"
#include <memory>
#include <optional>

enum class InputAction {
	None,
	ChangeScreen,
	ExitGame,
	ResetGame,
	UpdateScore,
	ToggleFullscreen
};

enum UIScreenTypes {
	Menu,
	Game
};

struct InputActionResult {
	InputAction action = InputAction::None;
	std::optional<UIScreenTypes> screenType = std::nullopt;
};

class UIScreenAbstract {
public:
    virtual ~UIScreenAbstract() = default;

	virtual InputActionResult draw(MouseInput& mouseInput, sf::RenderWindow& window) = 0;
    virtual InputActionResult handleKeyboardInput(sf::Keyboard::Scancode scancode) = 0;
    std::vector<std::unique_ptr<UIElement>> elements;
};