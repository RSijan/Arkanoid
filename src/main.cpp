#include "view/view.hpp"
#include "controller/controller.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

const int windowWidth = 500;
const int windowHeight = 500;
const int fontSize = 20;
const std::string fontPath = "font/SourceCodePro-Regular.ttf";


int main() {
    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(nullptr)));
    try {
        DisplayInitializer displayInitializer(windowWidth, windowHeight, fontSize, fontPath);
        ALLEGRO_DISPLAY* display = displayInitializer.getDisplay();

        Controller controller(display);

        controller.run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}