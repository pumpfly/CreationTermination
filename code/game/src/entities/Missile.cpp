#include "Missile.h"

#include <iostream>

#include "Entity.h"
#include "../Game.h"

namespace gl3 {
    Missile::Missile(gl3::Game *game, glm::vec2 position, float zRotation, glm::vec2 scale, Texture2D texture) : Entity(
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
