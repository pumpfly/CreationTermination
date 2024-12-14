//
// Created by pumf on 07/12/2024.
//

#include "Minienemies.h"

#include "Enemy.h"
#include "../Game.h"

namespace gl3 {
    Minienemies::Minienemies(glm::vec3 position, float zRotation, float size) : Entity(
            Shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag"),
            Mesh({0.0f, 0.0f, 0.0f,
                        0.0f, -0.9f, 0.0f,
                        -0.6f, 0.5f, 0.0f,
                        -0.3f, 0.25f, 0.0f,
                        -0.2f, 0.65f, 0.0f,
                        -0.1f, 0.3f, 0.0f,

                        0.0f, 0.2f, 0.0f,

                        0.1f, 0.3f, 0.0f,
                        0.2f, 0.65f, 0.0f,
                        0.3f, 0.25f, 0.0f,
                        0.6f, 0.5f, 0.0f,
                    },
                    {
                        0, 1, 2, // triangle1
                        0, 3, 4, // triangle2
                        0, 5, 6, // triangle3
                        0, 6, 7, // triangle4
                        0, 8, 9,  // triangle5
                        0, 10, 1 // triangle6
                    }),
            position,
            zRotation,
            glm::vec3(size, size, size),
            glm::vec4(0.35f, 0.35f, 0.35f, 1.0f))
    {}

    float lerp2(float a, float b, float f)
    {
        return a + f * (b - a);
    }

    void Minienemies::update(Game *game, float deltaTime) {
        /*std::time_t elapsedTime = std::time(nullptr);
        const auto shipPosition = game->getShip()->getPosition();
        auto distanceToShip = glm::distance(position, shipPosition);
        float delta_x = this->getPosition().x - shipPosition.x;
        float delta_y = this->getPosition().y - shipPosition.y;
        float theta_radians = atan2(delta_y, delta_x);

        zRotation = glm::degrees(theta_radians) - 90.0f;
        if (distanceToShip >= 0.5f) {
            position.x = lerp2(position.x, shipPosition.x, deltaTime * speed);
            position.y = lerp2(position.y, shipPosition.y, deltaTime * speed);
        }*/

    }
}
