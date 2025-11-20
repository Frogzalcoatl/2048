#include "2048/ui/cursorManager.hpp"
#include <unordered_map>
using namespace std;

sf::Cursor& CursorManager::getCursor(sf::Cursor::Type type) {
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
		return getCursor(sf::Cursor::Type::Arrow);
	}
	// Return an empty cursor if the function still failed.
	return *newCursor;
}