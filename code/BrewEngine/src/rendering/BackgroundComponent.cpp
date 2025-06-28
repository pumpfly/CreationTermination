#include "brewEngine/rendering/BackgroundComponent.h"

namespace gl3::brewEngine::rendering {

    BackgroundComponent::BackgroundComponent(ecs::guid_t owner, glm::vec2 position, glm::vec2 copyPosition, float scrollingSpeed, glm::vec2 scale) {
        this->position = position;
        this->copyPosition = copyPosition;
        this->scrollingSpeed = scrollingSpeed;
        this->scale = scale;
    }
}