#include <iostream>

#include "Game.h"
#include "Config.h"
#include "brewEngine/Config.h"

int main() {

    try {
        gl3::Game creationTermination(
            gl3::brewEngine::config::ScreenSize.x,
            gl3::brewEngine::config::ScreenSize.y,
            "Creation Termination"
        );
        creationTermination.init();
        creationTermination.run();
    }
    catch(const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    return 0;
}
