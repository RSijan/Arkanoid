#ifndef VIEW_HPP
#define VIEW_HPP

#include <memory>
#include <vector>

#include "../model/model.hpp"

struct Point {
  float x = 0, y = 0;
};

struct PointInt {
  int x = 0, y = 0;
};

/*--------------------------------------------------
Drawable class.
--------------------------------------------------*/
class Drawable {
 protected:
  Drawable()                             = default;
  Drawable(const Drawable &)            = default;
  Drawable(Drawable &&)                 = default;
  Drawable &operator=(const Drawable &) = default;
  Drawable &operator=(Drawable &&)      = default;

 public:
  virtual bool contains(Point p) const = 0;
  virtual void draw()                 = 0;
  virtual ~Drawable()                 = default;
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
}

class GameDisplayer: public ViewObject {
public:
    void drawPaddle(const std::shared_ptr<Paddle>& paddle);
    void drawBall(const std::shared_ptr<Ball>& ball);
    void drawBricks(const std::vector<std::shared_ptr<Bricks>>& bricks);
    void drawScore(const std::shared_ptr<Text>& score);
    void drawlives(const std::shared_ptr<Text>& lives);
    void drawWinMessage(const std::shared_ptr<Text>& message);
    void drawGameOver(const std::shared_ptr<Text>& message);
};

#endif #VIEW_HPP