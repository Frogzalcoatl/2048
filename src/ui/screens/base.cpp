#include "2048/ui/screens/base.hpp"
#include "2048/ui/button.hpp"
#include "2048/ui/cursorManager.hpp"
using namespace std;

InputActionResult UIScreen::draw(MouseInput& mouseInput, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2i mousePos = mouseInput.getPos();
    bool mouseIsWithinWindow = (mousePos.x > 0 && mousePos.x < windowSize.x) && (mousePos.y > 0 && mousePos.y < windowSize.y);
    if (mouseIsWithinWindow) {
        window.setMouseCursor(CursorManager::getNormalCursor());
    }
    InputActionResult finalResult{};
    for (auto& element : elements) {
        if (Button* button = dynamic_cast<Button*>(element.get())) {
            InputActionResult result = button->update(mouseInput, window);
            if (result.action == InputAction::ExitGame) {
                return InputActionResult{InputAction::ExitGame};
            } else if (result.action == InputAction::ChangeScreen || result.action == InputAction::ResetGame) {
                finalResult = result;
            }
        }
        element->draw(window);
    }
    return finalResult;
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