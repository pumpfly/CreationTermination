#pragma once
#include "brewEngine/ecs/Component.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

struct HealthComponent: Component {
    friend ComponentManager;
    friend Entity;

    int value;

private:
    explicit HealthComponent(guid_t owner, int health = 100) : Component(owner), value(health) {}
};