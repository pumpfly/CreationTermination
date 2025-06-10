#pragma once
#include "brewEngine/ecs/Component.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

struct Position: Component {
    friend ComponentManager;
    friend Entity;

    float x;
    float y;

private:
    explicit Position(guid_t owner, float xValue = 0, float yValue = 0) : Component(owner), x(xValue), y(yValue) {}
};