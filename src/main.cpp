#include "view/view.hpp"
#include "controller/controller.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

const int windowWidth = 500;
const int windowHeight = 500;
const int fontSize = 20;
const std::string fontPath = "SourceCodePro-Regular.ttf";


int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    
    try {
        DisplayInitializer DisplayInitializer(windowWidth, windowHeight, fontSize, fontPath);
        ALLEGRO_DISPLAY* display = DisplayInitializer.getDisplay();

        Controller controller(display);

        controller.run();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}