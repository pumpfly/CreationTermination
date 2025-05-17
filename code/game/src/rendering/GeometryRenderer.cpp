//
// Created by Lisa B on 02/05/2025.
//

#include "GeometryRenderer.h"

#include "../Game.h"
#include "glad/glad.h"
#include "../entities/Entity.h"
#include "projection/Projection.h"

namespace gl3 {
    GeometryRenderer::GeometryRenderer():
        tempS(gl3::Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag")),
        shader(&tempS){}

    GeometryRenderer::~GeometryRenderer() {
        glDeleteVertexArrays(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
    }

    void GeometryRenderer::drawLine(glm::vec2 p1, glm::vec2 p2) {
        float vertices[4] = {p1.x, p1.y, p2.x, p2.y};
        glm::vec4 color ={1.0, 0.0, 0.0, 1.0};
        glm::vec2 size = {10.0, 10.0};

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

        this->shader->use();


        auto model = glm::mat4(1.0f);

        this->shader->setMatrix("model", model);
        this->shader->setMatrix("projection", ProjectionMatrix);
        this->shader->setVector("color", color);

        glBindVertexArray(this->VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);

    }
};
