#pragma once
#include "2048/ui/screens/base.hpp"
#include "2048/ui/boardRenderer.hpp"
#include <functional>

class GameScreen : public UIScreen {
public:
    GameScreen(sf::RenderWindow& window, Board& board, std::function<void()> backButton, std::function<void()> newGameButton) ;
    void draw(sf::RenderWindow& window) override;
    void handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
    void updateScore();
private:
    Board& board;
    BoardRenderer boardRenderer;
    UIElement score;
    UIElement highScore;
};