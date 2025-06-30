#pragma once
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ecs.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

class EnemyComponent : Component
{
    friend ComponentManager;
    friend Entity;

public:
    //Creature Components
    guid_t creatureID;
    float speed = 1.5;
    float positionChangeTime = 1.0f;
    float countdown = positionChangeTime;
    float newPosition = 500;


    //SoLoud::Soloud audio;
    //SoLoud::Wav firingSound;

private:
    explicit EnemyComponent(guid_t owner, guid_t creatureID) : Component(owner), creatureID(creatureID) {}

};
