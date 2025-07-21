//
// Created by Lisa B on 02/05/2025.
//

#pragma once

#include "Shader.h"

namespace gl3::brewEngine::rendering {
    class GeometryRenderer {
    public:
        static GeometryRenderer &Instance() {
            static GeometryRenderer instance = GeometryRenderer();
            return instance;
        }

        void drawLine(glm::vec4 color, glm::vec2 p1, glm::vec2 p2);
        void drawCircle(glm::vec4 color, float cx, float cy, float r, int num_segments);


    private:
        GeometryRenderer();

        ~GeometryRenderer();

        Shader shader;

        unsigned int VAO{}, VBO{};
    };
};
