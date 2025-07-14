#include "EnemySystem.h"

#include <ctime>
#include "../Components/EnemyComponent.h"


EnemySystem::EnemySystem(Game &game, Entity *Creature): System(game) {
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
                EnemyComponent* smallEnemy = &SmallEnemy->addComponent<EnemyComponent>(SMALLENEMY);
                TransformComponent* smallEnemyTransform =
                        &SmallEnemy->addComponent<TransformComponent>(game.origin, glm::vec2(game.getContext().getWindowWidth()-500 + 120*j, 50 + 100*i), 0, glm::vec2(60, 50), 50);
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
                                healthC->health = healthC->health - 0.5f;
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

    // The actual Game core loop from the Enemies perspective
    game.onUpdate.addListener([&] (Game &)
    {
        if(currentTime >= 100) {
            currentTime = 0;
            difficulty++;
        }

        smallEnemySpawnCountdown -= game.getDeltaTime() * static_cast<float>(difficulty)*0.1;
        if(difficulty >= 2){mediumEnemySpawnCountdown -= game.getDeltaTime() * static_cast<float>(difficulty)*0.01;}
        if(difficulty >= 4){bigEnemySpawnCountdown -= game.getDeltaTime() * static_cast<float>(difficulty)*0.01;}

        std::mt19937 rng(dev());

        //Enemy Wave Size randomizer
        ////small enemies
        int SsmallestPossibleWaveSize = 3 + difficulty;
        int SbiggestPossibleWaveSize = 6 + difficulty;
        std::uniform_int_distribution<> SsizeDist{SsmallestPossibleWaveSize, SbiggestPossibleWaveSize};
        int SwaveSize = SsizeDist(rng);

        //medium and big spawn probability
        std::uniform_int_distribution<> spawnProbabilityDist{0, 100};
        ////medium enemies
        if(50 + difficulty*2 <= 100){MwillSpawn = (spawnProbabilityDist(rng) > 50 + difficulty);}
        int MsmallestPossibleWaveSize = 1;
        int MbiggestPossibleWaveSize = 3;
        std::uniform_int_distribution<> MsizeDist{MsmallestPossibleWaveSize, MbiggestPossibleWaveSize};
        int MwaveSize = MsizeDist(rng);

        ////big enemies
        if(30 + difficulty*2 <= 100){BwillSpawn = (spawnProbabilityDist(rng) > 30 + difficulty);}
        int BsmallestPossibleWaveSize = 1;
        int BbiggestPossibleWaveSize = 3;
        std::uniform_int_distribution<> BsizeDist{BsmallestPossibleWaveSize, BbiggestPossibleWaveSize};
        int BwaveSize = BsizeDist(rng);

        //Randomize space between enemies inside a wave
        std::uniform_real_distribution<> posdist{1, 4};
        float pos = posdist(rng);

        //spawning enemies
        ////small enemy spawner
        if(smallEnemySpawnCountdown <= 0) {
            for(int j = 0; j < SwaveSize; j++) {
                for(int i = 0; i < SwaveSize - difficulty; i++) {
                    Entity* SmallEnemy = &game.entityManager.createEntity();
                    EnemyComponent* smallEnemy = &SmallEnemy->addComponent<EnemyComponent>(SMALLENEMY);
                    TransformComponent* smallEnemyTransform =
                            &SmallEnemy->addComponent<TransformComponent>(game.origin, glm::vec2(game.getContext().getWindowWidth()-500 + 120*j + pos, 50*pos + 100*i + pos*10), 0, glm::vec2(60, 50), 50);
                    SpriteComponent* smallEnemySprite = &SmallEnemy->addComponent<SpriteComponent>("sprites/bat_Sprites.png", glm::vec2(600, 500), 2, 5);
                    HealthComponent* smallEnemyHealth = &SmallEnemy->addComponent<HealthComponent>(1);

                    //Collision Handling:
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
                                    healthC->health = healthC->health - 0.5f;
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
            smallEnemySpawnCountdown = smallEnemyCountdownReset;
        }
        ////medium enemey spawner
        if(difficulty > 2 && MwillSpawn && mediumEnemySpawnCountdown <= 0) {
            for(int j = 0; j < MwaveSize; j++) {
                for(int i = 0; i < MwaveSize; i++) {
                    Entity* MediumEnemy = &game.entityManager.createEntity();
                    EnemyComponent* mediumEnemy = &MediumEnemy->addComponent<EnemyComponent>(MEDIUMENEMY);
                    TransformComponent* mediumEnemyTransform =
                            &MediumEnemy->addComponent<TransformComponent>(game.origin, glm::vec2(game.getContext().getWindowWidth()-500 + 60*4*j + pos, 50 + 50*4*i + pos), 0, glm::vec2(60*2, 50*2), 50*2);
                    SpriteComponent* mediumEnemySprite = &MediumEnemy->addComponent<SpriteComponent>("sprites/bat_Sprites.png", glm::vec2(600, 500), 2, 5);
                    HealthComponent* mediumEnemyHealth = &MediumEnemy->addComponent<HealthComponent>(3);

                    //Collision Handling:
                    ColliderComponent* mediumEnemyCollider = &MediumEnemy->addComponent<ColliderComponent>(ENEMY, [&game, MediumEnemy]() {
                        if(MediumEnemy->isDeleted()) return;

                        //Fresh health component pointer to avoid garbage data
                        HealthComponent* healthC = &MediumEnemy->getComponent<HealthComponent>();
                        if(!healthC) return;
                        if(healthC->health == 0) {
                            game.entityManager.deleteEntity(*MediumEnemy);
                            return;
                        }

                        //getting new collider pointer to prevent stashing the mediumEnemyCollider itself inside the lambda function -> cycle
                        ColliderComponent* collider = &MediumEnemy->getComponent<ColliderComponent>();
                        if(!collider || !collider->currCollidingEntity) return;

                        Entity* collidingEntity = collider->currCollidingEntity;
                        if(collidingEntity && !collidingEntity->isDeleted()) {
                            if(game.componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
                                MissileComponent& missile = collidingEntity->getComponent<MissileComponent>();
                                if(missile.type == WAVE) {
                                    healthC->health = healthC->health - 0.5f;
                                }
                                else if(missile.type == CHARGE){
                                    HealthComponent& chargeMissileHealth = collidingEntity->getComponent<HealthComponent>();
                                    healthC->health = healthC->health - chargeMissileHealth.health;
                                }
                                else {
                                    healthC->health--;
                                }
                            }
                            else{
                                //collision with the Witch
                                healthC->health = 0;
                            }
                        }
                    });
                }
            }
        mediumEnemySpawnCountdown = mediumEnemyCountdownReset;
        }

        ///big enemey spawner
        if(difficulty > 4 && BwillSpawn && bigEnemySpawnCountdown <= 0) {
            for(int i = 0; i < BwaveSize; i++) {
                Entity* BigEnemy = &game.entityManager.createEntity();
                EnemyComponent* bigEnemy = &BigEnemy->addComponent<EnemyComponent>(BIGENEMY);
                TransformComponent* bigEnemyTransform =
                        &BigEnemy->addComponent<TransformComponent>(game.origin, glm::vec2((game.getContext().getWindowWidth()/2-50*4) + pos, -50*4), 0, glm::vec2(60*4, 50*4), 50*4);
                SpriteComponent* bigEnemySprite = &BigEnemy->addComponent<SpriteComponent>("sprites/bat_Sprites.png", glm::vec2(600, 500), 2, 5);
                HealthComponent* bigEnemyHealth = &BigEnemy->addComponent<HealthComponent>(5);

                //Collision Handling:
                ColliderComponent* bigEnemyCollider = &BigEnemy->addComponent<ColliderComponent>(ENEMY, [&game, BigEnemy]() {
                    if(BigEnemy->isDeleted()) return;

                    //Fresh health component pointer to avoid garbage data
                    HealthComponent* healthC = &BigEnemy->getComponent<HealthComponent>();
                    if(!healthC) return;
                    if(healthC->health == 0) {
                        game.entityManager.deleteEntity(*BigEnemy);
                        return;
                    }

                    //getting new collider pointer to prevent stashing the mediumEnemyCollider itself inside the lambda function -> cycle
                    ColliderComponent* collider = &BigEnemy->getComponent<ColliderComponent>();
                    if(!collider || !collider->currCollidingEntity) return;

                    Entity* collidingEntity = collider->currCollidingEntity;
                    if(collidingEntity && !collidingEntity->isDeleted()) {
                        if(game.componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
                            MissileComponent& missile = collidingEntity->getComponent<MissileComponent>();
                            if(missile.type == WAVE) {
                                healthC->health = healthC->health - 0.5f;
                            }
                            else if(missile.type == CHARGE){
                                HealthComponent& chargeMissileHealth = collidingEntity->getComponent<HealthComponent>();
                                healthC->health = healthC->health - chargeMissileHealth.health;
                            }
                            else {
                                healthC->health--;
                            }
                        }
                        else{
                            //collision with the Witch
                            healthC->health = 0;
                        }
                    }
                });
            }
            bigEnemySpawnCountdown = bigEnemyCountdownReset;
        }

        //Managing enemies
        game.componentManager.forEachComponent<EnemyComponent>([&] (EnemyComponent& enemy) {
            Entity* Enemy = nullptr;
            TransformComponent* enemyTransform = nullptr;
            Enemy = &game.entityManager.getEntity(enemy.entity());
            enemyTransform = &Enemy->getComponent<TransformComponent>();

            if(enemy.type == SMALLENEMY) {
                if(enemyTransform != nullptr ) {
                    if(enemyTransform->localPosition.x < -enemyTransform->localScale.x) {
                        game.entityManager.deleteEntity(game.entityManager.getEntity(enemyTransform->entity()));
                    }
                    else {
                        smallEnemyBehavior(game, enemyTransform, enemyTransform->localPosition.y);
                    }
                }
            }
            else if(enemy.type == MEDIUMENEMY) {
                if(enemyTransform != nullptr ) {
                    if(enemyTransform->localPosition.x < -enemyTransform->localScale.x) {
                        game.entityManager.deleteEntity(game.entityManager.getEntity(enemyTransform->entity()));
                    }
                    else {
                        mediumEnemiesBehavior(game, enemyTransform, enemyTransform->localPosition.y);
                    }
                }
            }
            else if(enemy.type == BIGENEMY) {
                if(enemyTransform != nullptr ) {
                    bigEnemiesBehavior(game, enemyTransform, &Enemy->getComponent<EnemyComponent>());
                }
            }
        });
    });
}

void EnemySystem::creatureMovement(Game& game, TransformComponent* creatureTransform, EnemyComponent* creature)
{
    std::time_t elapsedTime = std::time(nullptr);
    //zRotation = glm::degrees(theta_radians) - 90.0f;

    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{-1.2f, 500.0f};

    creature->countdown -= game.getDeltaTime();
    for(int i = 0; i < 20; i++) {
        if(creature->countdown <= 0) {
            creature->newPosition = dist(rng);
            creature->countdown = creature->positionChangeTime;
        }
    }
    creatureTransform->localPosition.y = lerp(creatureTransform->localPosition.y, creature->newPosition,
        game.getDeltaTime() * creature->speed);

}

void EnemySystem::smallEnemyBehavior(Game& game, TransformComponent* smallEnemyTransfrom, float YCoordinate)
{
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{5, 20};

    std::uniform_real_distribution<> waveLengthDist{90, 120};
    float waveLength = waveLengthDist(rng);

    smallEnemyTransfrom->localPosition.y = cos(smallEnemyTransfrom->localPosition.x / 50) + YCoordinate;
    smallEnemyTransfrom->localPosition.x--;

}

void EnemySystem::mediumEnemiesBehavior(Game& game, TransformComponent* mediumEnemyTransform, float YCoordinate) {
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{5, 20};

    std::uniform_real_distribution<> waveLengthDist{90, 120};
    float waveLength = waveLengthDist(rng);

    mediumEnemyTransform->localPosition.y = cos(mediumEnemyTransform->localPosition.x / 50) + YCoordinate;
    mediumEnemyTransform->localPosition.x--;
}

void EnemySystem::bigEnemiesBehavior(Game& game, TransformComponent* bigEnemyTransform, EnemyComponent* bigEnemy) {
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{5, 20};

    std::uniform_real_distribution<> waveLengthDist{90, 120};
    float waveLength = waveLengthDist(rng);

    bigEnemyTransform->localPosition.y++;
    bigEnemyTransform->localPosition.x--;
}

