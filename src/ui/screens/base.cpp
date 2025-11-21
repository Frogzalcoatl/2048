#include "2048/ui/screens/base.hpp"
using namespace std;

void UIScreen::draw(sf::RenderWindow& window) {
    for (auto& element : elements) {
        element->draw(window);
    }
}

void UIScreen::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    for (auto& element : elements) {
        element->handleEvent(event, window);
    }
}