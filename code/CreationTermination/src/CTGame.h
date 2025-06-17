#pragma once
#include <iostream>

#include "brewEngine/rendering/SpriteRenderer.h"
#include "brewEngine/rendering/SpriteComponent.h"
#include "Systems/AnimationSystem.h"

using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::TransformComponent;
using gl3::brewEngine::rendering::SpriteComponent;

class CTGame : public Game {
public:
    CTGame(int width, int height, const std::string &title) : Game(width, height, title) {}

private:
    void start() override;

    void update(GLFWwindow *window) override;

    void draw() override;

    std::unique_ptr<AnimationSystem> animationSystem;
    Entity *Witch = nullptr;
    TransformComponent *WitchTransform = nullptr;
    SpriteComponent *WitchSprite = nullptr;
    TransformComponent *Creature = nullptr;
    std::vector<TransformComponent> bats;

};
