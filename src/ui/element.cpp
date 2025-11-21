#include "2048/ui/element.hpp"
#include <SFML/Graphics.hpp>
#include <exception>

void UIElement::centerTextInBackground(Axis axis) {
	if (!background.has_value() || !text.has_value()) {
		return;
	}
	sf::Vector2f absoluteBackgroundCenter = background->getGlobalBounds().getCenter();
	sf::Vector2f textSize = text->getLocalBounds().size;
	sf::Vector2f newPosition = text->getPosition();
	if (axis == Axis::X || axis == Axis::XY) {
		newPosition.x = absoluteBackgroundCenter.x - textSize.x / 2.f;
	}
	if (axis == Axis::Y || axis == Axis::XY) {
		// -10.f for now since the font seems to have some extra transparent height.
		newPosition.y = absoluteBackgroundCenter.y - textSize.y / 2.f - 10.f;
	}
	text->setPosition(newPosition);
}

UIElement::UIElement(const sf::Vector2f& pos, const UIElementColorParams& colors, std::optional<UIElementTextParams> textParams, std::optional<sf::RectangleShape> backgroundArg) 
	: background{backgroundArg} {
	if (!backgroundArg.has_value() && !textParams.has_value()) {
		throw std::invalid_argument("UI Element must have either background or text.");
	}
	if (background.has_value()) {
		background->setPosition(pos);
		if (colors.background.has_value()) {
			background->setFillColor(*colors.background);
		}
	}
	if (textParams.has_value()) {
		text = sf::Text{*textParams->font, textParams->str, textParams->fontSize};
		text->setPosition(pos);
		if (colors.text.has_value()) {
			text->setFillColor(*colors.text);
		}
	}
	centerTextInBackground(Axis::XY);
}

void UIElement::setPosition(const sf::Vector2f& pos) {
	if (background.has_value()) {
		background->setPosition(pos);
		centerTextInBackground(Axis::XY);
	} else {
		if (text.has_value()) {
			text->setPosition(pos);
		}
	}
}

void UIElement::setBackgroundColor(const sf::Color& color) {
	if (background.has_value()) {
		background->setFillColor(color);
	}
}

void UIElement::setBackgroundSize(sf::Vector2f size) {
	if (background.has_value()) {
		background->setSize(size);
		centerTextInBackground(Axis::XY);
	}
}

void UIElement::setTextColor(const sf::Color& color) {
	if (text.has_value()) {
		text->setFillColor(color);
	}
}

void UIElement::setFont(sf::Font* font) {
	if (text.has_value()) {
		text->setFont(*font);
	}
}

void UIElement::setFontSize(unsigned int fontSize) {
	if (text.has_value()) {
		text->setCharacterSize(fontSize);
	}
}

void UIElement::setText(const std::string& newText) {
	if (text.has_value()) {
		text->setString(newText);
	}
}

std::optional<std::string> UIElement::getText() {
	if (text.has_value()) {
		return text->getString().toAnsiString();
	} else {
		return std::nullopt;
	}
}

void UIElement::draw(sf::RenderWindow& window) {
	if (background.has_value()) {
		window.draw(*background);
	}
	if (text.has_value()) {
		window.draw(*text);
	}
}

void UIElement::centerInWindow(sf::RenderWindow& window, Axis axis) {
	sf::Vector2f position;
	sf::Vector2f elementSize;
	if (background.has_value()) {
		position = background->getPosition();
		elementSize = background->getSize();
	} else if (text.has_value()) {
		position = text->getPosition();
		elementSize = text->getLocalBounds().size;
	} else {
		return;
	}
    sf::Vector2f viewSize = window.getView().getSize();

	if (axis == Axis::X || axis == Axis::XY) {
		position.x = viewSize.x / 2.f - elementSize.x / 2.f;
	}
	if (axis == Axis::Y || axis == Axis::XY) {
		position.y = viewSize.y / 2.f - elementSize.y / 2.f;
	}
	setPosition(position);
	centerTextInBackground(Axis::XY);
}

void UIElement::moveTextPositionBy(const sf::Vector2f& amount) {
	if (!text.has_value()) {
		return;
	}
	sf::Vector2f textPosition = text->getPosition();
	textPosition.x += amount.x;
	textPosition.y += amount.y;
	text->setPosition(textPosition);
}