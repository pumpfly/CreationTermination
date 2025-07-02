#pragma once

#include "SpriteComponent.h"
#include "SpriteRenderer.h"
#include "brewEngine/ecs/System.h"
#include "brewEngine/rendering/BackgroundComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

namespace gl3::brewEngine::rendering{
    class RenderingSystem : public System {
    public:
        explicit RenderingSystem(Game &game) : System(game) {
            game.onBeforeUpdate.addListener([&] (Game &) {
                game.componentManager.forEachComponent<SpriteComponent>([&](SpriteComponent& sprite) {
                    Entity* entity;
                    TransformComponent* entityTransform;
                    SpriteComponent* entitySprite;
                    BackgroundComponent* background;

                    entity = &game.entityManager.getEntity(sprite.entity());
                    entityTransform = &entity->getComponent<TransformComponent>();
                    entitySprite = &entity->getComponent<SpriteComponent>();

                    if(game.componentManager.hasComponent<BackgroundComponent>(entity->guid())) {
                        background = &entity->getComponent<BackgroundComponent>();
                        SpriteRenderer::Instance().DrawSprite(
                        entitySprite->sprite,
                        entityTransform->localPosition,
                        entityTransform->localScale,
                        0,
                        glm::vec4(1,1,1,1));
                        //Copy
                        SpriteRenderer::Instance().DrawSprite(
                         entitySprite->sprite,
                         background->copyPosition,
                         entityTransform->localScale,
                         0,
                         glm::vec4(1,1,1,1));
                    }
                    else if(sprite.frameCount != 0){
                        SpriteRenderer::Instance().DrawSpriteSheet(
                        entitySprite->sprite,
                        animateSpriteSheet(&entity->getComponent<SpriteComponent>(), game.getDeltaTime()),
                        glm::vec4(entityTransform->localPosition, entityTransform->localScale),
                        entityTransform->localZRotation,
                        glm::vec4(1,1,1,1));
                    }
                    else {
                        SpriteRenderer::Instance().DrawSprite(
                         entitySprite->sprite,
                         entityTransform->localPosition,
                         entityTransform->localScale,
                         0,
                         glm::vec4(1,1,1,1));
                    }
                });
            });
        }
        void scrollBackgroundSprite(TransformComponent* backgroundTransform, BackgroundComponent* background,
            bool isScrollingSideways, bool goesLeftOrUp, float deltaTime);
        glm::vec4 animateSpriteSheet(SpriteComponent* entitiesSprite, float deltaTime);
    };
}
