#pragma once

#include <iostream>
#include "brewEngine/ecs/System.h"
#include "Health.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class GameOverScreen : public System {
public:
    explicit GameOverScreen(Game &game) : System(game) {
        engine.onBeforeUpdate.addListener([&](Game &game) {
            checkEndGame(game);
        });
    }

private:
    void checkEndGame(Game &game) {
        game.componentManager.forEachComponent<Health>([&](Health &health) {
            if(health.value <= 0) {
                std::cout << "Game over." << std::endl;
                auto &player = game.entityManager.getEntity(health.entity());
                game.entityManager.deleteEntity(player);
                glfwSetWindowShouldClose(game.getWindow(), true);
            }
        });
    }
};