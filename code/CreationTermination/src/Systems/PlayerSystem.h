#pragma once

#include <iostream>
#include <ostream>

#include "../Components/PlayerComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/input/Input.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::input::Input;

class PlayerSystem : public System{
    public:
    explicit PlayerSystem(Game &game) : System(game) {
        game.onBeforeUpdate.addListener([&] (Game&) {
            Entity* Witch;
            TransformComponent* witchTransform;
            PlayerComponent* witchPlayer;
            game.componentManager.forEachComponent<PlayerComponent>([&](PlayerComponent& component) {
                Witch = &game.entityManager.getEntity(component.entity());
                witchTransform = &Witch->getComponent<TransformComponent>();
                witchPlayer = &Witch->getComponent<PlayerComponent>();

                playerMovement(game, witchTransform);
                playerShooting(game, witchTransform, witchPlayer);
            });
        });
    }

    void playerMovement(Game &game, TransformComponent* witchTransform);
    void playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer);
};

