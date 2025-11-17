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
            UIElementTextParams{"2048", &assets.boldFont, 150}
		)
    );
    elements.back().get()->centerInWindow(window, Axis::X);
    elements.push_back(
        make_unique<UIElement>(
            sf::Vector2f{0.f, 375.f},
            UIElementColorParams{nullopt, sf::Color{0xBBADA0FF}},
            nullopt,
            sf::RectangleShape{{500.f, 250.f}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
    sf::Vector2f buttonSize = {400.f, 75.f};
    elements.push_back(
        make_unique<Button>(
            []() {
                return ScreenResult{ScreenAction::ChangeScreen, UIScreenTypes::Game};
            },
            sf::Vector2f{0.f, 400.f},
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
                return ScreenResult{ScreenAction::ExitGame};
            },
            sf::Vector2f{0.f, 525.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"Quit", &assets.boldFont, 50},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
}
ScreenResult MenuScreen::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
    switch (scancode) {
        case sf::Keyboard::Scancode::Escape: {
            return ScreenResult{ScreenAction::ExitGame};
        }
    }
    return ScreenResult{};
}