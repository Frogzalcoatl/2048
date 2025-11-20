#pragma once
#include "2048/ui/screens/base.hpp"
#include "2048/ui/boardRenderer.hpp"

class GameScreen : public UIScreen {
public:
    GameScreen(sf::RenderWindow& window, Board& board);
    void draw(sf::RenderWindow& window) override;
    InputActionResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
    void setScore(std::uint64_t newScore);
private:
    Board& board;
    BoardRenderer boardRenderer;
    UIElement score;
    UIElement highScore;
};