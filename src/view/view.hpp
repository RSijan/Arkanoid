#ifndef VIEW_HPP
#define VIEW_HPP

#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "../utils/allegro_includes.hpp"
#include "drawables.hpp"
#include "../model/model.hpp"

class Text;

class ViewObject {
protected:
  ViewObject() = default;
  ViewObject(const ViewObject&)= default;
  ViewObject(ViewObject&&) = default;
  ViewObject& operator=(const ViewObject&)= default;
  ViewObject& operator=(ViewObject&&)= default;

public:
  virtual ~ViewObject() = default;
};

class GameObjectsDrawer: public ViewObject {
public:
  GameObjectsDrawer(ALLEGRO_DISPLAY* display);
  ~GameObjectsDrawer() override;
  void drawPaddle(const std::shared_ptr<Paddle>& paddle);
  void drawBall(const std::shared_ptr<Ball>& ball);
  void drawBricks(const std::vector<std::shared_ptr<Brick>>& bricks);
  void drawScore(const std::shared_ptr<Text>& score);
  void drawLives(const std::shared_ptr<Text>& lives);
  void drawWinMessage(const std::shared_ptr<Text>& message);
  void drawGameOver(const std::shared_ptr<Text>& message); 

private:
  ALLEGRO_DISPLAY* display;
};

class DisplayInitializer: public ViewObject {
public:
  DisplayInitializer(int windowWidth, int windowHeight, int fontSize, std::string fontPath);
  ~DisplayInitializer();
  ALLEGRO_DISPLAY* getDisplay();
  void must_init(bool test, const char *description);
  void must_init(void *test, const char *description);

private:
  ALLEGRO_DISPLAY *display = nullptr;
};

class DisplayManager: public ViewObject {
public:
  DisplayManager() = delete;
  DisplayManager(const DisplayManager&) = delete;
  DisplayManager& operator=(const DisplayManager&) = delete;
  explicit DisplayManager(ALLEGRO_DISPLAY* display);
  ~DisplayManager();
  void clearDisplay();
  void flipDisplay();
private:
  ALLEGRO_DISPLAY* display;
};

#endif // VIEW_HPP