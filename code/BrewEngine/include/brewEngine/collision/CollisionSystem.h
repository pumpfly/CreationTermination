
#pragma once
#include "ColliderComponent.h"
#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

namespace gl3::brewEngine::collision {
    class CollisionSystem : public System {
        public:
        explicit CollisionSystem(Game &game);

        bool hasCollision(Entity* entity, Entity* other);

    };
}

