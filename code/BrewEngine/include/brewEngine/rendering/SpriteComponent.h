#pragma once

#include "brewEngine/ecs/Component.h"
#include "Texture2D.h"
#include "brewEngine/sceneGraph/TransformComponent.h"
#include "glm/vec2.hpp"

namespace gl3::brewEngine::ecs {
    class ComponentManager;
    class Entity;
}

using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::TransformComponent;

namespace gl3::brewEngine::rendering {
    class SpriteComponent final : public ecs::Component {
        friend ComponentManager;
        friend Entity;

    public:

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath);

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath, glm::vec2 frameSize, int frames);

        ~SpriteComponent() override { deleted = true; }

        glm::vec4 animateSpriteSheet(SpriteComponent* entitiesSprite, float deltaTime);

        Texture2D sprite;
        glm::vec2 size;

        //Sprite Sheet Animation:
        int frameCount = 0;
        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;
        glm::vec2 spriteFrameSize = glm::vec2(0, 0);

    };
}