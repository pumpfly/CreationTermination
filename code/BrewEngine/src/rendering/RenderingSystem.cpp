#include "brewEngine/rendering/RenderingSystem.h"

using gl3::brewEngine::rendering::SpriteComponent;

namespace gl3::brewEngine::rendering {
    RenderingSystem::RenderingSystem(Game &game) : System(game) {
            game.onBeforeUpdate.addListener([&] (Game &) {
                game.componentManager.forEachComponent<SpriteComponent>([&](SpriteComponent& sprite) {
                    Entity* entity;
                    TransformComponent* entityTransform;
                    SpriteComponent* entitySprite;
                    BackgroundComponent* background;

                    entity = &game.entityManager.getEntity(sprite.entity());
                    entityTransform = &entity->getComponent<TransformComponent>();
                    entitySprite = &entity->getComponent<SpriteComponent>();

                    // Sprites meant for the Background need to render a copy of the sprite, which will be rendered directly
                    // at the end of the original sprite.
                    if(game.componentManager.hasComponent<BackgroundComponent>(entity->guid())) {
                        background = &entity->getComponent<BackgroundComponent>();
                        SpriteRenderer::Instance().DrawSprite(
                        entitySprite->sprite,
                        entityTransform->localPosition,
                        entityTransform->localScale,
                        0,
                        entitySprite->color);
                        //Copy
                        SpriteRenderer::Instance().DrawSprite(
                         entitySprite->sprite,
                         background->copyPosition,
                         entityTransform->localScale,
                         0,
                         entitySprite->color);
                    }
                    else if(sprite.frameCount != 0){
                        SpriteRenderer::Instance().DrawSpriteSheet(
                        entitySprite->sprite,
                        animateSpriteSheet(&entity->getComponent<SpriteComponent>(), game.getDeltaTime()),
                        glm::vec4(entityTransform->localPosition, entityTransform->localScale),
                        entityTransform->localZRotation,
                        entitySprite->color);
                    }
                    else {
                        SpriteRenderer::Instance().DrawSprite(
                         entitySprite->sprite,
                         entityTransform->localPosition,
                         entityTransform->localScale,
                         entityTransform->localZRotation,
                         entitySprite->color);
                    }
                });
            });
        game.onUpdate.addListener([&] (Game &g, float deltaTime) {
            g.componentManager.forEachComponent<BackgroundComponent>([&](BackgroundComponent& Bcomponent) {
                Entity* Background = &g.entityManager.getEntity(Bcomponent.entity());
                TransformComponent* bTransform = &Background->getComponent<TransformComponent>();
                scrollBackgroundSprite(bTransform, &Bcomponent, Bcomponent.isScrollingSideways,
                    Bcomponent.goesLeftOrUp, deltaTime);
            });
        });
    }

    void RenderingSystem::scrollBackgroundSprite(TransformComponent* backgroundTransform, BackgroundComponent* background,
        bool isScrollingSideways, bool goesLeftOrUp, float deltaTime) {
        // If isScrollingSideways and goesLeftOrUp is true then the background will scroll to the left
        // If isScrollingSideways is true but goesLeftOrUp is false then the background will scroll to the right
        // If isScrollingSideways is false but goesLeftOrUp is true the background will move up along the y axis
        // If isScrollingSideways and goesLeftOrUp is false, the background will go down
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

        // for horizontal background scrolling
        if(isScrollingSideways) {
            backgroundTransform->localPosition.x += offset * background->scrollingSpeed;
            background->copyPosition.x += offset * background->scrollingSpeed;

            if(backgroundTransform->localPosition.x <= sign * backgroundTransform->localScale.x) {
                backgroundTransform->localPosition.x = background->copyPosition.x + backgroundTransform->localScale.x;
            }
            else if(background->copyPosition.x <= sign* backgroundTransform->localScale.x) {
                background->copyPosition.x = backgroundTransform->localPosition.x  + backgroundTransform->localScale.x;
            }
        } // for vertical background scrolling
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
        if(entitiesSprite->spriteAnimTimer >= 1/entitiesSprite->framesPerSecond) {
            entitiesSprite->spriteAnimIndex = (entitiesSprite->spriteAnimIndex + 1) % entitiesSprite->frameCount;
            entitiesSprite->spriteAnimTimer = 0;
        }
        return {entitiesSprite->spriteFrameSize.x * entitiesSprite->spriteAnimIndex, 0, entitiesSprite->spriteFrameSize};
    }
}

