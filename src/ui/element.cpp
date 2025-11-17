#include "2048/ui/Element.hpp"
#include <SFML/Graphics.hpp>
using namespace std;

void UIElement::centerTextInBackground() {
	if (!background.has_value() || !text.has_value()) {
		return;
	}
	sf::Vector2f absoluteBackgroundCenter = background->getGlobalBounds().getCenter();
	sf::Vector2f textSize = text->getLocalBounds().size;
	// -10.f since the font seems to have some extra transparent height. Probably a better way to fix in the future.
	text->setPosition({(absoluteBackgroundCenter.x - textSize.x / 2.f), (absoluteBackgroundCenter.y - textSize.y / 2.f - 10.f)});
}

UIElement::UIElement(const sf::Vector2f& pos, const UIElementColorParams& colors, std::optional<UIElementTextParams> textParams, std::optional<sf::RectangleShape> background) 
	: background{background} {
	if (!background.has_value() && !textParams.has_value()) {
		this->~UIElement();
	}
	if (this->background.has_value()) {
		this->background->setPosition(pos);
		if (colors.background.has_value()) {
			this->background->setFillColor(*colors.background);
		}
	}
	if (textParams.has_value()) {
		text = sf::Text{*textParams->font, textParams->str, textParams->fontSize};
		text->setPosition(pos);
		if (colors.text.has_value()) {
			text->setFillColor(*colors.text);
		}
	}
	centerTextInBackground();
}

void UIElement::setPosition(const sf::Vector2f& pos) {
	if (background.has_value()) {
		background->setPosition(pos);
		centerTextInBackground();
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
		centerTextInBackground();
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

void UIElement::setText(string newText) {
	if (text.has_value()) {
		text->setString(newText);
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
	if (axis == Axis::X || axis == Axis::XY) {
		position.x = window.getSize().x / 2.f - elementSize.x / 2.f;
	}
	if (axis == Axis::Y || axis == Axis::XY) {
		position.y = window.getSize().y / 2.f - elementSize.y / 2.f;
	}
	setPosition(position);
	centerTextInBackground();
}