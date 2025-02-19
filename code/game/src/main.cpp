#include <iostream>

#include "Game.h"

int main() {

    try {
        gl3::Game creationTermination(1280, 720, "Space Battle");
        creationTermination.init();
        creationTermination.run();
    }
    catch(const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
