#pragma once
#include "brewEngine/ecs/Component.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

class HealthComponent: public Component {
    friend ComponentManager;
    friend Entity;

    public:
    void SetHealth(int newHealth) {health = newHealth;}

    int health;

private:
    explicit HealthComponent(guid_t owner, int health = 100) : Component(owner), health(health) {}
};