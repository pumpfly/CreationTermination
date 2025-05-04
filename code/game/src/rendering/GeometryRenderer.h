//
// Created by Lisa B on 02/05/2025.
//

#pragma once

#include <vector>

#include "Shader.h"
#include "glm/vec2.hpp"


namespace gl3 {
    class Game;
}

class GeometryRenderer {
public:

    static GeometryRenderer& Instance() {
        static GeometryRenderer instance = GeometryRenderer();
        return instance;
    }

    void drawLine(gl3::Game* game,glm::vec2 p1, glm::vec2 p2);

private:
    GeometryRenderer();
    ~GeometryRenderer();

    gl3::Shader *shader;
    gl3::Shader tempS;

    unsigned int VAO{}, VBO{};
};

