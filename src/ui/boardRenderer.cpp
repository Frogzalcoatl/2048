#include "2048/ui/boardRenderer.hpp"
#include <cmath>
#include <sstream>

BoardRenderer::BoardRenderer(GameAssets* assets, size_t boardWidth, size_t boardHeight)
    : assets(assets), boardWidth(boardWidth), boardHeight(boardHeight) {
    tiles.resize(boardWidth * boardHeight);
}

sf::Color BoardRenderer::lerp(const sf::Color& a, const sf::Color& b, float t) {
    t = std::max(0.f, std::min(1.f, t));
    return sf::Color(
        static_cast<std::uint8_t>(a.r + (b.r - a.r) * t),
        static_cast<std::uint8_t>(a.g + (b.g - a.g) * t),
        static_cast<std::uint8_t>(a.b + (b.b - a.b) * t),
        static_cast<std::uint8_t>(a.a + (b.a - a.a) * t)
    );
}

sf::Color BoardRenderer::colorForValue(uint64_t value) const {
    // Palette inspired by common 2048 themes
    switch (value) {
        case 0: return sf::Color(205, 193, 180); // empty tile
        case 2: return sf::Color(238, 228, 218);
        case 4: return sf::Color(237, 224, 200);
        case 8: return sf::Color(242, 177, 121);
        case 16: return sf::Color(245, 149, 99);
        case 32: return sf::Color(246, 124, 95);
        case 64: return sf::Color(246, 94, 59);
        case 128: return sf::Color(237, 207, 114);
        case 256: return sf::Color(237, 204, 97);
        case 512: return sf::Color(237, 200, 80);
        case 1024: return sf::Color(237, 197, 63);
        case 2048: return sf::Color(237, 194, 46);
        default: return sf::Color(60, 58, 50); // large tiles
    }
}

void BoardRenderer::render(sf::RenderTarget& target, const Board& board) {
    const auto& tileValues = board.getTiles();
    const float now = clock.getElapsedTime().asSeconds();

    // layout
    const float tileSize = 175.f;
    const float padding = 17.5f;
    const float boardW = boardWidth * tileSize + (boardWidth + 1) * padding;
    const float boardH = boardHeight * tileSize + (boardHeight + 1) * padding;
    const sf::Vector2f winSize(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y));
    const sf::Vector2f boardTopLeft((winSize.x - boardW) / 2.f, (winSize.y - boardH) / 2.f);

    // background rounded rect - using simple rectangle for portability
    sf::RectangleShape bg{
        sf::Vector2f(boardW, boardH)
    };
    bg.setPosition(boardTopLeft);
    bg.setFillColor(sf::Color(187, 173, 160));
    target.draw(bg);

    // draw tiles
    for (size_t y = 0; y < boardHeight; ++y) {
        for (size_t x = 0; x < boardWidth; ++x) {
            const size_t idx = y * boardWidth + x;
            const uint64_t value = tileValues[idx];
            TileAnim& ta = tiles[idx];

            if (value != ta.lastValue) {
                // start animation from previous color to new color
                ta.startColor = colorForValue(ta.lastValue);
                ta.endColor = colorForValue(value);
                ta.startTime = now;
                ta.animating = true;
                ta.lastValue = value;
            }

            float progress = 1.f;
            if (ta.animating) {
                progress = (now - ta.startTime) / ta.duration;
                if (progress >= 1.f) {
                    progress = 1.f;
                    ta.animating = false;
                }
            }

            const sf::Color curColor = lerp(ta.startColor, ta.endColor, progress);

            const float px = boardTopLeft.x + padding + x * (tileSize + padding);
            const float py = boardTopLeft.y + padding + y * (tileSize + padding);

            sf::RectangleShape tileRect(sf::Vector2f(tileSize, tileSize));
            tileRect.setPosition({px, py});
            tileRect.setFillColor(curColor);
            tileRect.setOutlineColor(sf::Color(170, 164, 158));
            tileRect.setOutlineThickness(3.f);
            target.draw(tileRect);

            if (value != 0) {
                // draw number centered
                sf::Text txt{assets->boldFont, [&value]() {
                    std::ostringstream ss;
                    ss << value;
                    return ss.str();
                }()};
                // choose text color based on tile brightness
                if (value == 2 || value == 4) txt.setFillColor(sf::Color(119, 110, 101));
                else txt.setFillColor(sf::Color::White);

                // size text to fit
                const float targetWidth = tileSize * 0.8f;
                unsigned int charSize = 64;
                txt.setCharacterSize(charSize);
                // shrink until it fits
                while (charSize > 8 && txt.getLocalBounds().size.x > targetWidth) {
                    charSize -= 2;
                    txt.setCharacterSize(charSize);
                }

                // center
                const sf::FloatRect bounds = txt.getLocalBounds();
                txt.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
                txt.setPosition({px + tileSize / 2.f, py + tileSize / 2.f - 6.f});
                target.draw(txt);
            }
        }
    }
}
