#pragma once

#include "../Components/MissileComponent.h"
#include "../Components/PlayerComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/input/Input.h"
#include "brewEngine/rendering/Texture2D.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::input::Input;

class PlayerSystem : public System{
    public:
    explicit PlayerSystem(Game &game, Entity* Witch);

    //countdown
    const float countdownReset = 0.1f;
    float countdown = countdownReset;

    bool isTooFarLeft = false;
    bool isTooFarRight = false;
    bool isTooFarUp = false;
    bool isTooFarDown = false;

    gl3::brewEngine::rendering::Texture2D missileSprite;

    void playerMovement(Game &game, TransformComponent* witchTransform);
    void playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer);
};

