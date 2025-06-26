#include "MissileSystem.h"

#include <iostream>

#include "brewEngine/rendering/SpriteRenderer.h"


void MissileSystem::updateMissiles(Game& game, TransformComponent* missileTransform, MissileComponent* missileComponent) {
    missileTransform->localPosition.y -=
        sin(glm::radians(missileTransform->localZRotation - 90.0f)) * missileComponent->speed * game.getDeltaTime();
    missileTransform->localPosition.x -=
        cos(glm::radians(missileTransform->localZRotation - 90.0f)) * missileComponent->speed * game.getDeltaTime();
}

void MissileSystem::drawMissiles(Game &game, TransformComponent *missileTransform, SpriteComponent *missileSprite) {
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        missileSprite->sprite,
        missileTransform->localPosition,
        missileTransform->localScale,
        0,
        glm::vec4(1,1,1,1));
}
