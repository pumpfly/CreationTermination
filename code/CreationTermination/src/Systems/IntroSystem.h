#pragma once
#pragma once


#include "brewEngine/rendering/Texture2D.h"
#include "brewEngine/collision/CollisionSystem.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::rendering::Texture2D;

class IntroSystem : public System{
public:
    explicit IntroSystem(Game &game, Entity* CutScene);

    std::vector<Texture2D> introSceneTextures;

    SpriteComponent *cutSceneSprite = nullptr;
    float sceneCountdown = 0;
    int sceneIndex = 0;
};
