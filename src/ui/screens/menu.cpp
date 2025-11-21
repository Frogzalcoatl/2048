#include "2048/ui/screens/menu.hpp"
#include "2048/ui/button.hpp"
#include "2048/ui/assets.hpp"
using namespace std;

MenuScreen::MenuScreen(sf::RenderWindow& window, function<void()> playButton, function<void()> onQuit): onQuit{onQuit} {
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
            UIElementTextParams{"2048", &Assets2048::boldFont, 300}
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
            playButton,
            sf::Vector2f{0.f, 500.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"Play", &Assets2048::boldFont, 50},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
    elements.push_back(
        make_unique<Button>(
            onQuit,
            sf::Vector2f{0.f, 625.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"Quit", &Assets2048::boldFont, 50},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
    elements.back().get()->centerInWindow(window, Axis::X);
}
void MenuScreen::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
    UIScreen::handleKeyboardInput(scancode);
    switch (scancode) {
        case sf::Keyboard::Scancode::Escape: {
            onQuit();
        } break;
    }
}