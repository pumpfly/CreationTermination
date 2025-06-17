#include "brewEngine/rendering/SpriteComponent.h"


namespace gl3::brewEngine::rendering{
    SpriteComponent::SpriteComponent(gl3::brewEngine::ecs::guid_t owner, const char* spritePath) {
        SpriteComponent::sprite = Texture2D::FromFile(spritePath);
    }

    SpriteComponent::SpriteComponent(ecs::guid_t owner, const char *spritePath, glm::vec2 frameSize, int frames) {
        sprite = Texture2D::FromFile(spritePath);
        spriteFrameSize = glm::vec2(frameSize.x, frameSize.y);
        frameCount = frames;
    }

    void SpriteComponent::SetBackgroundLayerSpeed(int layerNumber, float layerSpeed) {

    }

    void SpriteComponent::scrollBackgroundSprite() {

    }
}

