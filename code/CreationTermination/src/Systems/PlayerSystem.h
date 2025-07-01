#pragma once

#include "../Components/PlayerComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/input/Input.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::input::Input;

class PlayerSystem : public System{
    public:
    explicit PlayerSystem(Game &game, Entity* Witch) : System(game) {
        game.onBeforeUpdate.addListener([&, Witch] (Game&) {
            TransformComponent* witchTransform = &Witch->getComponent<TransformComponent>();
            PlayerComponent* witch = &Witch->getComponent<PlayerComponent>();
            playerMovement(game, witchTransform);
            playerShooting(game, witchTransform, witch);
        });
    }

    void playerMovement(Game &game, TransformComponent* witchTransform);
    void playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer);
};

