//
// Created by pumf on 21/07/2025.
//

#pragma once

#include "brewEngine/ecs/System.h"


using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class ShieldSystem : public System {
    public:
    explicit ShieldSystem(Game &game);
};
