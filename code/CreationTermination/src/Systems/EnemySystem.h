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
    explicit EnemySystem(Game &game, Entity* Creature);

    void creatureMovement(Game &game, TransformComponent* creatureTransform, EnemyComponent* creature);
    void creatureDefense();

    void enemyCosMovement(Game& game, TransformComponent* enemyTransform, float Ycoordinate,
        float speed, float wiggleLength);
    void enemySinMovement(Game& game, TransformComponent* enemyTransform, float Ycoordinate,
        float speed, float wiggleLength);
    void enemyDiagonalMovement(Game& game, TransformComponent* enemyTransfrom, float speed);
    void bigEnemiesBehavior(Game& game, TransformComponent* bigEnemyTransform, EnemyComponent* bigEnemy);

    float lerp(float a, float b, float f) {return a + f * (b - a);}
    std::random_device dev;

    glm::vec2 tempEnemyPosition = glm::vec2(0,0);

    //small enemy spawn counter
    const float smallEnemyCountdownReset = 1.0f;
    float smallEnemySpawnCountdown = smallEnemyCountdownReset;
    //medium enemy spawn counter
    bool MediumWillSpawn = false;
    const float mediumEnemyCountdownReset = 2.0f;
    float mediumEnemySpawnCountdown = mediumEnemyCountdownReset;
    //big enemy spaw counter
    bool BigWillSpawn = false;
    const float bigEnemyCountdownReset = 4.0f;
    float bigEnemySpawnCountdown = bigEnemyCountdownReset;


    unsigned int difficulty = 1;
    //Stopwatch/Timer
    float currentTime = 0;
};



