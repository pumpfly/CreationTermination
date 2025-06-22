#pragma once
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ecs.h"
#include "glm/vec2.hpp"

namespace gl3::brewEngine::rendering {
    class BackgroundComponent : public ecs::Component{
        friend ecs::ComponentManager;
        friend ecs::Entity;

        public:
        BackgroundComponent(ecs::guid_t owner, glm::vec2 position, glm::vec2 copysPosition, float scrollingSpeed, glm::vec2 scale);
        ~BackgroundComponent() override { deleted = true; }

        float scrollingSpeed;
        glm::vec2 scale;
        glm::vec2 position;
        glm::vec2 copysPosition = position;
    };
}
