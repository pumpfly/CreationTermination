#include "SpriteRenderer.h"
#include "Shader.h"
#include "Texture2D.h"
#include "projection/Projection.h"


namespace gl3 {
    SpriteRenderer::SpriteRenderer() :
        defaultShader(gl3::Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag")),
        shader(&defaultShader) {
        // configure VAO/VBO
        unsigned int VBO;
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
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
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

    void SpriteRenderer::SetShader(gl3::Shader& shader) {
        this->shader = &shader;
    }

    void SpriteRenderer::SetDefaultShader() {
        this->shader = &this->defaultShader;
    }

    void SpriteRenderer::DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec4 color) {
        this->shader->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));

        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

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
}
