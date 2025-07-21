#pragma once

#include "brewEngine/ecs/Component.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;

class ShieldComponent: public Component {
    friend ComponentManager;
    friend Entity;

    public:
    explicit ShieldComponent(gl3::brewEngine::ecs::guid_t owner, TransformComponent* follows, glm::vec2 offset,
        std::function<void()> endFunc):
    Component(owner), follows(follows), offset(offset),endFunc(std::move(endFunc)) {};

    TransformComponent* follows;
    std::function<void()> endFunc;
    glm::vec2 offset = glm::vec2(0.0f);

    const float lifetime = 1.0f;
    float activeTimer = 0.0f;
};