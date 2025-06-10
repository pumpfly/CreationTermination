#pragma once
#include <iostream>
#include "brewEngine/ecs/System.h"
#include "Health.h"
#include "Position.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class RenderSystem : public System {
public:
    explicit RenderSystem(Game &game) : System(game) {
        engine.onBeforeUpdate.addListener([&](Game &game) {
            renderPlayer(game);
        });
    }

private:
    void renderPlayer(Game &game) {
        auto &healthContainer = game.componentManager.getContainer<Health>();
        auto &positionContainer = game.componentManager.getContainer<Position>();
        for(auto &[owner, _] : healthContainer) {
            if(game.componentManager.hasComponent<Position>(owner)) {
                auto &health = game.componentManager.getComponent<Health>(owner);
                auto &position = game.componentManager.getComponent<Position>(owner);
                std::cout << "Player is at (" << position.x << ", " << position.y << ") and has " << health.value << " HP" << std::endl;
            }
        }
    }
};