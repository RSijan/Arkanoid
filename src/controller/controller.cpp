#include "controller.hpp"
#include "allegro5/allegro5.h"
#include "allegro5/allegro_primitives.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

AllegroInputHandler::AllegroInputHandler(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer) : queue(queue), timer(timer) {}
AllegroInputHandler::~AllegroInputHandler() {}
bool AllegroInputHandler::isKeyPressed(int keyCode) {
    ALLEGRO_EVENT event;
    al_peek_next_event(queue, &event);
    if (event.type == ALLEGRO_EVENT_KEY_DOWN){
        if(event.keyboard.keycode == keyCode){
            return true;
        }
    }
    return false;
}

Point AllegroInputHandler::getMousePosition() {
    ALLEGRO_EVENT event;
    al_peek_next_event(queue, &event);
    if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
        return {static_cast<float>(event.mouse.x), static_cast<float>(event.mouse.y)};
    }
    return {0, 0};
}
bool AllegroInputHandler::isMouseButtonPressed() {
    ALLEGRO_EVENT event;
    al_peek_next_event(queue, &event);
    if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        return true;
    }
    return false;
}


Controller::Controller(ALLEGRO_DISPLAY* display):display(display) {
    srand(static_cast<unsigned>(time(nullptr)));
    
    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    timer = al_create_timer(1.0/60);
    must_init(timer, "timer");

    queue = al_create_event_queue();
    must_init(queue, "queue");
        
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    inputHandler = new AllegroInputHandler(queue, timer);
    gameDrawer = std::make_shared<GameObjectsDrawer>(display);
    game = std::make_shared<Game>();
    level = std::make_shared<Level>();
    level->loadLevel("level1.txt");
    done = false;
    draw = true;
    displayManager = std::make_unique<DisplayManager>(display);
    al_start_timer(timer);
}
void Controller::run() {
    float paddle_x = 250;
    std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(Point{paddle_x, 480}, 100, 20);
    std::shared_ptr<Ball> ball = std::make_shared<Ball>(Point{250, 400}, 10);
    std::shared_ptr<Score> score = std::make_shared<Score>(Point{250, 20}, 50, 20, 0);
    std::shared_ptr<Lives> lives = std::make_shared<Lives>(Point{400, 20}, 50, 20, 3);
    while (!done) {
         if(draw){
            draw = false;
            displayManager->clearDisplay();

            gameDrawer->drawPaddle(paddle);
            gameDrawer->drawBall(ball);
            gameDrawer->drawBricks(level->bricks);
            gameDrawer->drawScore(score);
            gameDrawer->drawLives(lives);

            displayManager->flipDisplay();
         }
        al_wait_for_event(queue, &event);

        if (inputHandler->isKeyPressed(ALLEGRO_KEY_LEFT)) {
            paddle_x -= 50;
            std::cout << "Moved left" << std::endl;
            if (paddle_x < 0){
                paddle_x = 0;
            }
        }

        
        if(inputHandler->isKeyPressed(ALLEGRO_KEY_RIGHT)){
            paddle_x += 50;
            std::cout << "Moved right" << std::endl;
            if(paddle_x > 500) {
               paddle_x = 500;
            }
        }

        if(paddle){
            paddle->update(paddle_x);
        }

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                    //canvas.keyPressed(event.keyboard.keycode);
                break;
            case ALLEGRO_EVENT_TIMER:
                draw = true;
                break;
            default: {}
        }
    }

}


Controller::~Controller() {
    if (timer) {
        al_destroy_timer(timer);
        timer = nullptr;
    }

    if (queue) {
        al_destroy_event_queue(queue);
        queue = nullptr;
    }
    if(inputHandler){
       delete inputHandler;
       inputHandler = nullptr;
    }
}

void Controller::must_init(bool test, const char *description) {
    if (test) {
        return;
    }
    std::cerr << "couldn't initialize " << description << '\n';
    exit(1);
}

void Controller::must_init(void *test, const char *description) {
    must_init(test != nullptr, description);
}








