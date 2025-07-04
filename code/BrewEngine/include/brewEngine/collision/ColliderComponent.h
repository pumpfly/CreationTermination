#pragma once
#include "../../../../CreationTermination/src/Components/HealthComponent.h"
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/EntityManager.h"

using gl3::brewEngine::ecs::Component;
using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::guid_t;
using gl3::brewEngine::ecs::Entity;

enum CollisionCategory {
    ENEMY,
    PLAYER
};

namespace gl3::brewEngine::collision {
    class ColliderComponent : public Component {
        friend ComponentManager;
        friend Entity;

        explicit ColliderComponent(guid_t owner, CollisionCategory type,
            std::function <void()> handleCollision)
                : Component(owner), type(type), handleCollision(handleCollision) {}

    public:
        std::function <void()> handleCollision;

        CollisionCategory type;

        bool isInvulnerable = false;
        bool gotHit = false;
        const float timeBetweenDamage = 1.0f;
        float invulnerabilityTimer = timeBetweenDamage;
    };
}
