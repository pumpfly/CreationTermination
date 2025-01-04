//
// Created by pumf on 07/12/2024.
//

#include "Shield.h"
#include "../Game.h"

namespace gl3 {
    Shield::Shield(gl3::Game *game, glm::vec2 position, float zRotation, glm::vec2 scale, Texture2D texture) : Entity(
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
