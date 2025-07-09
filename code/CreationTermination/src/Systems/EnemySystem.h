#pragma once

#include <iostream>
#include <random>

#include "../Components/EnemyComponent.h"
#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/SpriteComponent.h"

struct EnemyComponent;
using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::collision::ColliderComponent;

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

            std::mt19937 rng(dev());

            //std::uniform_real_distribution<> posYdist{50.0f, 70};
            //float posY = posYdist(rng);

            for(int i = 0; i < 4; i++) {

                Entity* Bat = &game.entityManager.createEntity();
                EnemyComponent* bat = &Bat->addComponent<EnemyComponent>(MINIENEMY);
                TransformComponent* batTransfrom = &Bat->addComponent<TransformComponent>(game.origin, glm::vec2(game.getContext().getWindowWidth()-500, 60 + 60*i*2.5f), 0, glm::vec2(50, 50), 50);
                SpriteComponent* batSprite = &Bat->addComponent<SpriteComponent>("sprites/bat_Sprites.png", glm::vec2(600, 500), 2, 5);
                ColliderComponent* batCollider = &Bat->addComponent<ColliderComponent>(ENEMY, [this](){});

                //std::cout << batTransfrom->localPosition.x << " " << batTransfrom->localPosition.y << std::endl;

                smallEnemies.push_back(Bat);
            }
        });

        game.onUpdate.addListener([&] (Game &)
        {
            game.componentManager.forEachComponent<EnemyComponent>([&] (EnemyComponent& enemy) {
                Entity* smallEnemy = nullptr;
                TransformComponent* smallEnemyTransform = nullptr;
                if(enemy.type == MINIENEMY) {
                    smallEnemy = &game.entityManager.getEntity(enemy.entity());
                    smallEnemyTransform = &smallEnemy->getComponent<TransformComponent>();
                }
                if(smallEnemyTransform != nullptr ) {
                    if(smallEnemyTransform->localPosition.x < 0) {
                        game.entityManager.deleteEntity(game.entityManager.getEntity(smallEnemyTransform->entity()));
                        smallEnemies.erase(smallEnemies.begin());
                    }
                    else {
                        smallEnemyBehavior(game, smallEnemyTransform, smallEnemyTransform->localPosition.y);
                    }
                }
            });
        });
    }

    void creatureMovement(Game &game, TransformComponent* creatureTransform, EnemyComponent* creature);
    void creatureDefense();

    void smallEnemyBehavior(Game& game, TransformComponent* smallEnemyTransfrom, float Ycoordinate);
    void mediumEnemiesBehavior();
    void bigEnemiesBehavior();

    float lerp(float a, float b, float f) {return a + f * (b - a);}

    //small Enemy list
    std::vector <Entity*> smallEnemies;

    std::random_device dev;
};



