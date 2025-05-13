//
// Created by pumf on 07/12/2024.
//

#include "bats.h"

#include "Creature.h"
#include "../Game.h"

namespace gl3 {
    bats::bats(glm::vec2 position, float zRotation, glm::vec2 scale, float radius, Texture2D texture, TYPE type) : Entity(
            position,
            zRotation,
            scale,
            radius,
            glm::vec4(0.35f, 0.35f, 0.35f, 1.0f),
            texture,
            type)
    {}

    float lerp2(float a, float b, float f)
    {
        return a + f * (b - a);
    }

    void bats::update(Game *game, float deltaTime) {
        /*std::time_t elapsedTime = std::time(nullptr);
        const auto shipPosition = game->getWitch()->getPosition();
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
