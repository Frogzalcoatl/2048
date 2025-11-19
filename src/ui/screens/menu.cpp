#include "2048/ui/screens/menu.hpp"
#include "2048/ui/button.hpp"
using namespace std;

MenuScreen::MenuScreen(const GameAssets& assets, sf::RenderWindow& window) 
    : title{
        sf::Vector2f{100.f, 0.f},
		UIElementColorParams{sf::Color{0x786E65FF}},
        UIElementTextParams{"2048", &assets.boldFont, 300}
    }, buttonBackground{
        sf::Vector2f{0.f, 450.f},
        UIElementColorParams{nullopt, sf::Color{0xBBADA0FF}},
        nullopt,
        sf::RectangleShape{{475.f, 300.f}}
    }, playButton{
        []() {
            return ScreenResult{ScreenAction::ChangeScreen, UIScreenTypes::Game};
        },
        sf::Vector2f{0.f, 500.f},
		UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
        UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
        UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
        UIElementTextParams{"Play", &assets.boldFont, 50},
        sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
    }, quitButton{
        []() {
            return ScreenResult{ScreenAction::ExitGame};
        },
        sf::Vector2f{0.f, 625.f},
		UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
        UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
        UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
        UIElementTextParams{"Quit", &assets.boldFont, 50},
        sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
    }
    {
    title.centerInWindow(window, Axis::X);
    buttonBackground.centerInWindow(window, Axis::X);
    playButton.centerInWindow(window, Axis::X);
    quitButton.centerInWindow(window, Axis::X);

    elements.push_back(make_unique<UIElement>(title));
    elements.push_back(make_unique<UIElement>(buttonBackground));
    elements.push_back(make_unique<Button>(playButton));
    elements.push_back(make_unique<Button>(quitButton));
}
ScreenResult MenuScreen::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
    switch (scancode) {
        case sf::Keyboard::Scancode::Escape: {
            return ScreenResult{ScreenAction::ExitGame};
        }
    }
    return ScreenResult{};
}