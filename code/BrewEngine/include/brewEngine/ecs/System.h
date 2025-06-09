#pragma once

#include "brewEngine/Game.h"

namespace gl3::brewEngine::ecs {
    class System {
    public:
        explicit System(Game &engine) : engine(engine) {}
        System(System &&) = delete;
        System(const System &) = delete;
        virtual ~System() = default;

    protected:
        brewEngine::Game &engine;
    };
}
