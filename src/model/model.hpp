#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <vector>

#include "../view/drawables.hpp"
#include "../utils/observer.hpp"

#define INITIAL_LIVES 3
#define INITIAL_SCORE 0

struct Point {
  float x = 0, y = 0;
};

struct PointInt {
  int x = 0, y = 0;
};

class ModelObject: public virtual Subject, public virtual Drawable {
protected:
    ModelObject() = default;
    ModelObject(const ModelObject&) = default;
    ModelObject(ModelObject&&) = default;
    ModelObject& operator=(const ModelObject&) = default;
    ModelObject& operator=(ModelObject&&) = default;

public:
    virtual ~ModelObject() = default;
};

class Paddle: public ModelObject, public Rectangle {
public:
    Paddle(Point center, float w, float h);
};

class Ball: public ModelObject, public Circle {
    Ball(Point center, float r);
};

class Brick: public ModelObject, public Rectangle {
    Rectangle(Point center, float w, float h);
};

class Score: public ModelObject, public IntRectangle {
    Score(Point center, float w, float h, int score);
};

class Lives: public ModelObject, public IntRectangle {
    Lives(Point center, float w, float h, int score);
};

class Game {
public:
    int score;
    int lives;

    void reset();
    bool isGameOver();
};


class Level {
public:
    std::vector<std::shared_ptr<Brick>> bricks;
    void loadLevel(const std::string& filename);
};

#endif // MODEL_HPP