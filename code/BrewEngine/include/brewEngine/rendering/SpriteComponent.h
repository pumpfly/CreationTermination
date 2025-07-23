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
        /// By giving an entity a @class SpriteComponent it will automatically be rendered and animated if a sprite sheet has been used.
        /// The overall size, rotation and position of the displayed sprite depends on the TransformComponent of the entity.
        friend ComponentManager;
        friend Entity;

    public:

        /// There are two overloads of the @class SpriteComponent: One simply expects two parameters and that is the @param sprite which should be the type @class Texture2D
        /// and its @param color .
        /// If the user wants the original @param color of the image, they have to input the vector {1,1,1,1}
        /// To obtain the right sprite the user has to first load the sprite with @function FromFile() form @class Texture2D.
        /// This version of the SpriteComponent only displays a still image, no animation.
        explicit SpriteComponent(ecs::guid_t owner, Texture2D sprite, glm::vec4 color);

        /// The overload constructor expects three additional parameters: @param frameSize, frameCount, and @param framesPerSecond
        /// The user should use this version of @class SpriteComponent, if they want to implement and animate a sprite sheet.
        explicit SpriteComponent(ecs::guid_t owner, Texture2D sprite, glm::vec2 frameSize,
            int frameCount, float framesPerSecond, glm::vec4 color);

        ~SpriteComponent() override { deleted = true; }

        Texture2D sprite;
        glm::vec2 size = glm::vec2(1.0f, 1.0f);
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        //Sprite Sheet Animation:
        glm::vec2 frameSize = glm::vec2(1.0f, 1.0f);
        int frameCount = 0;
        float framesPerSecond = 0;

        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;
        glm::vec2 spriteFrameSize = glm::vec2(0, 0);

    };
}