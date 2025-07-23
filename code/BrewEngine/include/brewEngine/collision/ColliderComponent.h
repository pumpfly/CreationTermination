#pragma once
#include <utility>

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

        /// Giving an entity the @class ColliderComponent gives it the ability to collide with other entities which have a @class ColliderComponent as well.
        /// if two entites collide that have the same @param type a collision won't trigger.
        /// Example: A entity representing the player will have a ColliderComponent with the type @enum PLAYER,
        /// this player can create missiles which are also entities with a ColliderComponent. In order to prevent the player colliding with its own missiles
        /// the ColliderComponent of the missiles is also of the type @enum PLAYER.
        explicit ColliderComponent(guid_t owner, CollisionCategory type,
            std::function <void()> handleCollision)
                : Component(owner),type(type), handleCollision(std::move(handleCollision)) {}

        /// An overload of the ColliderComponent constructor that includes the member @param timeBetweenDamage
        /// which can be used to prevent certain effects to take place on collision for a given amount of time, like health reduction.
        explicit ColliderComponent(guid_t owner, CollisionCategory type, float timeBetweenDamage,
            std::function <void()> handleCollision)
                : Component(owner), timeBetweenDamage(timeBetweenDamage) ,type(type), handleCollision(std::move(handleCollision)) {}

    public:
        CollisionCategory type;
        ///handleCollision() is a lambda function that is a parameter of the ColliderComponent constructor.
        /// If the user adds a ColliderComponent to an entity, handleCollision's definition is the input.
        /// This function will only get called on collision.
        std::function <void()> handleCollision;

        Entity* currCollidingEntity = nullptr;

        bool isShielded = false;
        bool isInvulnerable = false;

        float timeBetweenDamage = 1.0f;
        float invulnerabilityTimer = timeBetweenDamage;
    };
}
