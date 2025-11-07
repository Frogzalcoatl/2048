#include <SFML/Graphics.hpp>
#include <iostream>
#include "./game/board.h"
using namespace std;

bool previouslyPressedP = false;

int main() {
	auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
	window.setFramerateLimit(144);
	const sf::Font font(".\\assets\\fonts\\DejaVuSans.ttf");
	string str = "";
	sf::Text text(font, str, 100);
	auto board = Board();
	board.populate();
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}
		// Below is just for the purpose of testing. Press p to repopulate board.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P) && !previouslyPressedP) {
			board.clear();
			board.populate();
			previouslyPressedP = true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::P) && previouslyPressedP) {
			previouslyPressedP = false;
		}
		text.setString(board.getTestString());
		window.clear();
		window.draw(text);
		window.display();
	}
}
