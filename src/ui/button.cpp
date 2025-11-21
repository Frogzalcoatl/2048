#include "2048/ui/button.hpp"
#include "2048/ui/cursorManager.hpp"
using namespace std;

Button::Button(
	function<void()> onClick, const sf::Vector2f& pos, const UIElementColorParams& normalColors, const UIElementColorParams& hoveredColors, const UIElementColorParams& clickedColors, 
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

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
	if (event.is<sf::Event::MouseMoved>()) {
		sf::Vector2i mousePos = {event.getIf<sf::Event::MouseMoved>()->position.x, event.getIf<sf::Event::MouseMoved>()->position.y};
    	sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		sf::FloatRect elementBounds;
		if (background.has_value()) {
			elementBounds = background->getGlobalBounds();
		} else if (text.has_value()) {
			elementBounds = text->getGlobalBounds();
		} else {
			return;
		}
		bool currentlyHovered = elementBounds.contains(worldPos);
		if (currentlyHovered != isHovered) {
			isHovered = currentlyHovered;
			if (isHovered) {
				updateColors(hovered);
				window.setMouseCursor(CursorManager::getCursor(sf::Cursor::Type::Hand));
			} else {
				updateColors(normal);
				window.setMouseCursor(CursorManager::getCursor(sf::Cursor::Type::Arrow));
				isPressed = false;
			}
		}
	}
	if (event.is<sf::Event::MouseButtonPressed>()) {
        if (event.getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left && isHovered) {
            isPressed = true;
            updateColors(clicked);
        }
    }
	if (event.is<sf::Event::MouseButtonReleased>()) {
        if (event.getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left) {		
			bool wasPressed = isPressed;
			isPressed = false;
			if (wasPressed && isHovered) {
				isPressed = false;
                updateColors(hovered);
                onClick();
				return;
            }
        }
    }
}