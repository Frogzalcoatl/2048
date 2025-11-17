#include "2048/ui/button.hpp"
using namespace std;

Button::Button(
	function<ScreenResult()> onClick, sf::Vector2f& pos, const UIElementColorParams& normalColors, const UIElementColorParams& hoveredColors, const UIElementColorParams& clickedColors, 
	optional<UIElementTextParams> textParams, optional<sf::RectangleShape> background
) : UIElement(pos, normalColors, textParams, background), onClick(onClick), normal(normalColors), hovered(hoveredColors), clicked(clickedColors) {}

void Button::updateColors(UIElementColorParams& colors) {
	if (background.has_value()) {
		if (colors.background.has_value()) {
			background->setFillColor(*colors.background);
		} else {
			background->setFillColor(sf::Color::White);
		}
	}
	if (text.has_value()) {
		if (colors.text.has_value()) {
			text->setFillColor(*colors.text);
		} else {
			text->setFillColor(sf::Color::Magenta);
		}
	}
}

ScreenResult Button::update(MouseInput& mouseInput, sf::RenderWindow& window) {
	sf::FloatRect elementBounds;
	if (background.has_value()) {
		elementBounds = background->getGlobalBounds();
	} else if (text.has_value()) {
		elementBounds = text->getGlobalBounds();
	} else {
		return ScreenResult{};
	}
	sf::Vector2i mousePos = mouseInput.getPos();
	bool mouseIsWithinBounds = elementBounds.contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)});
	if (mouseIsWithinBounds) {
		window.setMouseCursor(cursorHovered);
	}
	bool leftClickPressed = mouseInput.isLeftClickDown();
	bool leftClickReleased = mouseInput.wasLeftClickReleased();
	if (mouseIsWithinBounds) {
		window.setMouseCursor(cursorHovered);
		bool leftClickPressed = mouseInput.isLeftClickDown();
		bool leftClickReleased = mouseInput.wasLeftClickReleased();
		if (leftClickPressed) {
			updateColors(clicked);
		} else {
			updateColors(hovered);
		}
		if (leftClickReleased) {
			return onClick();
		}
	} else {
		updateColors(normal);
	}
	return ScreenResult{};
}