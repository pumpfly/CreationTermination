#pragma once

#include "brewEngine/Game.h"
#include "brewEngine/rendering/BackgroundComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"
#include "Systems/MissileSystem.h"
#include "Systems/PlayerSystem.h"
#include "brewEngine/rendering/RenderingSystem.h"
#include "Systems/EnemySystem.h"


using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::TransformComponent;
using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::rendering::BackgroundComponent;
using gl3::brewEngine::rendering::RenderingSystem;

class CTGame : public Game {
public:
    CTGame(int width, int height, const std::string &title) : Game(width, height, title) {}

private:
    void start() override;

    void update(GLFWwindow *window) override;

    void draw() override;

    //Systems
    std::unique_ptr<RenderingSystem> renderSystem;
    std::unique_ptr<PlayerSystem> playerSystem;
    std::unique_ptr<MissileSystem> missileSystem;
    std::unique_ptr<EnemySystem> enemySystem;

    // Entities and their componenets
    //Player/Witch
    Entity* Witch = nullptr;
    PlayerComponent* WitchPlayer = nullptr;
    TransformComponent *WitchTransform = nullptr;
    SpriteComponent *WitchSprite = nullptr;

    //Creature
    Entity* Creature = nullptr;
    EnemyComponent* CreatureEnemyComponent = nullptr;
    TransformComponent *CreatureTransform = nullptr;
    SpriteComponent *CreatureSprite = nullptr;

    //Background/Landscape
    Entity* Background_Layer1 = nullptr;
    SpriteComponent* BackgroundSprite_Layer1 = nullptr;
    BackgroundComponent* BackgroundComponents_Layer1 = nullptr;

    Entity* Background_Layer2 = nullptr;
    SpriteComponent* BackgroundSprite_Layer2 = nullptr;
    BackgroundComponent* BackgroundComponents_Layer2 = nullptr;

    Entity* Background_Layer3 = nullptr;
    SpriteComponent* BackgroundSprite_Layer3 = nullptr;
    BackgroundComponent* BackgroundComponents_Layer3 = nullptr;

    std::vector<TransformComponent> bats;

};
