#include <SFML/Graphics.hpp>
#include <iostream>
#include "2048/game/board.hpp"
#include "2048/game/keyboardInput.hpp"
#include "2048/ui/assets.hpp"
#include "2048/ui/boardRenderer.hpp"
using namespace std;

int main() {
	sf::RenderWindow window{sf::VideoMode{{1920u, 1080u}}, "2048"};
	window.setFramerateLimit(60);
	GameAssets assets;
	assets.loadAll();
	// sf::Text debugText{assets.boldFont, "", 100};
	Board board{4, 4, 2};
	Graphics2048::BoardRenderer renderer(&assets, board.width, board.height);
	KeyboardInput keyboardInput;
	while (window.isOpen()) {
		while (const optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			} else if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				keyboardInput.pressed(keyPressed, &board);
			} else if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>()) {
				keyboardInput.released(keyReleased);
			}
		}
		// Update & render board with colored tiles and animations
		window.clear();
		renderer.render(window, board);
		window.display();
	}
}
