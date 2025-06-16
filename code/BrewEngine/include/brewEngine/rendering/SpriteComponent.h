#pragma once
#include <string>

#include "brewEngine/ecs/Component.h"

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

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath) {
            sprite = Texture2D::FromFile(spritePath);
        };

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath, glm::vec2 frameSize, int frames) {
            sprite = Texture2D::FromFile(spritePath);
            spriteFrameSize = glm::vec2(frameSize.x, frameSize.y);
            frameCount = frames;
        }

        ~SpriteComponent() override {
                deleted = true;
        }

        Texture2D sprite;

        //Sprite Sheet Animation:
        int frameCount = 0;
        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;
        glm::vec2 spriteFrameSize = glm::vec2(0, 0);
    };
}