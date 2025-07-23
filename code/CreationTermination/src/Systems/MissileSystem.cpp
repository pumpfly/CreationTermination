#include "MissileSystem.h"

#include <iostream>

#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/rendering/SpriteRenderer.h"

MissileSystem::MissileSystem(Game &game): System(game) {
    debugSprite = gl3::brewEngine::rendering::Texture2D::FromFile("sprites/radiusCircle.png");
    game.onAfterUpdate.addListener([&] (Game&) {
        if(game.getGameState() != gl3::brewEngine::GAME_ACTIVE) return;
        game.componentManager.forEachComponent<MissileComponent>([&](MissileComponent& component) {
            Entity* Missile;
            TransformComponent* missileTransform;
            MissileComponent* missile;
            gl3::brewEngine::collision::ColliderComponent* missileCollider;

            Missile = &game.entityManager.getEntity(component.entity());
            missileTransform = &Missile->getComponent<TransformComponent>();
            missile = &Missile->getComponent<MissileComponent>();
            missileCollider = &Missile->getComponent<gl3::brewEngine::collision::ColliderComponent>();

            missileCollider->invulnerabilityTimer -= game.getDeltaTime();

            if(missileCollider->invulnerabilityTimer <= 0) {
                missileCollider->isInvulnerable = false;
            }

            if(missileTransform->localPosition.x > game.getWindowWidth() || missileTransform->localPosition.x < 0
                || missileTransform->localPosition.y > game.getWindowHeight() || missileTransform->localPosition.y < 0) {
                game.entityManager.deleteEntity(*Missile);
            }
            else {
                updateMissiles(game, missile->goesToTheRight, missileTransform, missile);
            }
        });
    });
}

void MissileSystem::updateMissiles(Game& game, bool goesToTheRight, TransformComponent* missileTransform, MissileComponent* missileComponent) {
    float sign = 1;
    if(!goesToTheRight) sign = -1.0;

    missileTransform->localPosition.y -=
        sin(glm::radians(missileTransform->localZRotation - 180)) * missileComponent->speed * game.getDeltaTime() * sign;
    missileTransform->localPosition.x -=
        cos(glm::radians(missileTransform->localZRotation -180)) * missileComponent->speed * game.getDeltaTime() * sign;
}
