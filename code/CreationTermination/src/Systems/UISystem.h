#pragma once

#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/SpriteComponent.h"
#include "../Components/UiComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;

class UISystem : public System{
    public:
    explicit UISystem(Game &game): System(game)
    {
    }
};

