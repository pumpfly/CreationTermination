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

    glm::vec4 SpriteComponent::animateSpriteSheet(SpriteComponent *entitiesSprite, float deltaTime) {
        entitiesSprite->spriteAnimTimer += deltaTime;
        if(entitiesSprite->spriteAnimTimer >= 0.2f) {
            entitiesSprite->spriteAnimIndex = (entitiesSprite->spriteAnimIndex + 1) % entitiesSprite->frameCount;
            entitiesSprite->spriteAnimTimer = 0;
        }
        return {entitiesSprite->spriteFrameSize.x * entitiesSprite->spriteAnimIndex, 0, entitiesSprite->spriteFrameSize};
    }
}

