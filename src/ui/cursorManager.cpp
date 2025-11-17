#include "2048/ui/cursorManager.hpp"

namespace CursorManager {
	sf::Cursor& getHoveredCursor() {
		static sf::Cursor cursor = sf::Cursor(sf::Cursor::Type::Hand);
		return cursor;
	}

	sf::Cursor& getNormalCursor() {
		static sf::Cursor cursor = sf::Cursor(sf::Cursor::Type::Arrow);
		return cursor;
	}
}