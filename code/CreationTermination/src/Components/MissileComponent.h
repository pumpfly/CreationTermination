#pragma once

#include "brewEngine/ecs/Entity.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/Component.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;

enum MissileType {
    DEFAULT,
    WAVE,
    CHARGE
};

class MissileComponent : public Component {
    friend ComponentManager;
    friend Entity;

    public:
    explicit MissileComponent(gl3::brewEngine::ecs::guid_t owner, bool goesToTheRight, float speed, float damage, MissileType type)
                                    : Component(owner), speed(speed), damage(damage), type(type), goesToTheRight(goesToTheRight) {};
    // Constructor for Charge Missile
    explicit MissileComponent(gl3::brewEngine::ecs::guid_t owner, bool goesToTheRight, bool isBeingCharged, float speed, MissileType type)
                                    : Component(owner), speed(speed), type(type), goesToTheRight(goesToTheRight), isBeingCharged(isBeingCharged) {};

    MissileType type;
    bool goesToTheRight = true;
    bool isBeingCharged = false;
    float speed = 200.0f;
    float damage = 0;
};
