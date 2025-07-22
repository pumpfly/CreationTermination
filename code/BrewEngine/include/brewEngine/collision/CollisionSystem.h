
#pragma once
#include "ColliderComponent.h"
#include "brewEngine/rendering/Texture2D.h"
#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

namespace gl3::brewEngine::collision {
    class CollisionSystem : public System {
        public:
        explicit CollisionSystem(Game &game);

        bool hasCollision(Entity* entity, Entity* other);

        rendering::Texture2D radiusDisplay;
        Entity* radiusCenter = nullptr;

        float timeBetweenDamage = 1.0f;
        float invulnerabilityTimer = timeBetweenDamage;
    };
}

