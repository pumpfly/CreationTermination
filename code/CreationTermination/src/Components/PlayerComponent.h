#pragma once

#include "brewEngine/ecs/Component.h"
#include "brewEngine/sceneGraph/TransformComponent.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;

class PlayerComponent : public Component {
    friend ComponentManager;
    friend Entity;

    public:
    explicit PlayerComponent(gl3::brewEngine::ecs::guid_t owner): Component(owner) {};

    bool madeFirstShot = false;
    int missilesShot = 0;
};