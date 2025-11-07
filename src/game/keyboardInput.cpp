#include <SFML/Window/Keyboard.hpp>
#include "2048/game/keyboardInput.h"
#include "2048/game/board.h"
using namespace std;

KeyboardInput keyboardInput;

// Using unordered_maps for the first time in cpp.
void KeyboardInput::update() {
	for (auto& pair : pressedLastFrame) {
		sf::Keyboard::Scancode scancode = pair.first;
		bool& wasPressedLastFrame = pair.second;
		bool isPressedNow = sf::Keyboard::isKeyPressed(scancode);
		if (isPressedNow && !wasPressedLastFrame) {
			// it is short for iterator.
			auto func_it = keyPressFunctions.find(scancode);
			// pressedLastFrame.end() points to the position after its last element.
			// If func_it is invalid, it would equal pressedLastFrame.end().
			if (func_it != keyPressFunctions.end()) {
				func_it->second();
			}
		}
		wasPressedLastFrame = isPressedNow;
	}
}