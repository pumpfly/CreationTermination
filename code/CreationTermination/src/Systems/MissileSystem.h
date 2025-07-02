#pragma once

#include "brewEngine/ecs/System.h"
#include "../Components/MissileComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;


class MissileSystem : public System{
    public:
    explicit MissileSystem(Game &game): System(game) {
        game.onAfterUpdate.addListener([&] (Game&) {
            game.componentManager.forEachComponent<MissileComponent>([&](MissileComponent& component) {
                Entity* Missile;
                TransformComponent* missileTransform;
                SpriteComponent* missileSprite;
                MissileComponent* missile;

                Missile = &game.entityManager.getEntity(component.entity());
                missileTransform = &Missile->getComponent<TransformComponent>();
                missileSprite = &Missile->getComponent<SpriteComponent>();
                missile = &Missile->getComponent<MissileComponent>();

                updateMissiles(game, missileTransform, missile);
                //drawMissiles(game, missileTransform, missileSprite);
            });
        });
    }

    void updateMissiles(Game& game, TransformComponent* missileTransform, MissileComponent* missileComponent);
    //void drawMissiles(Game& game, TransformComponent* missileTransform, SpriteComponent* missileSprite);
};
