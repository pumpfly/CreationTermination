#pragma once
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::rendering::Texture2D;

class GameOverSystem : public System{
    public:
    explicit GameOverSystem(Game& game, Entity* EndScene, const Texture2D &gameOver, const Texture2D &gameWon);

    SpriteComponent* endSceneSprite = nullptr;
};
