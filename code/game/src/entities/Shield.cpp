//
// Created by pumf on 07/12/2024.
//

#include "Shield.h"
#include "../Game.h"

namespace gl3 {
    Shield::Shield(gl3::Game *game, glm::vec2 position, float zRotation, glm::vec2 scale, Texture2D texture) : Entity(
                gl3::Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag"),
                gl3::Mesh({0.0f, 0.0f, 0.0f,
                    0.2f, 1.0f, 0.0f,
                    0.6f, 0.8f, 0.0f,
                    0.8f, 0.6f, 0.0f,
                    0.9f, 0.4f, 0.0f,
                    0.9f, -0.4f, 0.0f,
                    0.8f, -0.6f, 0.0f,
                    0.6f, -0.8f, 0.0f,
                    0.2f, -1.0f, 0.0f,
                    -0.2f, -1.0f, 0.0f,
                    -0.6f, -0.8f, 0.0f,
                    -0.8f, -0.6f, 0.0f,
                    -0.9f, -0.4f, 0.0f,
                    -0.9f, 0.4f, 0.0f,
                    -0.8f, 0.6f, 0.0f,
                    -0.6f, 0.8f, 0.0f,
                    -0.2f, 1.0f, 0.0f,
                },
                     {0, 1, 2,
                      0, 2, 3,
                      0, 3, 4,
                      0, 4, 5,
                      0, 5, 6,
                      0, 6, 7,
                      0, 7, 8,
                      0, 8, 9,
                      0, 9, 10,
                     0, 10, 11,
                     0, 11, 12,
                     0, 12, 13,
                     0, 13, 14,
                     0, 14, 15,
                     0, 15, 16,
                     0, 16, 1}),
                position,
                zRotation,
                scale,
                {1.0f, 1.0f, 1.0f, 0.5f}) {
    }

    void Shield::update(gl3::Game *game, float deltaTime) {
        position.y = getPosition().y;
        position.x = getPosition().x;
    }
}
