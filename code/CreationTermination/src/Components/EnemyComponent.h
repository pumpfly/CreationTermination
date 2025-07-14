#pragma once
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ecs.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/EntityManager.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

enum EnemyType {
    CREATURE,
    SMALLENEMY,
    MEDIUMENEMY,
    BIGENEMY
};

class EnemyComponent : public Component
{
    friend ComponentManager;
    friend Entity;

public:
    EnemyType type;

    //Creature Components
    float speed = 1.5;
    float positionChangeTime = 1.0f;
    float countdown = positionChangeTime;
    float newPosition = 500;


    //SoLoud::Soloud audio;
    //SoLoud::Wav firingSound;

private:
    explicit EnemyComponent(guid_t owner, EnemyType type) : Component(owner), type(type){}
};
