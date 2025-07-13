#pragma once

#include "brewEngine/Game.h"
#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/collision/CollisionSystem.h"
#include "brewEngine/rendering/BackgroundComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/PlayerComponent.h"
#include "Systems/MissileSystem.h"
#include "Systems/PlayerSystem.h"
#include "brewEngine/rendering/RenderingSystem.h"
#include "Components/HealthComponent.h"
#include "Components/UiComponent.h"
#include "Systems/EnemySystem.h"


using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::TransformComponent;
using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::rendering::BackgroundComponent;
using gl3::brewEngine::rendering::RenderingSystem;
using gl3::brewEngine::collision::ColliderComponent;
using gl3::brewEngine::collision::CollisionSystem;

class CTGame : public Game {
public:
    CTGame(int width, int height, const std::string &title) : Game(width, height, title) {}

private:
    void start() override;

    void update(GLFWwindow *window) override;

    //Score
    int currScore = 0;
    int maxScore = 5000;

    //Systems
    std::unique_ptr<RenderingSystem> renderSystem;
    std::unique_ptr<PlayerSystem> playerSystem;
    std::unique_ptr<MissileSystem> missileSystem;
    std::unique_ptr<EnemySystem> enemySystem;
    std::unique_ptr<CollisionSystem> collisionSystem;

    // Entities and their componenets

    //Background/Landscape
    Entity* Background_Layer1 = nullptr;
    SpriteComponent* backgroundSprite_Layer1 = nullptr;
    TransformComponent* backgroundTransform_Layer1 = nullptr;
    BackgroundComponent* backgroundComponents_Layer1 = nullptr;

    Entity* Background_Layer2 = nullptr;
    SpriteComponent* backgroundSprite_Layer2 = nullptr;
    TransformComponent* backgroundTransform_Layer2 = nullptr;
    BackgroundComponent* backgroundComponents_Layer2 = nullptr;

    Entity* Background_Layer3 = nullptr;
    SpriteComponent* backgroundSprite_Layer3 = nullptr;
    TransformComponent* backgroundTransform_Layer3 = nullptr;
    BackgroundComponent* backgroundComponents_Layer3 = nullptr;

    // Main Characters
    ////Player/Witch
    Entity* Witch = nullptr;
    PlayerComponent* witchPlayer = nullptr;
    TransformComponent *witchTransform = nullptr;
    SpriteComponent *witchSprite = nullptr;
    ColliderComponent *witchCollider = nullptr;
    HealthComponent *witchHealth = nullptr;

    ////Creature
    Entity* Creature = nullptr;
    EnemyComponent* creatureEnemyComponent = nullptr;
    TransformComponent *creatureTransform = nullptr;
    SpriteComponent *creatureSprite = nullptr;
    ColliderComponent *creatureCollider = nullptr;
    HealthComponent *creatureHealth = nullptr;

    //UI
    ////HealthBars
    Entity* WitchBackgroundHealthBar = nullptr;
    TransformComponent *witchBackgroundHealthBarTransform = nullptr;
    SpriteComponent *witchBackgroundHealthBarSprite = nullptr;

    Entity* WitchHealthQuad = nullptr;
    TransformComponent *witchHealthQuadTransform = nullptr;
    SpriteComponent *witchHealthQuadSprite = nullptr;
    UiComponent *witchHealthQuadComponent = nullptr;
    std::vector<Entity*> healthQuads;

    ////Leif UI elements
    LfFont bigfont;

};
