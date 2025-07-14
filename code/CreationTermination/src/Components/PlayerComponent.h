#pragma once

#include "brewEngine/ecs/Component.h"
#include "brewEngine/sceneGraph/TransformComponent.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/EntityManager.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;

class PlayerComponent : public Component {
    friend ComponentManager;
    friend Entity;

    public:
    explicit PlayerComponent(gl3::brewEngine::ecs::guid_t owner): Component(owner) {};

    bool chargingMissile = false;
    //isCreatingSingleMissile serves the purpose to prevent creating multiple missiles while the player charges the charge Missile
    bool isCreatingSingleMissile = false;
    float missileTempSize = 1.0f;
    guid_t currentMissileID = -1;
};