#pragma once

#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/BackgroundComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

class RenderingSystem : public System {
public:
    explicit RenderingSystem(Game &game) : System(game) {
        /*game.onAfterUpdate.addListener([&](Game&) {

        });*/
    }
    void scrollBackgroundSprite(gl3::brewEngine::rendering::BackgroundComponent* background, bool isScrollingSideways, bool goesLeftOrUp, float deltaTime);
};
