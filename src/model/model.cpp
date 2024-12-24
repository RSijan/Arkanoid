#include "model.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>


Paddle::Paddle(Point center, float w, float h) : Rectangle{center, w, h} {}

void Paddle::update(float x) {
    center_.x = x;
}

Ball::Ball(Point center, float r): Circle{center, r} {}

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

void Level::loadLevel(const std::string& filename) {
    bricks.clear();
    std::ifstream file(filename);
    if (!file.is_open()){
        std::cerr << "Error: Could not open level file: " << filename << std::endl;
        return;
    }
    std::string line;
    float brickWidth = 50;
    float brickHeight = 20;
    int row = 0;

    while (std::getline(file, line)) {
         for (int col = 0; col < line.size(); ++col) {
            char c = line[col];
            float x = static_cast<float>(col * brickWidth + brickWidth/2);
            float y = static_cast<float>(row * brickHeight + brickHeight/2 + 50);

            if (c == '#') {
                 bricks.push_back(std::make_shared<Brick>(Point{x, y}, brickWidth, brickHeight));
            // } else if (c == '2') {
            //      bricks.push_back(std::make_shared<Brick>(Point{x, y}, brickWidth, brickHeight, 2));
            // }else if (c == 'X') {
            //     bricks.push_back(std::make_shared<Brick>(Point{x, y}, brickWidth, brickHeight, -1));
            }
        }
        row++;
    }
     file.close();
}

    