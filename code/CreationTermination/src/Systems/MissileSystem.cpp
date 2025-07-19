#include "MissileSystem.h"

#include <iostream>

#include "brewEngine/rendering/SpriteRenderer.h"

MissileSystem::MissileSystem(Game &game): System(game) {
    game.onAfterUpdate.addListener([&] (Game&) {
        if(game.getGameState() != GAME_ACTIVE) return;
        game.componentManager.forEachComponent<MissileComponent>([&](MissileComponent& component) {
            Entity* Missile;
            TransformComponent* missileTransform;
            SpriteComponent* missileSprite;
            MissileComponent* missile;

            Missile = &game.entityManager.getEntity(component.entity());
            missileTransform = &Missile->getComponent<TransformComponent>();
            missileSprite = &Missile->getComponent<SpriteComponent>();
            missile = &Missile->getComponent<MissileComponent>();

            if(missileTransform->localPosition.x > game.getContext().getWindowWidth() || missileTransform->localPosition.x < 0
                || missileTransform->localPosition.y > game.getContext().getWindowHeight() || missileTransform->localPosition.y < 0) {
                game.entityManager.deleteEntity(*Missile);
            }
            else {
                updateMissiles(game, missileTransform, missile);
            }
        });
    });
}

void MissileSystem::updateMissiles(Game& game, TransformComponent* missileTransform, MissileComponent* missileComponent) {
    missileTransform->localPosition.y -=
        sin(glm::radians(missileTransform->localZRotation - 90.0f)) * missileComponent->speed * game.getDeltaTime();
    missileTransform->localPosition.x -=
        cos(glm::radians(missileTransform->localZRotation - 90.0f)) * missileComponent->speed * game.getDeltaTime();
}
