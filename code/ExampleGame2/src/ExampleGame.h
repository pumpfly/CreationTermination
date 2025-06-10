#pragma once
#include <iostream>
#include "brewEngine/Game.h"
#include "Health.h"
#include "RenderSystem.h"
#include "GameOverScreen.h"
#include "Position.h"

using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;

class ExampleGame : public Game {
public:
    ExampleGame(int width, int height, const std::string &title) : Game(width, height, title) {
    }

private:
    void start() override {
        RenderSystem renderSystem(*this);
        GameOverScreen gameOverScreen(*this);
        auto &player = entityManager.createEntity();
        auto &health = player.addComponent<Health>(200);
        auto &position = player.addComponent<Position>(5, 5);
        playerHealth = &health;
    }

    void update(GLFWwindow *window) override {
        playerHealth->value -= 10;
        std::cout << "hallo" << std::endl;
    }

private:
    Health *playerHealth = nullptr;
};