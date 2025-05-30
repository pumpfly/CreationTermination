//
// Created by pumf on 07/12/2024.
//

#include "bats.h"

#include "Creature.h"
#include "../Game.h"

namespace gl3 {
    bats::bats(glm::vec2 position, float zRotation, glm::vec2 scale, float radius, Texture2D texture, int health, TYPE type)
    : Entity(
            position,
            zRotation,
            scale,
            radius,
            glm::vec4(0.35f, 0.35f, 0.35f, 1.0f),
            texture,
            health,
            type)
    {}

    float lerp2(float a, float b, float f)
    {
        return a + f * (b - a);
    }

    void bats::update(Game *game, float deltaTime) {
        const auto shipPosition = game->getWitch()->getPosition();
        auto distanceToWitch = glm::distance(position, shipPosition);

        if (distanceToWitch >= 0.5f) {
            position.x = lerp2(position.x, shipPosition.x, deltaTime * speed);
            position.y = lerp2(position.y, shipPosition.y, deltaTime * speed);
        }

        this->spriteAnimTimer += deltaTime;
        if (this->spriteAnimTimer >= 0.1f) {
            this->spriteAnimIndex = (this->spriteAnimIndex + 1) % 2;
            this->spriteAnimTimer = 0.0f;
        }

    }

    void bats::draw() {
        SpriteRenderer::Instance().DrawSpritePro(texture, glm::vec4(this->spriteFrameSize.x*this->spriteAnimIndex, 0, this->spriteFrameSize),
                                                 glm::vec4(this->position, this->size), zRotation, this->color);
    }
}
