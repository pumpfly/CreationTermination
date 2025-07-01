#pragma once

#include <iostream>

#include "../Components/EnemyComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/SpriteComponent.h"

struct EnemyComponent;
using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;

class EnemySystem : public System{
public:
    explicit EnemySystem(Game &game, Entity* Creature) : System(game)
    {
        game.onBeforeUpdate.addListener([&, Creature] (Game &)
        {
            TransformComponent* creatureTransform = &Creature->getComponent<TransformComponent>();
            EnemyComponent* creature = &Creature->getComponent<EnemyComponent>();
            creatureMovement(game, creatureTransform, creature);
        });

        game.onStartup.addListener([&] (Game &) {
            //TODO: For loop should end at random number between 5 and 15
            for(int i = 0; i < 8; i++) {
                Entity* Bat = &game.entityManager.createEntity();
                EnemyComponent* bat = &Bat->addComponent<EnemyComponent>(MINIENEMY);
                TransformComponent* batTransfrom = &Bat->addComponent<TransformComponent>(game.origin, glm::vec2(200+ i*10, 200+i*10), 0, glm::vec2(50, 50));
                SpriteComponent* batSprite = &Bat->addComponent<SpriteComponent>("sprites/bat_Sprites.png");
                //TODO:: RenderSystem should call DrawSprite method after creating a Spritecomponent
                smallEnemies.push_back(Bat);
            }
        });
    }

    void creatureMovement(Game &game, TransformComponent* creatureTransform, EnemyComponent* creature);
    void creatureDefense();

    void smallEnemiesBehavior();
    void mediumEnemiesBehavior();
    void bigEnemiesBehavior();

    //small Enemy list
    std::vector <Entity*> smallEnemies;
};



