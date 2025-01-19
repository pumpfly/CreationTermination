#include "Missiles.h"

#include <iostream>

#include "Entity.h"
#include "../Game.h"

namespace gl3 {
    Missiles::Missiles(glm::vec2 position, float zRotation, glm::vec2 scale, float radius,
        glm::vec4 color, Texture2D texture, TYPE type) : Entity(
            position,
            zRotation,
            scale,
            radius,
            color,
            texture,
            type) {
    }
    void Missiles::update(gl3::Game *game, float deltaTime) {
        position.y = getPosition().y - sin(glm::radians(zRotation - 90.0f)) * speed * deltaTime;
        position.x = getPosition().x - cos(glm::radians(zRotation - 90.0f)) * speed * deltaTime;

    }

}
