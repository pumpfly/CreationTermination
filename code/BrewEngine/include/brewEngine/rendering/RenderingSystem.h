#pragma once

#include "SpriteComponent.h"
#include "SpriteRenderer.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/BackgroundComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

namespace gl3::brewEngine::rendering{
    class RenderingSystem : public System {
    public:
        explicit RenderingSystem(Game &game);
        //in order for the Background to scroll, this method switches the position of the Sprite and its copy
        void scrollBackgroundSprite(TransformComponent* backgroundTransform, BackgroundComponent* background,
            bool isScrollingSideways, bool goesLeftOrUp, float deltaTime);
        glm::vec4 animateSpriteSheet(SpriteComponent* entitiesSprite, float deltaTime);
    };
}
