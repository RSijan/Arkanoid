#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <vector>

#include "../view/drawables.hpp"
#include "../utils/observer.hpp"

class ModelObject: public virtual Subject, public virtual Drawable {
protected:
    ModelObject() = default;
    ModelObject(const ModelObject&) = default;
    // ModelObject(ModelObject&&) = default;
    ModelObject& operator=(const ModelObject&) = default;
    // ModelObject& operator=(ModelObject&&) = default;

public:
    ModelObject(ModelObject&&) = delete;
    ModelObject& operator=(ModelObject&&) = delete;
    virtual ~ModelObject() = default;
};

class Paddle: public ModelObject, public Rectangle {
public:
    Paddle(Point center, float w, float h);
    void setX(int newX);
    void setY(int newY);
    void update(float x);
    ~Paddle() override = default;
};

class Ball: public ModelObject, public Circle {
public:
    Ball(Point center, float r);
    ~Ball() override = default;
    void update();
    Point velicity_;
};

class Brick: public virtual Drawable, public Rectangle {
public:
    Brick() = default;
    Brick(Point center, float w, float h);
private:
    Point center_;
    float w_, h_;
};

class Score: public ModelObject, public IntRectangle {
public:
    Score(Point center, float w, float h, int score);
};

class Lives: public ModelObject, public IntRectangle {
public:
    Lives(Point center, float w, float h, int score);
};

class Game {
public:
    static constexpr int INITIAL_LIVES = 3;
    static constexpr int INITIAL_SCORE = 0;
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