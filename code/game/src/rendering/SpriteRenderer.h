#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Texture2D.h"


namespace gl3 {
    class SpriteRenderer {
    public:

        // Instance returns the current global instance of the SpriteRenderer.
        // The SpriteRenderer must be accessed through this method.
        static SpriteRenderer& Instance() {
            static SpriteRenderer instance = SpriteRenderer();
            return instance;
        }

        // Set the sprite renderers shader to a new shader.
        void SetShader(gl3::Shader& shader);

        // Reset the sprite renderers shader to the default shader.
        void SetDefaultShader();

        // Renders a defined quad textured with given sprite
        // TODO: fix game import
        void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(1.0f, 1.0f), float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));
        void DrawSpritePro(Texture2D &texture, glm::vec4 source, glm::vec4 dest, float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));
    private:
        SpriteRenderer();
        ~SpriteRenderer();

        void generateQuad(glm::vec2 topLeft, glm::vec2 bottomLeft, glm::vec2 bottomRight, glm::vec2 topRight);

        // Copying the instance must be prevented.
        SpriteRenderer(SpriteRenderer const&); // Do not implement copy constructor.
        void operator=(SpriteRenderer const&); // Do not implement assignment operator.

        gl3::Shader* shader; // The currently active shader.
        gl3::Shader defaultShader;
        unsigned int baseQuadVAO{};
        unsigned int baseQuadVBO{};

    };
}