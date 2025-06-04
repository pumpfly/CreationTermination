#include <iostream>

#include "Game.h"
#include "Config.h"
#include "../../BrewEngine/include/brewEngine/HelloWorld.h"

int main() {

    try {
        gl3::Game creationTermination(
            gl3::config::ScreenSize.x,
            gl3::config::ScreenSize.y,
            "Space Battle"
        );
        creationTermination.init();
        creationTermination.run();
    }
    catch(const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

    HelloWorld().print();

    return 0;
}
