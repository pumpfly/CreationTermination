#pragma once

#include "brewEngine/ecs/System.h"
#include "../Components/MissileComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;


class MissileSystem : public System{
    public:
    explicit MissileSystem(Game &game);

    void updateMissiles(Game& game, bool goesToTheRight, TransformComponent* missileTransform, MissileComponent* missileComponent);
};
