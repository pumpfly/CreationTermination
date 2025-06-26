#pragma once
#include <memory>
#include <vector>

#include "brewEngine/sceneGraph/TransformComponent.h"
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
    explicit MissileComponent(guid_t owner, float speed, MissileType type)
                                    : Component(owner), speed(speed), type(type) {};

    MissileType type;
    float speed = 200.0f;
};
