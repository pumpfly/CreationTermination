
#pragma once

#include "brewEngine/ecs/System.h"

struct EnemyComponent;
using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class EnemySystem : public System{
public:
    explicit EnemySystem(Game &game) : System(game)
    {
        game.onStartup.addListener([&] (Game &)
        {

        });
    }

    void creatureMovement(TransformComponent* creatureTransform, EnemyComponent* creature, float deltaTime);
    void creatureDefense();

    void smallEnemiesBehavior();
    void mediumEnemiesBehavior();
    void largeEnemiesBehavior();
};



