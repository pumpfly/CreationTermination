#include "Missile.h"

#include <iostream>

#include "Entity.h"
#include "../Game.h"

namespace gl3 {
    Missile::Missile(gl3::Game *game, glm::vec2 position, float zRotation, glm::vec2 scale, Texture2D texture) : Entity(
            Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag"),
            Mesh({0.0f, 0.0f, 0.0f,
                  0.0f, 0.5f, 0.0f,
                  0.2f, 0.4f, 0.0f,
                  0.2, -0.2, 0.0f,
                  0.3f, -0.3f, 0.0f,
                  0.3f, -0.4f, 0.0f,

                  -0.3f, -0.4f, 0.0f,
                  -0.3f, -0.3f, 0.0f,
                  -0.2, -0.2, 0.0f,
                  -0.2f, 0.4f, 0.0f},
                 {0, 1, 2,
                  0, 2, 3,
                  0, 3, 4,
                  0, 4, 5,
                  0, 5, 6,
                  0, 6, 7,
                  0, 7, 8,
                  0, 8, 9,
                  0, 9, 1}),
            position,
            zRotation,
            scale,
            {7.0f, 0.0f, 1.0f, 1.0f},
            texture) {
    }
    void Missile::update(gl3::Game *game, float deltaTime) {
        position.y = getPosition().y - sin(glm::radians(zRotation - 90.0f)) * speed * deltaTime;
        position.x = getPosition().x - cos(glm::radians(zRotation - 90.0f)) * speed * deltaTime;
    }

}
