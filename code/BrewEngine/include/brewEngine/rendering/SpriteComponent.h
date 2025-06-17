#pragma once
#include <string>
#include <vector>

#include "brewEngine/ecs/Component.h"
#include "Texture2D.h"
#include "glm/vec2.hpp"

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

        explicit SpriteComponent(ecs::guid_t owner, const char* spritePath, glm::vec2 frameSize, int frames);

        ~SpriteComponent() override { deleted = true; }

        //Background scrolling
        void SetBackgroundLayerSpeed(int layerNumber, float layerSpeed);
        void scrollBackgroundSprite();

        Texture2D sprite;

        //Sprite Sheet Animation:
        int frameCount = 0;
        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;
        glm::vec2 spriteFrameSize = glm::vec2(0, 0);

        ////Background scrolling
        //layers
        std::vector<float> layers;
        float layer1speed = 800.0f;
        float layer2speed = 600.0f;
        float layer3speed = 400.0f;


        glm::vec2 layer1_position = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer1copy_position = glm::vec2(1280*3, 0.0f);

        glm::vec2 layer2_position = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer2copy_position = glm::vec2(1280*3, 0.0f);

        glm::vec2 layer3_position = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer3copy_position = glm::vec2(1280*3, 0.0f);

    protected:
        glm::vec2 scale;
        std::string layerName;

    };
}