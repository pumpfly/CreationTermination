#pragma once
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ecs.h"
#include "glm/vec2.hpp"

using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;

namespace gl3::brewEngine::rendering {
    class BackgroundComponent final : public ecs::Component{
        friend ecs::ComponentManager;
        friend ecs::Entity;

        public:
        explicit BackgroundComponent(ecs::guid_t owner, glm::vec2 position, float scrollingSpeed, glm::vec2 scale);
        ~BackgroundComponent() override { deleted = true; }

        float scrollingSpeed;
        glm::vec2 scale;
        glm::vec2 position;
        glm::vec2 copysPosition = glm::vec2(scale.x, position.y);
    };
}
