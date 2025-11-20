#include "2048/ui/screens/base.hpp"
using namespace std;

void UIScreen::draw(sf::RenderWindow& window) {
    for (auto& element : elements) {
        element->draw(window);
    }
}

InputActionResult UIScreen::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
    switch (scancode) {
        case sf::Keyboard::Scancode::F11: {
            return InputActionResult{InputAction::ToggleFullscreen};
        } break;
        default: {
            return InputActionResult{};
        }
    }
}

InputActionResult UIScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    InputActionResult finalResult{};
    for (auto& element : elements) {
        InputActionResult result = element->handleEvent(event, window);
        if (result.action != InputAction::None) {
            finalResult = result;
        }
    }
    return finalResult;
}