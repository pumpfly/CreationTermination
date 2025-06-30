
#pragma once

#include "brewEngine/ecs/System.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class EnemySystem : public System{
public:
    explicit EnemySystem(Game &game) : System(game)
    {
        game.onBeforeUpdate.addListener([&] (Game &)
        {

        });
    }

};



