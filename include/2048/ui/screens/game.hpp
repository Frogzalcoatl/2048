#pragma once
#include "2048/ui/assets.hpp"
#include "2048/ui/screens/base.hpp"
#include "2048/ui/boardRenderer.hpp"

class GameScreen : public UIScreen {
public:
    GameScreen(GameAssets& assets, sf::RenderWindow& window, Board& board);
    ScreenResult draw(MouseInput& mouseInput, sf::RenderWindow& window) override;
    ScreenResult handleKeyboardInput(sf::Keyboard::Scancode scancode) override;
    void setScore(std::uint64_t newScore);
private:
    Board& board;
    GameAssets& assets;
    BoardRenderer boardRenderer;
    UIElement score;
    UIElement highScore;
    UIElement background;
};