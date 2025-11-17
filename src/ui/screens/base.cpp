#include "2048/ui/screens/base.hpp"
#include "2048/ui/button.hpp"
using namespace std;

ScreenResult UIScreen::draw(MouseInput& mouseInput, sf::RenderWindow& window) {
    window.setMouseCursor(cursorNormal);
    ScreenResult finalResult{};
    for (auto& u_ptr : elements) {
        auto element = u_ptr.get();
        if (Button* button = dynamic_cast<Button*>(element)) {
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