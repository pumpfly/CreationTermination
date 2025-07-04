#include "PlayerSystem.h"

#include <iostream>

#include "../Components/MissileComponent.h"
#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::collision::ColliderComponent;

void PlayerSystem::playerMovement(Game &game, TransformComponent* witchTransform)  {

    glm::vec2 forward(0.0f, 0.0f);
    forward.x += cos(glm::radians(witchTransform->localZRotation));
    forward.y += sin(glm::radians(witchTransform->localZRotation));
    forward = forward * game.getDeltaTime();

    if(Input::IsKeyDown(Input::KEY_A)) {
        witchTransform->localPosition.x -= forward.x * 200.0f;
    }
    if(Input::IsKeyDown(Input::KEY_D)) {
        witchTransform->localPosition.x += forward.x * 200.0f;
    }
    if(Input::IsKeyDown(Input::KEY_W)) {
        witchTransform->localPosition.y = witchTransform->localPosition.y - game.getDeltaTime() * 200.0f;
    }
    if(Input::IsKeyDown(Input::KEY_S)) {
        witchTransform->localPosition.y = witchTransform->localPosition.y + game.getDeltaTime() * 200.0f;
    }
}

void PlayerSystem::playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer) {
    game.countdown -= game.getDeltaTime();
    //Default Missiles
    if(game.countdown <= 0) {
        if(Input::IsKeyDown(Input::KEY_SPACE)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};

            Entity* DefaultMissile = &game.entityManager.createEntity();
            MissileComponent* defaultMissileComponent = &DefaultMissile->addComponent<MissileComponent>(400.0f, DEFAULT);
            TransformComponent* defaultMissileTransform =
                &DefaultMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - 90, glm::vec2(10, 10), 10);
            SpriteComponent* defaultMissileSprite = &DefaultMissile->addComponent<SpriteComponent>("sprites/a.png");
            ColliderComponent* defaultMissileCollider = &DefaultMissile->addComponent<ColliderComponent>(PLAYER, [this](){});
            guid_t ID = DefaultMissile->guid();

            witchPlayer->missilesShot++;
            if(witchPlayer->missilesShot == 100) {
                auto &missile = game.entityManager.getEntity(defaultMissileComponent->entity());
                game.entityManager.deleteEntity(missile);
            }
            game.countdown = game.countdownReset;
        }
        if(Input::IsKeyDown(Input::KEY_E)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};
            for(int i = 0; i <= 8; i++) {
                Entity* WaveMissile = &game.entityManager.createEntity();
                MissileComponent* waveMissiel = &WaveMissile->addComponent<MissileComponent>(400.0f, WAVE);
                TransformComponent* wavetMissileTransform =
                &WaveMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - (45.0f + (i * 10.0f)), glm::vec2(5, 5), 5);
                SpriteComponent* waveMissileSprite = &WaveMissile->addComponent<SpriteComponent>("sprites/a.png");
                ColliderComponent* waveMissileCollider = &WaveMissile->addComponent<ColliderComponent>(PLAYER, [this](){});
                if(witchPlayer->missilesShot == 150) {
                    auto &missile = game.entityManager.getEntity(waveMissiel->entity());
                    game.entityManager.deleteEntity(missile);
                }
                game.countdown = game.countdownReset;
            }
        }
        if(Input::IsKeyDown(Input::KEY_F)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y / 2 - 10};

            Entity* ChargeMissile;
            MissileComponent* chargeMissile;
            TransformComponent* chargeMissileTransform;
            SpriteComponent* chargeMissileSprite;

            guid_t currMissileID = -1;

            if(!witchPlayer->onlySingleMissile) {
                ChargeMissile = &game.entityManager.createEntity();
                chargeMissile = &ChargeMissile->addComponent<MissileComponent>(400.0f, CHARGE);
                chargeMissileTransform =
                &ChargeMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - 90, glm::vec2(10, 10), 10);
                chargeMissileSprite = &ChargeMissile->addComponent<SpriteComponent>("sprites/a.png");
                ColliderComponent* chargeMissileCollider = &ChargeMissile->addComponent<ColliderComponent>(PLAYER, [this](){});

                currMissileID = ChargeMissile->guid();
                witchPlayer->currentMissileID = currMissileID; // Store for later use
            }
            else {
                currMissileID = witchPlayer->currentMissileID;
                if(currMissileID != -1) {
                    chargeMissileTransform = &game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>();
                }
            }
            if(currMissileID != -1 && chargeMissileTransform) {
                if(chargeMissileTransform->localScale.x <= 50.0f) {
                    witchPlayer->missileTempSize = (witchPlayer->missileTempSize + 100.0f) * game.getDeltaTime();
                    game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>().localScale += witchPlayer->missileTempSize;
                    game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>().radius += witchPlayer->missileTempSize;
                }
                chargeMissileTransform->localPosition = witchTransform->localPosition + offset;
            }

            witchPlayer->onlySingleMissile = true;

            /*if(currMissileID != -1 && chargeMissileTransform && witchPlayer->missilesShot == 10) {
                auto &missile = game.entityManager.getEntity(game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>().localScale.x->entity());
                game.entityManager.deleteEntity(missile);
            }*/

        }
        if(Input::IsKeyReleased(Input::KEY_F)) {
            //TODO: isKeyRealeased is broken: fix it
            std::cout << "released F" << std::endl;
            witchPlayer->onlySingleMissile = false;
        }
    }
}
