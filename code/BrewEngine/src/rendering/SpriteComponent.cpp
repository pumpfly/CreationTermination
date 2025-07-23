#include "brewEngine/rendering/SpriteComponent.h"


namespace gl3::brewEngine::rendering{
    SpriteComponent::SpriteComponent(ecs::guid_t owner, Texture2D sprite, glm::vec4 color)
    : Component(owner), sprite(sprite), color(color){}

    SpriteComponent::SpriteComponent(ecs::guid_t owner, Texture2D sprite, glm::vec2 frameSize, int frameCount,
                                     float framesPerSecond, glm::vec4 color)
    : Component(owner),
    sprite(sprite),
    frameSize(frameSize),
    frameCount(frameCount),
    framesPerSecond(framesPerSecond),
    color(color)
    {
        spriteFrameSize = glm::vec2(frameSize.x, frameSize.y);
    }
}

