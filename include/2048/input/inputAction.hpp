#pragma once
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