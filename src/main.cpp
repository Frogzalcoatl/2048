#include <SFML/Graphics.hpp>
#include <iostream>
#include "2048/game/board.h"
#include "2048/game/keyboardInput.h"
using namespace std;

int main() {
	auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "2048");
	window.setFramerateLimit(60);
	const sf::Font font(".\\assets\\fonts\\DejaVuSans.ttf");
	sf::Text text(font, "", 100);
	board.populate();
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				keyboardInput.pressed(keyPressed);
			} else if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>()) {
				keyboardInput.released(keyReleased);
			}
		}
		text.setString(board.getTestString());
		window.clear();
		window.draw(text);
		window.display();
	}
}
