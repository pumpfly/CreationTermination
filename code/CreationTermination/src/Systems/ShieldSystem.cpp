#include "ShieldSystem.h"

#include "../Components/ShieldComponent.h"

ShieldSystem::ShieldSystem(Game &game): System(game) {
    game.onUpdate.addListener([](Game& game, float dt) {
        if(game.getGameState() != GAME_ACTIVE) return;
        game.componentManager.forEachComponent<ShieldComponent>([&](ShieldComponent& shieldComponent) {
            Entity* shieldEntity;
            TransformComponent* shieldTransform;

            shieldEntity = &game.entityManager.getEntity(shieldComponent.entity());
            shieldTransform = &shieldEntity->getComponent<TransformComponent>();

            shieldTransform->localPosition = shieldComponent.follows->localPosition - shieldComponent.offset;

            shieldComponent.activeTimer += dt;
            if (shieldComponent.activeTimer >= shieldComponent.lifetime) {
                shieldComponent.endFunc();
                game.entityManager.deleteEntity(*shieldEntity);
            }
        });
    });
}

