#include "brewEngine/rendering/SpriteComponent.h"


namespace gl3::brewEngine::rendering{
    SpriteComponent::SpriteComponent(gl3::brewEngine::ecs::guid_t owner, const char* spritePath) : Component(owner) {
        sprite = Texture2D::FromFile(spritePath);
    }

    SpriteComponent::SpriteComponent(ecs::guid_t owner, const char *spritePath, glm::vec2 frameSize, int frameCount,
                                     float framesPerSecond, glm::vec4 color)
    : Component(owner), frameSize(frameSize), frameCount(frameCount), framesPerSecond(framesPerSecond), color(color){
        sprite = Texture2D::FromFile(spritePath);
        spriteFrameSize = glm::vec2(frameSize.x, frameSize.y);
        this->frameCount = frameCount;
    }
}

