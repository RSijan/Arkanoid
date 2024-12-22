#include "view.h"
#include "drawable.h"
#include "allegro5/allegro5.h"

void GameRenderer::drawPaddle(const std::shared_ptr<Paddle>& paddle) {
  paddle->draw();
}

void GameRenderer::drawBall(const std::shared_ptr<Ball>& ball) {
    ball->draw();
}

void GameRenderer::drawBricks(const std::vector<std::shared_ptr<Brick>>& bricks) {
    for (const auto& brick : bricks) {
        brick->draw();
    }
}

void GameRenderer::drawScore(const std::shared_ptr<Text>& score) {
    score->draw();
}

void GameRenderer::drawLives(const std::shared_ptr<Text>& lives) {
    lives->draw();
}

void GameRenderer::drawWinMessage(const std::shared_ptr<Text>& message) {
    message->draw();
}

void GameRenderer::drawGameOver(const std::shared_ptr<Text>& message) {
    message->draw();
}