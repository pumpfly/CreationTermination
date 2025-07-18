#include "brewEngine/rendering/BackgroundComponent.h"

namespace gl3::brewEngine::rendering {

    BackgroundComponent::BackgroundComponent(ecs::guid_t owner, glm::vec2 copyPosition,
        float scrollingSpeed, bool isScrollingSideways, bool goesLeftOrUp) :
    Component(owner),
    copyPosition(copyPosition),
    scrollingSpeed(scrollingSpeed),
    isScrollingSideways(isScrollingSideways),
    goesLeftOrUp(goesLeftOrUp){}
}