#pragma once
#include "brewEngine/ecs/Component.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/EntityManager.h"
#include "brewEngine/ecs/ecs.h"
#include "brewEngine/sceneGraph/TransformComponent.h"
#include "glm/vec2.hpp"

using gl3::brewEngine::ecs::ComponentManager;
using gl3::brewEngine::ecs::Entity;

namespace gl3::brewEngine::rendering {
    class BackgroundComponent final : public ecs::Component{
        friend ComponentManager;
        friend Entity;

        public:
        explicit BackgroundComponent(ecs::guid_t owner, glm::vec2 copyPosition,
            float scrollingSpeed, bool isScrollingSideways, bool goesLeftOrUp);
        ~BackgroundComponent() override { deleted = true; }

        float scrollingSpeed = 0.0f;
        glm::vec2 copyPosition = glm::vec2(0.0f);
        bool isScrollingSideways = false;
        bool goesLeftOrUp = false;
    };
}
