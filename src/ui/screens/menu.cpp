#include "2048/ui/screens/menu.hpp"
#include "2048/ui/button.hpp"
using namespace std;

MenuScreen::MenuScreen(const GameAssets& assets, sf::RenderWindow& window) {
    elements.push_back(
        make_unique<UIElement>(
            sf::Vector2f{0.f, 0.f},
            UIElementColorParams{nullopt, sf::Color{0xFAF8EFFF}},
            nullopt,
            sf::RectangleShape{{1920.f, 1080.f}}
        )
    );
    elements.push_back(
        make_unique<UIElement>(
			sf::Vector2f{100.f, 0.f},
			UIElementColorParams{sf::Color{0x786E65FF}},
            UIElementTextParams{"2048", &assets.boldFont, 300}
		)
    );
    elements.back().get()->centerInWindow(window, Axis::X);
    elements.push_back(
        make_unique<UIElement>(
            sf::Vector2f{0.f, 450.f},
            UIElementColorParams{nullopt, sf::Color{0xBBADA0FF}},
            nullopt,
            sf::RectangleShape{{475.f, 300.f}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
    sf::Vector2f buttonSize = {400.f, 75.f};
    elements.push_back(
        make_unique<Button>(
            []() {
                return InputActionResult{InputAction::ChangeScreen, UIScreenTypes::Game};
            },
            sf::Vector2f{0.f, 500.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"Play", &assets.boldFont, 50},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
    elements.push_back(
        make_unique<Button>(
            []() {
                return InputActionResult{InputAction::ExitGame};
            },
            sf::Vector2f{0.f, 625.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"Quit", &assets.boldFont, 50},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
}
InputActionResult MenuScreen::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
    InputActionResult baseResult = UIScreen::handleKeyboardInput(scancode);
    if (baseResult.action != InputAction::None) {
		return baseResult;
	}
    switch (scancode) {
        case sf::Keyboard::Scancode::Escape: {
            return InputActionResult{InputAction::ExitGame};
        } break;
        default: {
            return InputActionResult{};
        }
    }
}