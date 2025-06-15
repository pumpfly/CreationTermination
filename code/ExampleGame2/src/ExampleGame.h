#pragma once
#include <iostream>
#include "glm/vec3.hpp"
#include "brewEngine/Game.h"
#include "brewEngine/sceneGraph/Transform.h"
#include "RenderSystem.h"

using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::Transform;

class ExampleGame : public Game {
public:
    ExampleGame(int width, int height, const std::string &title) : Game(width, height, title) {
    }

private:
    void start() override {
        renderSystem = std::make_unique<RenderSystem>(*this);
        t1 = &entityManager.createEntity().addComponent<Transform>(origin, glm::vec3(1, 1, 1));
        t2 = &entityManager.createEntity().addComponent<Transform>(origin, glm::vec3(2, 2, 2));
        t3 = &entityManager.createEntity().addComponent<Transform>(t1, glm::vec3(3, 3, 3));
    }

    void update(GLFWwindow *window) override {
        static int frameCount = 0;

        switch(frameCount) {
        case 0:
            break;
        case 1:
            t1->localPosition = {5, 5, 5};
            break;
        case 2:
            t3->localPosition = {4, 4, 4};
            break;
        case 3:
            entityManager.deleteEntity(entityManager.getEntity(t1->entity()));
            break;
        default:
            //glfwSetWindowShouldClose(window, true);
            break;
        }

        ++frameCount;
    }

private:
    std::unique_ptr<RenderSystem> renderSystem;
    Transform *t1 = nullptr;
    Transform *t2 = nullptr;
    Transform *t3 = nullptr;
};