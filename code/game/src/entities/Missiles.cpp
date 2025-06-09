#include "Missiles.h"

#include <iostream>

#include "Entity.h"

namespace gl3 {
    Missiles::Missiles(glm::vec2 position, float zRotation, glm::vec2 size, float radius,
        glm::vec4 color, Texture2D texture, int health, TYPE type) : Entity(
            position,
            zRotation,
            size,
            radius,
            color,
            texture,
            health,
            type) {
    }
    void Missiles::update(gl3::Game *game, float deltaTime) {
        position.y = getPosition().y - sin(glm::radians(zRotation - 90.0f)) * speed * deltaTime;
        position.x = getPosition().x - cos(glm::radians(zRotation - 90.0f)) * speed * deltaTime;

    }

}
