#include "model.hpp"
#include <fstream>
#include <sstream>
#include <string>


Paddle::Paddle(Point center, float w, float h) : Rectangle{center, w, h} {}

Ball::Ball(Point center, float r): Ball{center, r} {}

Brick::Brick(Point center, float w, float h): Rectangle{center, w, h} {}

Score::Score(Point center, float w, float h, int score): IntRectangle{center, w, h, score} {}

Lives::Lives(Point center, float w, float h, int lives): IntRectangle{center, w, h, lives} {}

void Game::reset() {
    score = INITIAL_SCORE;
    lives = INITIAL_LIVES;
}

bool Game::isGameOver(){
    return lives==0;
}

void loadLevel(const std::string& filename){
    printf("load");
}