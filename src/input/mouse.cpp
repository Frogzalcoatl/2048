#include <SFML/Window/Mouse.hpp>
#include "2048/input/mouse.hpp"
#include <unordered_map>
using namespace std;

void MouseInput::update(sf::RenderWindow& window) {
	mousePos = sf::Mouse::getPosition(window);
	bool leftClickDownLastTick = leftClickDown;
	leftClickDown = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	if (leftClickDownLastTick && !leftClickDown) {
		leftClickReleased = true;
	} else {
		leftClickReleased = false;
	}
	if (requestedCursorType != currentCursorType) {
		window.setMouseCursor(getSystemCursor(requestedCursorType));
	}
	resetCursorRequest();
}

sf::Vector2i MouseInput::getPos() {
	return mousePos;
}

bool MouseInput::isLeftClickDown() {
	return leftClickDown;
}

bool MouseInput::wasLeftClickReleased() {
	return leftClickReleased;
}

sf::Cursor& MouseInput::getSystemCursor(sf::Cursor::Type type) {
	// Since this map is static it exists across every call to this function.
	static unordered_map<sf::Cursor::Type, unique_ptr<sf::Cursor>> cursorCache;
	auto iterator = cursorCache.find(type);
	if (iterator != cursorCache.end()) {
		return *iterator->second;
	}
	auto newCursor = make_unique<sf::Cursor>(type);
	if (newCursor->createFromSystem(type)) {
		cursorCache[type] = move(newCursor);
		return *cursorCache[type];
	}
	if (type != sf::Cursor::Type::Arrow) {
		// Return the default cursor if the function failed for whatever reason.
		return getSystemCursor(sf::Cursor::Type::Arrow);
	}
	// Return an empty cursor if the function still failed.
	return *newCursor;
}

void MouseInput::requestCursor(const sf::Cursor::Type cursorType) {
	requestedCursorType = cursorType;
}

void MouseInput::resetCursorRequest() {
	currentCursorType = requestedCursorType;
	requestedCursorType = sf::Cursor::Type::Arrow;
}