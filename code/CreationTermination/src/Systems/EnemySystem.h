#pragma once

#include <iostream>
#include <random>

#include "../Components/EnemyComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/SpriteComponent.h"

struct EnemyComponent;
using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;

class EnemySystem : public System{
public:
    explicit EnemySystem(Game &game, Entity* Creature, Entity* Witch) : System(game)
    {
        game.onBeforeUpdate.addListener([&, Creature] (Game &)
        {
            TransformComponent* creatureTransform = &Creature->getComponent<TransformComponent>();
            EnemyComponent* creature = &Creature->getComponent<EnemyComponent>();
            creatureMovement(game, creatureTransform, creature);
        });

        game.onAfterStartup.addListener([&] (Game &) {
            //TODO: For loop should end at random number between 5 and 15

            std::mt19937 rng(dev());
            std::uniform_int_distribution<> distEnemyCount{5, 20};

            for(int i = 0; i < distEnemyCount(rng); i++) {

                std::uniform_int_distribution<> posXdist{game.getContext().getWindowWidth()/2, game.getContext().getWindowWidth()};
                std::uniform_int_distribution<> posYdist{0, 1};
                int posY;

                if (posYdist(rng) == 0)
                {
                    posY = -20;
                }
                else
                {
                    posY = game.getContext().getWindowHeight();
                }

                Entity* Bat = &game.entityManager.createEntity();
                EnemyComponent* bat = &Bat->addComponent<EnemyComponent>(MINIENEMY);
                TransformComponent* batTransfrom = &Bat->addComponent<TransformComponent>(game.origin, glm::vec2(posXdist(rng), posY), 0, glm::vec2(50, 50));
                SpriteComponent* batSprite = &Bat->addComponent<SpriteComponent>("sprites/bat_Sprites.png", glm::vec2(600, 500), 2, 5);

                smallEnemies.push_back(Bat);
            }
        });

        game.onUpdate.addListener([&, Witch] (Game &)
        {
            for (Entity* enemy : smallEnemies)
            {
                TransformComponent* enemyTransform = &enemy->getComponent<TransformComponent>();
                smallEnemyBehavior(game, &Witch->getComponent<TransformComponent>(), enemyTransform, 0.5f);
            }
        });
    }

    void creatureMovement(Game &game, TransformComponent* creatureTransform, EnemyComponent* creature);
    void creatureDefense();

    void smallEnemyBehavior(Game& game, TransformComponent* playerTransform, TransformComponent* smallEnemyTransfrom, float speed);
    void mediumEnemiesBehavior();
    void bigEnemiesBehavior();

    float lerp(float a, float b, float f) {return a + f * (b - a);}

    //small Enemy list
    std::vector <Entity*> smallEnemies;

    std::random_device dev;
};



