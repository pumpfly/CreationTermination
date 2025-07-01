#pragma once

#include <iostream>

#include "../Components/EnemyComponent.h"
#include "brewEngine/ecs/System.h"

struct EnemyComponent;
using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class EnemySystem : public System{
public:
    explicit EnemySystem(Game &game) : System(game)
    {
        game.onBeforeUpdate.addListener([&] (Game &)
        {
            Entity* Creature;
            TransformComponent* creatureTransform;
            EnemyComponent* creature;
            game.componentManager.forEachComponent<EnemyComponent>([&](EnemyComponent& enemyComponent) {
                if(enemyComponent.type == CREATURE) {
                    std::cout << "got in" << std::endl;                    Creature = &game.entityManager.getEntity(enemyComponent.entity());
                    creatureTransform = &Creature->getComponent<TransformComponent>();
                    creature = &Creature->getComponent<EnemyComponent>();
                }
                creatureMovement(game, creatureTransform, creature);
            });
        });

        game.onAfterUpdate.addListener([&] (Game &) {

        });
    }

    void creatureMovement(Game &game, TransformComponent* creatureTransform, EnemyComponent* creature);
    void creatureDefense();

    void smallEnemiesBehavior();
    void mediumEnemiesBehavior();
    void bigEnemiesBehavior();
};



