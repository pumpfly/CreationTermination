#pragma once

#include "brewEngine/ecs/Component.h"
#include "Texture2D.h"

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace gl3::brewEngine::ecs {
    class ComponentManager;
    class Entity;
}

using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;


namespace gl3::brewEngine::rendering {
    class SpriteComponent final : public ecs::Component {
        friend ComponentManager;
        friend Entity;

    public:

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath);

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath, glm::vec2 frameSize,
            int frameCount, float framesPerSecond);

        ~SpriteComponent() override { deleted = true; }

        Texture2D sprite;
        glm::vec2 size = glm::vec2(1.0f, 1.0f);

        //Sprite Sheet Animation:
        glm::vec2 frameSize = glm::vec2(1.0f, 1.0f);
        int frameCount = 0;
        float framesPerSecond = 0;

        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;
        glm::vec2 spriteFrameSize = glm::vec2(0, 0);

    };
}