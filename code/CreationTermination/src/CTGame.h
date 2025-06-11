#pragma once
#include <iostream>
#include "glm/vec3.hpp"
#include "brewEngine/Game.h"
#include "brewEngine/sceneGraph/Transform.h"
#include "Systems/RenderSystem.h"

using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::Transform;

class CTGame : public Game {
public:
    CTGame(int width, int height, const std::string &title) : Game(width, height, title) {
    }

private:
    void start() override {
        renderSystem = std::make_unique<RenderSystem>(*this);
        t1 = &entityManager.createEntity().addComponent<Transform>(origin, glm::vec3(1, 1, 1));
    }

    void update(GLFWwindow *window) override {

    }

private:
    std::unique_ptr<RenderSystem> renderSystem;
    Transform *t1 = nullptr;
    Transform *t2 = nullptr;
    Transform *t3 = nullptr;
};
