#pragma once
#include <functional>
#include <optional>
#include <SFML/Graphics.hpp>
#include "2048/ui/element.hpp"
#include "2048/input/mouse.hpp"
#include "2048/ui/screens/base.hpp"

class Button : public UIElement {
public:
	Button(
		std::function<InputActionResult()> onClick, const sf::Vector2f& pos, const UIElementColorParams& normalColors, const UIElementColorParams& hoveredColors, const UIElementColorParams& clickedColors,
		std::optional<UIElementTextParams> textParams, std::optional<sf::RectangleShape> background = std::nullopt
	);
	InputActionResult update(MouseInput& mouseInput, sf::RenderWindow& window);

private:
	std::function<InputActionResult()> onClick;
	UIElementColorParams normal;
	UIElementColorParams hovered;
	UIElementColorParams clicked;
	void updateColors(UIElementColorParams& colors);
};