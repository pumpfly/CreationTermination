#include <iostream>
#include <leif.h>

#include "CTGame.h"
#include "brewEngine/Config.h"

int main() {
    try {
        CTGame creationTermination(
            1920,
            1080,
            "Creation Termination"
        );
        creationTermination.run();
    }
    catch(const std::exception &e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
    }

}
