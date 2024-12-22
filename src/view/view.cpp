#include "view.hpp"

GameObjectsDrawer::GameObjectsDrawer(ALLEGRO_DISPLAY* display):display(display) {}
GameObjectsDrawer::~GameObjectsDrawer() {}

void GameObjectsDrawer::drawPaddle(const std::shared_ptr<Paddle>& paddle) {
    paddle->draw();
}

void GameObjectsDrawer::drawBall(const std::shared_ptr<Ball>& ball) {
    ball->draw();
}

void GameObjectsDrawer::drawBricks(const std::vector<std::shared_ptr<Brick>>& bricks) {
    if (!bricks.empty()) {
        for (const auto& brick : bricks) {
            brick->draw();
        }
    }
}

void GameObjectsDrawer::drawScore(const std::shared_ptr<Text>& score) {
    score->draw();
}

void GameObjectsDrawer::drawLives(const std::shared_ptr<Text>& lives) {
    lives->draw();
}

void GameObjectsDrawer::drawWinMessage(const std::shared_ptr<Text>& message) {
    message->draw();
}

void GameObjectsDrawer::drawGameOver(const std::shared_ptr<Text>& message) {
    message->draw();
}

DisplayInitializer::DisplayInitializer(int width, int height, int fontSize, std::string fontPath) {

        al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
        al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
        al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

        display = al_create_display(width, height);
        must_init(display, "display");
        must_init(al_init_ttf_addon(), "TTF addon");

        font = al_load_ttf_font(fontPath.c_str(), fontSize, 0);
        must_init(font, "font");
        must_init(al_init_primitives_addon(), "primitives");

        FONT_SIZE = fontSize;
}

DisplayInitializer::~DisplayInitializer() {
    
    if (display) {
        al_destroy_display(display);
        display = nullptr;
    }

    if (font) {
        al_destroy_font(font);
        font = nullptr;
    }
}

ALLEGRO_DISPLAY* DisplayInitializer::getDisplay() {
    return display;
}

void DisplayInitializer::must_init(bool test, const char *description) {
  if (test) {
    return;
  }
  std::cerr << "couldn't initialize " << description << '\n';
  exit(1);
}

void DisplayInitializer::must_init(void *test, const char *description) {
  must_init(test != nullptr, description);
}