// class AllegroInputHandler : public InputHandler {
// public:
//     AllegroInputHandler(ALLEGRO_EVENT_QUEUE* queue) : queue(queue) {}
//     bool isKeyPressed(int keyCode) override {
//         ALLEGRO_EVENT event;
//         while (al_get_next_event(queue, &event)) {
//             if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
//                 if(event.keyboard.keycode == keyCode) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }

//     Point getMousePosition() override {
//         ALLEGRO_EVENT event;
//         while (al_get_next_event(queue, &event)) {
//             if(event.type == ALLEGRO_EVENT_MOUSE_AXES) {
//                 return {static_cast<float>(event.mouse.x), static_cast<float>(event.mouse.y)};
//             }
//         }
//         return {0, 0};
//     }

//     bool isMouseButtonPressed() override {
//         ALLEGRO_EVENT event;
//         while (al_get_next_event(queue, &event)) {
//             if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
//                 return true;
//             }
//         }
//         return false;
//     }

// private:
//     ALLEGRO_EVENT_QUEUE* queue;
//     ALLEGRO_EVENT event;
//     ALLEGRO_TIMER* timer;
// };

// Controller::Controller(ALLEGRO_DISPLAY* display):display(display) {
//     srand(static_cast<unsigned>(time(nullptr)));
    
//     must_init(al_install_keyboard(), "keyboard");
//     must_init(al_install_mouse(), "mouse");

//     ALLEGRO_TIMER *timer = al_create_timer(1.0/60);
//     must_init(timer, "timer");

//     ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
//     must_init(queue, "queue");

        
//     al_register_event_source(queue, al_get_keyboard_event_source());
//     al_register_event_source(queue, al_get_display_event_source(display));
//     al_register_event_source(queue, al_get_mouse_event_source());
//     al_register_event_source(queue, al_get_timer_event_source(timer));

//     inputHandler= std::make_shared<AllegroInputHandler>(queue);
//     gameDrawer = std::make_shared<GameObjectsDrawer>(display);
//     game = std::make_shared<Game>();
//     level = std::make_shared<Level>();
//     level->loadLevel("level1.txt");
//     done = false;
//     draw = false;

//     al_start_timer(timer);
// }

// void Controller::run() {
//     while (!done) {
//         al_wait_for_event(queue, &event);
//         while (al_get_next_event(queue, &event)) {
//             switch (event.type) {
//                 case ALLEGRO_EVENT_DISPLAY_CLOSE:
//                     done = true;
//                     break;
//                 case ALLEGRO_EVENT_KEY_DOWN:
//                     // canvas.keyPressed(event.keyboard.keycode);
//                     break;
//                 case ALLEGRO_EVENT_TIMER:
//                     draw = true;
//                     al_stop_timer(timer);
//                     break;
//                 default: {}
                    
//             }
//         }
//     }

//     if(draw) {
//         draw = false;
//         al_start_timer(timer);
//         al_clear_to_color(al_map_rgb(255, 255, 255));

//         std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>(Point{250, 480}, 100, 20);
//         std::shared_ptr<Ball> ball = std::make_shared<Ball>(Point{250, 400}, 10);
//         std::shared_ptr<Score> score = std::make_shared<Score>(Point{250, 20}, 50, 20, 0);
//         std::shared_ptr<Lives> lives = std::make_shared<Lives>(Point{400, 20}, 50, 20, 3);


//         gameDrawer->drawPaddle(paddle);
//         gameDrawer->drawBall(ball);
//         gameDrawer->drawBricks(level->bricks);
//         gameDrawer->drawScore(score);
//         gameDrawer->drawLives(lives);

//         al_flip_display();
//     }
// }


// Controller::~Controller() {
//     if (timer) {
//         al_destroy_timer(timer);
//         timer = nullptr;
//     }

//     if (queue) {
//         al_destroy_event_queue(queue);
//         queue = nullptr;
//     }
// }

// void Controller::must_init(bool test, const char *description) {
//     if (test) {
//         return;
//     }
//     std::cerr << "couldn't initialize " << description << '\n';
//     exit(1);
// }

// void Controller::must_init(void *test, const char *description) {
//     must_init(test != nullptr, description);
// }