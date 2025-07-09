#pragma once
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/EntityManager.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

class UiComponent : public Component
{
    friend ComponentManager;
    friend Entity;

public:


private:

    explicit UiComponent(guid_t owner) : Component(owner){};

};
