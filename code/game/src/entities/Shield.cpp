//
// Created by pumf on 07/12/2024.
//

#include "Shield.h"
#include "../Game.h"

namespace gl3 {
    Shield::Shield(gl3::Game *game, glm::vec2 position, float zRotation, glm::vec2 scale, float radius,
        Texture2D texture, int health, TYPE type) : Entity(
                position,
                zRotation,
                scale,
                radius,
                {1.0f, 1.0f, 1.0f, 0.5f},
                texture,
                health,
                type) {
    }

    void Shield::update(gl3::Game *game, float deltaTime) {
        position.y = getPosition().y;
        position.x = getPosition().x;
    }
}
