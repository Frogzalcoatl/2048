#include "2048/ui/screens/game.hpp"
#include "2048/ui/button.hpp"
#include "2048/game/stringToInt.hpp"
#include "2048/game/scoreStorage.hpp"
#include "2048/ui/assets.hpp"
using namespace std;

GameScreen::GameScreen(sf::RenderWindow& window, Board& board) 
	: board{board}, boardRenderer{board.width, board.height},
	score{
		sf::Vector2f{938.f, 30.f},
        UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0xBBADA0FF}},
        UIElementTextParams{to_string(board.getScore()), &Assets2048::boldFont, 28},
        sf::RectangleShape{{200.f, 70.f}}
	}, highScore{
		sf::Vector2f{1154.f, 30.f},
        UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0xBBADA0FF}},
        UIElementTextParams{to_string(ScoreStorage::loadHighScore()), &Assets2048::boldFont, 28},
        sf::RectangleShape{{200.f, 70.f}}
	} {
	score.moveTextPositionBy({0.f, 10.f});
	highScore.moveTextPositionBy({0.f, 10.f});
    // Must explicitly state types in make_unique since template functions cant recogize types just from {}.
	elements.push_back(
        make_unique<UIElement>(
			sf::Vector2f{1006.f, 35.f},
			UIElementColorParams{sf::Color{0xEEE4D4FF}},
			UIElementTextParams{"SCORE", &Assets2048::boldFont, 22}
		)
    );
	elements.push_back(
        make_unique<UIElement>(
			sf::Vector2f{1229.f, 35.f},
			UIElementColorParams{sf::Color{0xEEE4D4FF}},
			UIElementTextParams{"BEST", &Assets2048::boldFont, 22}
		)
    );
	elements.push_back(
        make_unique<UIElement>(
			sf::Vector2f{566.f, 20.f},
			UIElementColorParams{sf::Color{0x786E65FF}},
			UIElementTextParams{"2048", &Assets2048::boldFont, 75}
		)
    );
	elements.push_back(
		make_unique<UIElement>(
			sf::Vector2f{566.f, 110.f},
			UIElementColorParams{sf::Color{0x786E65FF}},
			UIElementTextParams{"Join numbers to get to the 2048 tile!", &Assets2048::regularFont, 22}
		)
	);

	sf::Vector2f buttonSize = {250.f, 90.f};
    elements.push_back(
        make_unique<Button>(
            []() {
                return InputActionResult{InputAction::ChangeScreen, UIScreenTypes::Menu};
            },
            sf::Vector2f{0.f, 965.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"Back", &Assets2048::boldFont, 40},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
	elements.back().get()->centerInWindow(window, Axis::X);
	elements.push_back(
        make_unique<Button>(
            []() {
                return InputActionResult{InputAction::ResetGame};
            },
            sf::Vector2f{1600.f, 20.f},
			UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x726151FF}},
            UIElementColorParams{sf::Color{0xFFFFFFFF}, sf::Color{0x8F7A66FF}},
            UIElementTextParams{"New Game", &Assets2048::boldFont, 40},
            sf::RectangleShape{sf::Vector2f{buttonSize.x, buttonSize.y}}
        )
    );
}

InputActionResult GameScreen::handleKeyboardInput(sf::Keyboard::Scancode scancode) {
	InputActionResult baseResult = UIScreen::handleKeyboardInput(scancode);
	if (baseResult.action != InputAction::None) {
		return baseResult;
	}
    switch (scancode) {
		case sf::Keyboard::Scancode::Up:
		case sf::Keyboard::Scancode::W: {
			board.doMove(Direction::Up);
			return InputActionResult{InputAction::UpdateScore};
		}; break;
		case sf::Keyboard::Scancode::Down:
		case sf::Keyboard::Scancode::S: {
			board.doMove(Direction::Down);
			return InputActionResult{InputAction::UpdateScore};
		}; break;
		case sf::Keyboard::Scancode::Right:
		case sf::Keyboard::Scancode::D: {
			board.doMove(Direction::Right);
			return InputActionResult{InputAction::UpdateScore};
		}; break;
		case sf::Keyboard::Scancode::Left:
		case sf::Keyboard::Scancode::A: {
			board.doMove(Direction::Left);
			return InputActionResult{InputAction::UpdateScore};
		}; break;
		default: {
			return InputActionResult{};
		}
	}
}

InputActionResult GameScreen::draw(MouseInput& mouseInput, sf::RenderWindow& window) {
	score.draw(window);
	highScore.draw(window);
	InputActionResult buttonResult = UIScreen::draw(mouseInput, window);
	boardRenderer.render(window, board);
	bool isGameOver = board.getGameOverStatus();
	if (isGameOver) {
		sf::Text gameOver{Assets2048::boldFont, "GAME OVER!", 200};
		sf::Vector2f size = gameOver.getGlobalBounds().size;
		gameOver.setPosition({1920.f / 2.f - size.x / 2.f, 1080.f / 2.f - size.y / 2.f - 100});
		gameOver.setFillColor(sf::Color::Black);
		window.draw(gameOver);
	}
	return buttonResult;
}

void GameScreen::setScore(uint64_t newScore) {
	score.setText(to_string(newScore));
	score.centerTextInBackground(Axis::X);
	auto highScoreText = highScore.getText();
	if (!highScoreText.has_value()) {
		return;
	}
	uint64_t highScoreNum = stringToUInt64(*highScoreText);
	if (newScore > highScoreNum) {
		highScore.setText(to_string(newScore));
		highScore.centerTextInBackground(Axis::X);
		ScoreStorage::saveHighScore(newScore);
	}
}