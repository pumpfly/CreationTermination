#pragma once

#include "brewEngine/Events.h"

class Player {
public:

    using event_t = typename gl3::brewEngine::events::Events<Player>;
    event_t onPlayerDeath;

    void getDamage(int value) {

    }
};