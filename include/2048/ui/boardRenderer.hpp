#pragma once
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include "2048/game/board.hpp"
#include "2048/ui/assets.hpp"

class BoardRenderer {
public:
	BoardRenderer(GameAssets* assets, size_t boardWidth, size_t boardHeight);
	// render the board to the target; call once per frame
	void render(sf::RenderTarget& target, const Board& board);

private:
	struct TileAnim {
		std::uint64_t lastValue = 0;
		sf::Color startColor{200, 200, 200};
		sf::Color endColor{200, 200, 200};
		float startTime = 0.f;
		float duration = 0.2f;  // seconds
		bool animating = false;
	};

	GameAssets* assets;
	size_t boardWidth;
	size_t boardHeight;
	std::vector<TileAnim> tiles;
	sf::Clock clock;

	sf::Color colorForValue(std::uint64_t value) const;
	static sf::Color lerp(const sf::Color& a, const sf::Color& b, float t);
};
