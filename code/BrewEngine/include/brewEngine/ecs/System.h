#pragma once

#include "brewEngine/Game.h"

namespace gl3::brewEngine::ecs {
    class System {
    /// The Systems, objects/classes that inherit from gl3::brewEngine::ecs::System, make use of the events.
    /// Systems are being created inside the start function of game.
    public:
        explicit System(Game &engine) : engine(engine) {}
        System(System &&) = delete;
        System(const System &) = delete;
        virtual ~System() = default;

    protected:
        Game &engine;
    };
}
