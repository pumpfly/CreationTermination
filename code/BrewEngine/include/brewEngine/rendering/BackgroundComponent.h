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
        /// An entity with a BackgroundComponent is like the name implies the Background of the games scene.
        /// Background entities have the possibility to scroll.
        /// To make the scrolling seamless a copy of the backgrounds sprite will be rendered which ideally will be positioned at the end of the original sprite
        /// even though the user can freely choose what value @param copyPosition should have. While the background moves the original image and the copy
        /// will switch places, this results in an endless loop.
        /// The User has also the possibility to change the speed of the scrolling, if the background should not scroll the speed should be set to 0;
        /// If @param isScrollingSideways and @param goesLeftOrUp is true then the background will scroll to the left
        /// If @param isScrollingSideways is true but @param goesLeftOrUp is false then the background will scroll to the right
        /// If @param isScrollingSideways is false but @param goesLeftOrUp is true the background will move up along the y axis
        /// If @param isScrollingSideways and @param goesLeftOrUp is false, the background will go down
        /// Depending on if the background should left, right, up or down the copy should be positioned accrodingly.
        explicit BackgroundComponent(ecs::guid_t owner, glm::vec2 copyPosition,
            float scrollingSpeed, bool isScrollingSideways, bool goesLeftOrUp);

        ~BackgroundComponent() override { deleted = true; }

        float scrollingSpeed = 0.0f;
        glm::vec2 copyPosition = glm::vec2(0.0f);
        bool isScrollingSideways = false;
        bool goesLeftOrUp = false;
    };
}
