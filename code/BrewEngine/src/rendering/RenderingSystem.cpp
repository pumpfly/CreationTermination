#include "brewEngine/rendering/RenderingSystem.h"

using gl3::brewEngine::rendering::SpriteComponent;

namespace gl3::brewEngine::rendering {
    void RenderingSystem::scrollBackgroundSprite(TransformComponent* backgroundTransform, BackgroundComponent* background, bool isScrollingSideways, bool goesLeftOrUp, float deltaTime) {
        // If isScrollingSideways and goesLeftOrDown is true then the background will scroll to the left
        // If isScrollingSideways is true but goesLeftOrDown is false then the background will scroll to the right
        // If isScrollingSideways is false but goesLeftOrDown is true the background will move up along the y axis
        // If isScrollingSideways and goesLeftOrDown is false, the background will go down
        float offset;
        float sign;

        if(goesLeftOrUp) {
            offset = -1.0f * deltaTime;
            sign = -1;
        }
        else {
            offset = 1.0f * deltaTime;
            sign = 1;
        }

        if(isScrollingSideways) {
            backgroundTransform->localPosition.x += offset * background->scrollingSpeed;
            background->copyPosition.x += offset * background->scrollingSpeed;

            if(backgroundTransform->localPosition.x <= sign * backgroundTransform->localScale.x) {
                backgroundTransform->localPosition.x = background->copyPosition.x + backgroundTransform->localScale.x;
            }
            else if(background->copyPosition.x <= sign* backgroundTransform->localScale.x) {
                background->copyPosition.x = backgroundTransform->localPosition.x  + backgroundTransform->localScale.x;
            }
        }
        else {
            backgroundTransform->localPosition.y += offset * background->scrollingSpeed;
            background->copyPosition.y += offset * background->scrollingSpeed;

            if(backgroundTransform->localPosition.y <= sign * backgroundTransform->localScale.y) {
                backgroundTransform->localPosition.y = background->copyPosition.y + backgroundTransform->localScale.y;
            }
            else if(background->copyPosition.y <= sign * backgroundTransform->localScale.y) {
                background->copyPosition.y = backgroundTransform->localPosition.y + backgroundTransform->localScale.y;
            }
        }
    }
    glm::vec4 RenderingSystem::animateSpriteSheet(SpriteComponent *entitiesSprite, float deltaTime) {
        entitiesSprite->spriteAnimTimer += deltaTime;
        if(entitiesSprite->spriteAnimTimer >= 0.2f) {
            entitiesSprite->spriteAnimIndex = (entitiesSprite->spriteAnimIndex + 1) % entitiesSprite->frameCount;
            entitiesSprite->spriteAnimTimer = 0;
        }
        return {entitiesSprite->spriteFrameSize.x * entitiesSprite->spriteAnimIndex, 0, entitiesSprite->spriteFrameSize};
    }
}

