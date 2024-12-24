#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../view/view.hpp"
#include "../model/model.hpp"
#include "../utils/allegro_includes.hpp"

#include <memory>

class InputHandler {
public:
    virtual bool isKeyPressed(int keyCode) = 0;
    virtual Point getMousePosition() = 0;
    virtual bool isMouseButtonPressed() = 0;
    virtual ~InputHandler() = default;
};

class AllegroInputHandler : public InputHandler {
public:
    AllegroInputHandler() = delete;
    AllegroInputHandler(const AllegroInputHandler&) = delete;
    AllegroInputHandler& operator=(const AllegroInputHandler&) = delete;
    AllegroInputHandler(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer);
    ~AllegroInputHandler();

    bool isKeyPressed(int keyCode) override;
    Point getMousePosition() override;
    bool isMouseButtonPressed() override;
private:
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;
};


class Controller {
public:
    Controller() = delete;
    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;
    explicit Controller(ALLEGRO_DISPLAY* display);
    ~Controller();

    void run();
     void must_init(bool test, const char *description);
     void must_init(void *test, const char *description);
private:
    ALLEGRO_DISPLAY *display = nullptr;
    InputHandler* inputHandler = nullptr;
    std::shared_ptr<GameObjectsDrawer> gameDrawer;
    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    bool done = false;
    bool draw = false;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER* timer = nullptr;
    ALLEGRO_EVENT_QUEUE* queue = nullptr;
    std::unique_ptr<DisplayManager> displayManager;
};

#endif // CONTROLLER_HPP