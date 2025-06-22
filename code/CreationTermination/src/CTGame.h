#pragma once

#include "brewEngine/Game.h"
#include "brewEngine/rendering/BackgroundComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"


using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::TransformComponent;
using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::rendering::BackgroundComponent;

class CTGame : public Game {
public:
    CTGame(int width, int height, const std::string &title) : Game(width, height, title) {}

private:
    void start() override;

    void update(GLFWwindow *window) override;

    void draw() override;

    Entity* Witch = nullptr;
    TransformComponent *WitchTransform = nullptr;
    SpriteComponent *WitchSprite = nullptr;

    Entity *Creature = nullptr;
    TransformComponent *CreatureTransform = nullptr;
    SpriteComponent *CreatureSprite = nullptr;

    //Background/Landscape
    Entity* Background_Layer1 = nullptr;
    SpriteComponent* BackgroundSprite_Layer1 = nullptr;
    BackgroundComponent* BackgroundComponents_Layer1 = nullptr;

    std::vector<TransformComponent> bats;

};
