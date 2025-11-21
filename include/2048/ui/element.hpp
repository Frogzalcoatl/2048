#pragma once
#include <optional>
#include <SFML/Graphics.hpp>

struct UIElementColorParams {
	std::optional<sf::Color> text;
	std::optional<sf::Color> background;
};

struct UIElementTextParams {
	std::string str;
	const sf::Font* font;
	unsigned int fontSize;
};

enum Axis {
	X,
	Y,
	XY
};

class UIElement {
public:
	virtual ~UIElement() {}

	UIElement(const sf::Vector2f& pos, const UIElementColorParams& colors, std::optional<UIElementTextParams> textParams, std::optional<sf::RectangleShape> background = std::nullopt);
	void setPosition(const sf::Vector2f& pos);
	void setBackgroundColor(const sf::Color& color);
	void setBackgroundSize(const sf::Vector2f size);
	void setTextColor(const sf::Color& color);
	void setFont(sf::Font* font);
	void setFontSize(unsigned int fontSize);
	void setText(const std::string& newText);
	std::optional<std::string> getText();
	void draw(sf::RenderWindow& window);
	void centerInWindow(sf::RenderWindow& window, Axis axis);
	void moveTextPositionBy(const sf::Vector2f& amount);
	void centerTextInBackground(Axis axis);
	virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) {};

protected:
	std::optional<sf::RectangleShape> background;
	std::optional<sf::Text> text;
};