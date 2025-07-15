#define GLM_ENABLE_EXPERIMENTAL
#include "brewEngine/rendering/SpriteRenderer.h"
#include "brewEngine/rendering/Shader.h"
#include "brewEngine/rendering/Texture2D.h"
#include "glm/ext/matrix_transform.hpp"

#include "brewEngine/rendering/Projection.h"


namespace gl3::brewEngine::rendering {
    SpriteRenderer::SpriteRenderer() :
        defaultShader(Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag")),
        shader(&defaultShader) {
        // configure VAO/VBO
        float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &this->baseQuadVAO);
        glGenBuffers(1, &this->baseQuadVBO);

        glBindBuffer(GL_ARRAY_BUFFER, this->baseQuadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->baseQuadVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    SpriteRenderer::~SpriteRenderer() {
        glDeleteVertexArrays(1, &this->baseQuadVAO);
    }

    void SpriteRenderer::generateQuad(glm::vec2 topLeft, glm::vec2 bottomLeft, glm::vec2 bottomRight,
        glm::vec2 topRight) {
        float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, topLeft.x, topLeft.y,
            1.0f, 0.0f, bottomRight.x, bottomRight.y,
            0.0f, 0.0f, bottomLeft.x, bottomLeft.y,
            //
            0.0f, 1.0f, topLeft.x, topLeft.y,
            1.0f, 1.0f, topRight.x, topRight.y,
            1.0f, 0.0f, bottomRight.x, bottomRight.y
        };

        glBindBuffer(GL_ARRAY_BUFFER, this->baseQuadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->baseQuadVAO);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }

    void SpriteRenderer::SetShader(Shader& shader) {
        this->shader = &shader;
    }

    void SpriteRenderer::SetDefaultShader() {
        this->shader = &this->defaultShader;
    }

    void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec4 color) {
        this->shader->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));

        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::scale(model, glm::vec3(size, 1.0f));

        this->shader->setMatrix("model", model);
        this->shader->setMatrix("projection", ProjectionMatrix);
        this->shader->setVector("color", color);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glBindVertexArray(this->baseQuadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

    }

    // DrawSpriteSheet is important for animation
    void SpriteRenderer::DrawSpriteSheet(Texture2D &texture, glm::vec4 source, glm::vec4 dest, float rotate,
        glm::vec4 color) {

        glm::vec2 topLeft = glm::vec2(source.x/texture.Width, (source.y + source.w)/texture.Height);
        glm::vec2 bottomLeft = glm::vec2(source.x/texture.Width, source.y/texture.Height);
        glm::vec2 bottomRight = glm::vec2((source.x + source.z)/texture.Width, source.y/texture.Height);
        glm::vec2 topRight = glm::vec2((source.x + source.z)/texture.Width, (source.y + source.w)/texture.Height);

        generateQuad(topLeft, bottomLeft, bottomRight, topRight);

        this->shader->use();

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, glm::vec3(dest.x, dest.y, 0.0f));

        //model = glm::translate(model, glm::vec3(0.5f * dest.z, 0.5f * dest.w, 0.0f));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = glm::translate(model, glm::vec3(-0.5f * dest.z, -0.5f * dest.w, 0.0f));

        model = glm::scale(model, glm::vec3(dest.z, dest.w, 1.0f));


        this->shader->setMatrix("model", model);
        this->shader->setMatrix("projection", ProjectionMatrix);
        this->shader->setVector("color", color);

        glActiveTexture(GL_TEXTURE0);
        texture.Bind();

        glBindVertexArray(this->baseQuadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        generateQuad(glm::vec2(0, 1), glm::vec2(0.0f, 0.0f), glm::vec2(1, 0.0f), glm::vec2(1,1));
    }
}
