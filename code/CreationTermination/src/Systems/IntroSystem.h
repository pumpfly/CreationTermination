#pragma once
#pragma once

#include "EnemySystem.h"
#include "MissileSystem.h"
#include "PlayerSystem.h"
#include "brewEngine/collision/CollisionSystem.h"
#include "brewEngine/ecs/System.h"

struct EnemyComponent;
using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class IntroSystem : public System{
public:
    explicit IntroSystem(Game &game);

    float sceneCountdown = 0;
    int sceneIndex = 0;
};
