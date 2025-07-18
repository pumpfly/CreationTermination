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

    bool MovesInCosCurves = true;
    bool MovesInSinCurves = false;
    bool MovesDiagonalUp = false;
    bool MovesDiagonalDown = false;

    float speed = 1.5;
    float positionChangeTime = 1.0f;
    float countdown = positionChangeTime;
    float newPosition = 500;


    //SoLoud::Soloud audio;
    //SoLoud::Wav firingSound;

private:
    //This constructor will be used by small and medium enemy
    explicit EnemyComponent(guid_t owner, EnemyType type,
        bool MovesInCosCurves, bool MovesInSinCurves, bool MovesDiagonalUp, bool MovesDiagonalDown)
    : Component(owner), type(type),
    MovesInCosCurves(MovesInCosCurves), MovesInSinCurves(MovesInSinCurves),
    MovesDiagonalUp(MovesDiagonalUp), MovesDiagonalDown(MovesDiagonalDown){}

    //The constructor will be used by creature and big enemy
    explicit EnemyComponent(guid_t owner, EnemyType type) : Component(owner), type(type){}
};
