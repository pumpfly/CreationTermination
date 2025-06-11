//
// Created by Lisa B on 02/05/2025.
//

#include "brewEngine/rendering/GeometryRenderer.h"

#include "brewEngine/Game.h"
#include "glad/glad.h"
#include "brewEngine/rendering/Shader.h"
#include "glm/ext/matrix_transform.hpp"
#include "brewEngine/rendering/Projection.h"

namespace gl3::brewEngine::rendering {
    GeometryRenderer::GeometryRenderer():
        shader(Shader("shaders/vertexShader.vert", "shaders/solid_color.frag")){}

    GeometryRenderer::~GeometryRenderer() {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }

    void GeometryRenderer::drawLine(glm::vec4 color, glm::vec2 p1, glm::vec2 p2) {
        float vertices[4] = {p1.x, p1.y, p2.x, p2.y};

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                                2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        this->shader.use();

        auto model = glm::identity<glm::mat4>();

        this->shader.setMatrix("model", model);
        this->shader.setMatrix("projection", ProjectionMatrix);
        this->shader.setVector("color", color);

        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);

    }
};
