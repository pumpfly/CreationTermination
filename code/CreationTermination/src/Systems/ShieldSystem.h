#pragma once

#include "brewEngine/ecs/System.h"


using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class ShieldSystem : public System {
    public:
    explicit ShieldSystem(Game &game);
};
