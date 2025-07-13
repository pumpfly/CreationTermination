#pragma once

#include <iostream>
#include <random>

#include "../Components/EnemyComponent.h"
#include "../Components/MissileComponent.h"
#include "../Components/PlayerComponent.h"
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
            for(int j = 0; j < 4; j++) {
                for(int i = 0; i < 4; i++) {
                Entity* SmallEnemy = &game.entityManager.createEntity();
                EnemyComponent* smallEnemy = &SmallEnemy->addComponent<EnemyComponent>(MINIENEMY);
                TransformComponent* smallEnemyTransform =
                    &SmallEnemy->addComponent<TransformComponent>(game.origin, glm::vec2(game.getContext().getWindowWidth()-500 + 60*j, 60 + 60*i*2.5f), 0, glm::vec2(50, 50), 50);
                SpriteComponent* smallEnemySprite = &SmallEnemy->addComponent<SpriteComponent>("sprites/bat_Sprites.png", glm::vec2(600, 500), 2, 5);
                HealthComponent* smallEnemyHealth = &SmallEnemy->addComponent<HealthComponent>(1);
                ColliderComponent* smallEnemyCollider = &SmallEnemy->addComponent<ColliderComponent>(ENEMY, [&game, SmallEnemy]() {
                    if(SmallEnemy->isDeleted()) return;

                    HealthComponent* healthC = &SmallEnemy->getComponent<HealthComponent>();
                    if(!healthC) return;

                    if(healthC->health == 0) {
                        game.entityManager.deleteEntity(*SmallEnemy);
                        return;
                    }

                    ColliderComponent* collider = &SmallEnemy->getComponent<ColliderComponent>();
                    if(!collider || !collider->currCollidingEntity) return;

                    Entity* collidingEntity = collider->currCollidingEntity;
                    if(collidingEntity && !collidingEntity->isDeleted()) {
                        if(game.componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
                                MissileComponent& missile = collidingEntity->getComponent<MissileComponent>();
                                if(missile.type == WAVE) {
                                    std::cout << "WAVE hit - Health before: " << healthC->health << std::endl;
                                    healthC->health = healthC->health - 0.5f;
                                    std::cout << "WAVE hit - Health after: " << healthC->health << std::endl;
                                }
                                else{
                                    healthC->health = 0;
                                }
                            }
                            else{
                                healthC->health = 0;
                            }
                        }
                    });
                }
            }
        });

        game.onUpdate.addListener([&] (Game &)
        {
            //std::mt19937 rng(dev());
            //std::uniform_real_distribution<> posYdist{50.0f, 70};
            //float posY = posYdist(rng);

            if(game.currentTime == 0) {

            }
            game.componentManager.forEachComponent<EnemyComponent>([&] (EnemyComponent& enemy) {
                Entity* smallEnemy = nullptr;
                TransformComponent* smallEnemyTransform = nullptr;
                if(enemy.type == MINIENEMY) {
                    smallEnemy = &game.entityManager.getEntity(enemy.entity());
                    smallEnemyTransform = &smallEnemy->getComponent<TransformComponent>();
                    if(smallEnemyTransform != nullptr ) {
                        if(smallEnemyTransform->localPosition.x < -smallEnemyTransform->localScale.x) {
                            game.entityManager.deleteEntity(game.entityManager.getEntity(smallEnemyTransform->entity()));
                        }
                        else {
                            smallEnemyBehavior(game, smallEnemyTransform, smallEnemyTransform->localPosition.y);
                        }
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
    std::random_device dev;

};



