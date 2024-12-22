#ifndef VIEW_HPP
#define VIEW_HPP

#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "allegro5/allegro5.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"

#include "drawables.hpp"
#include "../model/model.hpp"

struct Point {
  float x = 0, y = 0;
};

struct PointInt {
  int x = 0, y = 0;
};

class Text;

class ViewObject: public virtual Drawable {
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

#endif // VIEW_HPP