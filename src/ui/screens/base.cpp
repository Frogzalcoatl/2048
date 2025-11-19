#include "2048/ui/screens/base.hpp"
#include "2048/ui/button.hpp"
#include "2048/ui/cursorManager.hpp"
using namespace std;

ScreenResult UIScreen::draw(MouseInput& mouseInput, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2i mousePos = mouseInput.getPos();
    bool mouseIsWithinWindow = (mousePos.x > 0 && mousePos.x < windowSize.x) && (mousePos.y > 0 && mousePos.y < windowSize.y);
    if (mouseIsWithinWindow) {
        window.setMouseCursor(CursorManager::getNormalCursor());
    }
    ScreenResult finalResult{};
    for (auto& element : elements) {
        if (Button* button = dynamic_cast<Button*>(element.get())) {
            ScreenResult result = button->update(mouseInput, window);
            if (result.action == ScreenAction::ExitGame) {
                return ScreenResult{ScreenAction::ExitGame};
            } else if (result.action == ScreenAction::ChangeScreen || result.action == ScreenAction::ResetGame) {
                finalResult = result;
            }
        }
        element->draw(window);
    }
    return finalResult;
}