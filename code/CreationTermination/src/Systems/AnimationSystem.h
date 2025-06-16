#pragma once

#pragma once
#include "brewEngine/ecs/System.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::rendering::SpriteComponent;

class AnimationSystem : public System {
public:
    explicit AnimationSystem(Game &game) : System(game) {
        game.onStartup.addListener([&](Game&) {
        });
    }

    glm::vec4 animateSpriteSheet(SpriteComponent entitiesSprite, float deltaTime) {
        entitiesSprite.spriteAnimTimer += deltaTime;
        if(entitiesSprite.spriteAnimTimer >= 0.1f) {
            entitiesSprite.spriteAnimIndex = (entitiesSprite.spriteAnimIndex + 1) % entitiesSprite.frameCount;
        }
        return {entitiesSprite.spriteFrameSize.x * entitiesSprite.spriteAnimIndex, 0, entitiesSprite.spriteFrameSize};
    };

};