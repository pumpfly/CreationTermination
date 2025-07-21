#pragma once

#include "../Components/MissileComponent.h"
#include "../Components/PlayerComponent.h"
#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/input/Input.h"
#include "brewEngine/rendering/Texture2D.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::input::Input;

class PlayerSystem : public System{
    public:
    explicit PlayerSystem(Game &game, Entity* Witch, int& shieldCooldownUINumber);

    //countdown
    const float countdownReset = 0.1f;
    float countdown = countdownReset;

    //Movement is restricted inside Screensize
    bool isTooFarLeft = false;
    bool isTooFarRight = false;
    bool isTooFarUp = false;
    bool isTooFarDown = false;

    gl3::brewEngine::rendering::Texture2D missileSprite;
    gl3::brewEngine::rendering::Texture2D shieldSprite;
    //needed for bool isBeingCharged
    MissileComponent* chargeMissile = nullptr;
    guid_t currMissileID = -1;

    void playerMovement(Game &game, TransformComponent* witchTransform);
    void playerShield(Game& game, TransformComponent* witchTransform, gl3::brewEngine::collision::ColliderComponent* witchCollider, int& shieldCooldownUINumber);
    void playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer);

    float shieldCooldown = -1;
};


