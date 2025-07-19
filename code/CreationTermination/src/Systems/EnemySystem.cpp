#include "EnemySystem.h"

#include <ctime>
#include <iostream>

#include "../Components/EnemyComponent.h"


EnemySystem::EnemySystem(Game &game, Entity *Creature): System(game) {
    smallEnemyTexture = Texture2D::FromFile("sprites/bat_Sprites.png");
    mediumEnemyTexture = Texture2D::FromFile("sprites/BirdOfPrey.png");
    bigEnemyTexture = Texture2D::FromFile("sprites/dragonIdle.png");
    for(int j = 0; j < 4; j++) {
            for(int i = 0; i < 4; i++) {
                Entity* SmallEnemy = &game.entityManager.createEntity();
                EnemyComponent* smallEnemy = &SmallEnemy->addComponent<EnemyComponent>(SMALLENEMY, true, false, false, false);
                TransformComponent* smallEnemyTransform =
                        &SmallEnemy->addComponent<TransformComponent>(game.origin,
                            glm::vec2(game.getContext().getWindowWidth() + 120*j, 50 + 100*i),
                            0,
                            glm::vec2(60, 50), 50);
                SpriteComponent* smallEnemySprite = &SmallEnemy->addComponent<SpriteComponent>(
                    smallEnemyTexture,
                    glm::vec2(600, 500),
                    2,
                    5,
                    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
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

    game.onBeforeUpdate.addListener([&, Creature] (Game & g)
    {
        if(game.getGameState() != GAME_ACTIVE) return;

        TransformComponent* creatureTransform = &Creature->getComponent<TransformComponent>();
        EnemyComponent* creature = &Creature->getComponent<EnemyComponent>();
        ColliderComponent* creatureCollider = &Creature->getComponent<ColliderComponent>();
        SpriteComponent* creatureSprite = &Creature->getComponent<SpriteComponent>();
        creatureMovement(g, creatureTransform, creature, 1.5);

        if(creatureCollider->isInvulnerable && creatureCollider->invulnerabilityTimer > 0) {
            creatureCollider->invulnerabilityTimer -= g.getDeltaTime();
            creatureSprite->color = glm::vec4(1, 0, 0, 1);
        }
        else {
            creatureSprite->color = glm::vec4(1, 1, 1, 1);
            creatureCollider->invulnerabilityTimer = creatureCollider->timeBetweenDamage;
            creatureCollider->isInvulnerable = false;
        }

    });

    game.onUpdate.addListener([&] (Game & g, float deltaTime) {
        if(game.getGameState() != GAME_ACTIVE) return;

        currentTime += deltaTime;

        if(currentTime >= 30) {
            currentTime = 0;
            difficulty++;
        }

        smallEnemySpawnCountdown -= deltaTime * static_cast<float>(difficulty)*0.2;
        if(difficulty >= 2){mediumEnemySpawnCountdown -= deltaTime * static_cast<float>(difficulty)*0.1;}
        if(difficulty >= 4){bigEnemySpawnCountdown -= deltaTime * static_cast<float>(difficulty)*0.05;}

        std::mt19937 rng(dev());

        //Enemy Wave Size randomizer
        ////small enemies
        int SsmallestPossibleWaveSize = 3;
        int SbiggestPossibleWaveSize = 6;
        std::uniform_int_distribution<> SsizeDist{SsmallestPossibleWaveSize, SbiggestPossibleWaveSize};
        int SwaveSize = SsizeDist(rng);

        //medium and big spawn probability
        std::uniform_int_distribution<> spawnProbabilityDist{0, 100};
        ////medium enemies
        //if(50 + difficulty*2 <= 100){MediumWillSpawn = (spawnProbabilityDist(rng) < 70 + difficulty);}
        int MsmallestPossibleWaveSize = 2;
        int MbiggestPossibleWaveSize = 4;
        std::uniform_int_distribution<> MsizeDist{MsmallestPossibleWaveSize, MbiggestPossibleWaveSize};
        int MwaveSize = MsizeDist(rng);

        ////big enemies
        if(30 + difficulty*2 <= 100){BigWillSpawn = (spawnProbabilityDist(rng) < 70 + difficulty);}
        int BsmallestPossibleWaveSize = 1;
        int BbiggestPossibleWaveSize = 3;
        std::uniform_int_distribution<> BsizeDist{BsmallestPossibleWaveSize, BbiggestPossibleWaveSize};
        int BwaveSize = BsizeDist(rng);

        //Randomize space between enemies inside a wave
        std::uniform_real_distribution<> posdist{1, 4};
        float pos = posdist(rng);

        //change from one enemy behavior to another
        // If behaviorChanger = 1 it will be either a sinus or cosinus curve
        // If behaviorChanger = 0 the enemy will move diagonal across the screen
        std::uniform_int_distribution<> oneOrTheOther{0, 1};
        int behaviorChanger = oneOrTheOther(rng);
        //For the diagonal movement behavior method: Either the enemy comes from above or below
        int UpOrDown = oneOrTheOther(rng);
        //For the enemyCosSinMovement method: Either the enemy follows a cos line or a sin line
        int isCosOrSin = oneOrTheOther(rng);

        // for deciding what method should be called for the behavior of the enemies
        bool cos = false;
        bool sin = false;
        bool diagonalUp = false;
        bool diagonalDown = false;

        //spawning enemies
        ////small enemy spawner
        if(smallEnemySpawnCountdown <= 0) {

            // will be changed according to the enemy behavior and used for the creation of the enemies transform
            glm::vec2 currLocalPos = glm::vec2(0, 0);

            if(behaviorChanger == 1) {
                if(isCosOrSin == 1) {cos = true;}
                else {sin = true;}
            }
            else {
                if(UpOrDown == 1) {
                    diagonalUp = true;
                    currLocalPos = glm::vec2(g.getContext().getWindowWidth() + 60, g.getContext().getWindowHeight() + 50);
                }
                else {
                    diagonalDown = true;
                    currLocalPos = glm::vec2(g.getContext().getWindowWidth() + 60, 0);
                }
            }

            //Even though Clion represents the coming code as not being used, it is definitely being used.

            for(int j = 0; j < SwaveSize; j++) {
                for(int i = 0; i < SwaveSize - difficulty; i++) {
                    if(cos || sin) {
                        currLocalPos = glm::vec2(g.getContext().getWindowWidth() + 120*j + pos, 50*pos + 100*i);
                    }
                    else {
                        //offset between the line of enemies
                        currLocalPos.x = currLocalPos.x + pos*30;
                    }
                    Entity* SmallEnemy = &g.entityManager.createEntity();
                    EnemyComponent* smallEnemy =
                        &SmallEnemy->addComponent<EnemyComponent>(SMALLENEMY, cos, sin, diagonalUp, diagonalDown);
                    TransformComponent* smallEnemyTransform =
                            &SmallEnemy->addComponent<TransformComponent>(g.origin,
                                currLocalPos,
                                0,
                                glm::vec2(60, 50), 50);
                    SpriteComponent* smallEnemySprite =
                        &SmallEnemy->addComponent<SpriteComponent>(
                            smallEnemyTexture,
                            glm::vec2(600, 500),
                            2,
                            5,
                            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                    HealthComponent* smallEnemyHealth = &SmallEnemy->addComponent<HealthComponent>(1);

                    //Collision Handling:
                    ColliderComponent* smallEnemyCollider = &SmallEnemy->addComponent<ColliderComponent>(ENEMY, [&g, SmallEnemy]{
                        if(SmallEnemy->isDeleted()) return;

                        HealthComponent* healthC = &SmallEnemy->getComponent<HealthComponent>();
                        if(!healthC) return;

                        if(healthC->health == 0) {
                            g.entityManager.deleteEntity(*SmallEnemy);
                            return;
                        }

                        ColliderComponent* collider = &SmallEnemy->getComponent<ColliderComponent>();
                        if(!collider || !collider->currCollidingEntity) return;

                        Entity* collidingEntity = collider->currCollidingEntity;
                        if(collidingEntity && !collidingEntity->isDeleted()) {
                            if(g.componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
                                auto& missile = collidingEntity->getComponent<MissileComponent>();
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
        if(difficulty >= 2 && mediumEnemySpawnCountdown <= 0) {

            // will be changed according to the enemy behavior and used for the creation of the enemies transform
            glm::vec2 currLocalPos = glm::vec2(0, 0);

            if(behaviorChanger == 1) {
                if(isCosOrSin == 1) {cos = true;}
                else {sin = true;}
            }
            else {
                // Deciding the spawn point of the first enemy of the wave
                if(UpOrDown == 1) {
                    diagonalUp = true;
                    currLocalPos = glm::vec2(g.getContext().getWindowWidth()+60*2, g.getContext().getWindowHeight()+50*2);
                }
                else {
                    diagonalDown = true;
                    currLocalPos = glm::vec2(g.getContext().getWindowWidth()+60*2, 0);
                }
            }

            for(int j = 0; j < MwaveSize; j++) {
                for(int i = 0; i < MwaveSize; i++) {
                    if(cos || sin) {
                        currLocalPos = glm::vec2(g.getContext().getWindowWidth() + 120*j*1.5 + pos, pos*50*1.5 + 100*i);
                    }
                    else {
                        //offset between enemies
                        currLocalPos.x = currLocalPos.x + pos*30*1.5;
                    }
                    Entity* MediumEnemy = &g.entityManager.createEntity();
                    EnemyComponent* mediumEnemy = &MediumEnemy->addComponent<EnemyComponent>(MEDIUMENEMY, cos, sin, diagonalUp, diagonalDown);
                    TransformComponent* mediumEnemyTransform =
                            &MediumEnemy->addComponent<TransformComponent>(g.origin,
                                currLocalPos,
                                0,
                                glm::vec2(60*2, 50*2),
                                50*2);
                    SpriteComponent* mediumEnemySprite =
                        &MediumEnemy->addComponent<SpriteComponent>(
                            mediumEnemyTexture,
                            glm::vec2(600, 500),
                            2,
                            5,
                            glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                    HealthComponent* mediumEnemyHealth = &MediumEnemy->addComponent<HealthComponent>(5);

                    //Collision Handling:
                    ColliderComponent* mediumEnemyCollider = &MediumEnemy->addComponent<ColliderComponent>(ENEMY, [&g, MediumEnemy]() {
                        if(MediumEnemy->isDeleted()) return;

                        //Fresh health component pointer to avoid garbage data
                        HealthComponent* healthC = &MediumEnemy->getComponent<HealthComponent>();
                        if(!healthC) return;
                        if(healthC->health == 0) {
                            g.entityManager.deleteEntity(*MediumEnemy);
                            return;
                        }

                        //getting new collider pointer to prevent stashing the mediumEnemyCollider itself inside the lambda function -> cycle
                        ColliderComponent* collider = &MediumEnemy->getComponent<ColliderComponent>();
                        if(!collider || !collider->currCollidingEntity) return;

                        Entity* collidingEntity = collider->currCollidingEntity;
                        if(collidingEntity && !collidingEntity->isDeleted()) {
                            if(g.componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
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
        ///BigWillSpawn
        if(BigWillSpawn && difficulty >= 4 && bigEnemySpawnCountdown <= 0) {
            for(int i = 0; i < BwaveSize; i++) {
                Entity* BigEnemy = &g.entityManager.createEntity();
                EnemyComponent* bigEnemy = &BigEnemy->addComponent<EnemyComponent>(BIGENEMY);
                TransformComponent* bigEnemyTransform =
                        &BigEnemy->addComponent<TransformComponent>(g.origin,
                            glm::vec2((g.getContext().getWindowWidth()/2-50*3 - i*60*3) + pos, -50*3),
                            0,
                            glm::vec2(60*4, 50*4),
                            50*4);
                SpriteComponent* bigEnemySprite = &BigEnemy->addComponent<SpriteComponent>(
                    bigEnemyTexture,
                    glm::vec2(600, 500),
                    2,
                    5,
                    glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
                HealthComponent* bigEnemyHealth = &BigEnemy->addComponent<HealthComponent>(100);

                //Collision Handling:
                ColliderComponent* bigEnemyCollider = &BigEnemy->addComponent<ColliderComponent>(ENEMY, [&g, BigEnemy]() {
                    if(BigEnemy->isDeleted()) return;

                    //Fresh health component pointer to avoid garbage data
                    HealthComponent* healthC = &BigEnemy->getComponent<HealthComponent>();
                    if(!healthC) return;
                    if(healthC->health <= 0) {
                        g.entityManager.deleteEntity(*BigEnemy);
                        return;
                    }

                    //getting new collider pointer to prevent stashing the mediumEnemyCollider itself inside the lambda function -> cycle
                    ColliderComponent* collider = &BigEnemy->getComponent<ColliderComponent>();
                    if(!collider || !collider->currCollidingEntity) return;

                    Entity* collidingEntity = collider->currCollidingEntity;
                    if(collidingEntity && !collidingEntity->isDeleted()) {
                        if(g.componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
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
            Enemy = &g.entityManager.getEntity(enemy.entity());
            enemyTransform = &Enemy->getComponent<TransformComponent>();

            if(enemy.type == SMALLENEMY || enemy.type == MEDIUMENEMY) {
                if(enemyTransform != nullptr ) {
                    if(enemyTransform->localPosition.x < -enemyTransform->localScale.x) {
                        g.entityManager.deleteEntity(g.entityManager.getEntity(enemyTransform->entity()));
                    }
                    else {
                        if(enemy.MovesInCosCurves) {
                            enemyCosMovement(g, enemyTransform, enemyTransform->localPosition.y, 300, 50);
                        }
                        else if(enemy.MovesInSinCurves){
                            enemySinMovement(g, enemyTransform, enemyTransform->localPosition.y, 300, 50);
                        }
                        else if(enemy.MovesDiagonalUp || enemy.MovesDiagonalDown) {
                            enemyDiagonalMovement(g, enemyTransform, enemy.MovesDiagonalUp, 300);
                        }
                    }
                }
            }
            if(enemy.type == BIGENEMY) {
                bigEnemiesBehavior(g, enemyTransform, &enemy, 1.5);
            }
        });
    });
}

void EnemySystem::enemyCosMovement(Game& game, TransformComponent* enemyTransform,
                                   float Ycoordinate, float speed, float wiggleLength) {
    enemyTransform->localPosition.y = (cos(enemyTransform->localPosition.x / wiggleLength) + Ycoordinate);
    enemyTransform->localPosition.x = enemyTransform->localPosition.x - speed * game.getDeltaTime();
}


void EnemySystem::enemySinMovement(Game &game, TransformComponent *enemyTransform, float Ycoordinate, float speed,
    float wiggleLength){
    enemyTransform->localPosition.y = (cos(enemyTransform->localPosition.x / wiggleLength) + Ycoordinate);
    enemyTransform->localPosition.x = enemyTransform->localPosition.x - speed * game.getDeltaTime();
}

void EnemySystem::enemyDiagonalMovement(Game &game, TransformComponent *enemyTransform, bool goingUp, float speed) {
    // Store initial coordinates
    static float referenceX = enemyTransform->localPosition.x;
    static float referenceY = enemyTransform->localPosition.y;

    enemyTransform->localPosition.x -= speed * game.getDeltaTime();

    // Move relative to reference point
    float deltaX = referenceX - enemyTransform->localPosition.x;
    enemyTransform->localPosition.y = referenceY + (goingUp ? -1 : 1) * deltaX * 0.4;

}

void EnemySystem::bigEnemiesBehavior(Game& game, TransformComponent* bigEnemyTransform, EnemyComponent* bigEnemy, float speed) {
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{-1.2f, 500.0f};

    bigEnemy->countdown -= game.getDeltaTime();
    for(int i = 0; i < 20; i++) {
        if(bigEnemy->countdown <= 0) {
            bigEnemy->newPosition = dist(rng);
            bigEnemy->countdown = bigEnemy->positionChangeTime;
        }
    }
    bigEnemyTransform->localPosition.y = lerp(bigEnemyTransform->localPosition.y, bigEnemy->newPosition,
        game.getDeltaTime() * speed);
}


void EnemySystem::creatureMovement(Game &game, TransformComponent *creatureTransform, EnemyComponent *creature, float speed) {
    std::time_t elapsedTime = std::time(nullptr);

    //zRotation = glm::degrees(theta_radians) - 90.0f;

    std::random_device dev;
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
        game.getDeltaTime() * speed);
}
