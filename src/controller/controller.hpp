#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP
#include "allegro5/allegro5.h"
#include "../view/view.hpp"
#include "../model/model.hpp"

#include <memory>

class InputHandler {
    public:
        virtual ~InputHandler() = default;
        virtual bool isKeyPressed(int keyCode) = 0;
        virtual Point getMousePosition() = 0;
        virtual bool isMouseButtonPressed() = 0;
    
};

class Controller {
 public:
    Controller(ALLEGRO_DISPLAY* display);
    ~Controller() = default;
    void run();

private:
    ALLEGRO_DISPLAY *display;
    std::shared_ptr<InputHandler> inputHandler;
    std::shared_ptr<GameObjectsDrawer> gameDrawer;
    std::shared_ptr<Game> game;
    std::shared_ptr<Level> level;
    bool done;
    bool draw;
    ALLEGRO_EVENT event;

    void must_init(bool test, const char *description);
    void must_init(void *test, const char *description);
    ALLEGRO_EVENT_QUEUE* queue = nullptr;
    ALLEGRO_TIMER* timer = nullptr;
};

#endif // CONTROLLER_HPP