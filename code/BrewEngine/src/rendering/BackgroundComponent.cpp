#include "brewEngine/rendering/BackgroundComponent.h"

namespace gl3::brewEngine::rendering {

    BackgroundComponent::BackgroundComponent(ecs::guid_t owner, glm::vec2 copyPosition, float scrollingSpeed)  : Component(owner){
        this->copyPosition = copyPosition;
        this->scrollingSpeed = scrollingSpeed;
    }
}