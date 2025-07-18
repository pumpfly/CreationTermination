#include "PlayerSystem.h"

#include <iostream>

#include "../Components/MissileComponent.h"
#include "brewEngine/Config.h"
#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::collision::ColliderComponent;

PlayerSystem::PlayerSystem(Game &game, Entity *Witch): System(game) {
    if(game.getGameState() != GAME_ACTIVE) return;
    game.onBeforeUpdate.addListener([&, Witch] (Game&) {
        TransformComponent* witchTransform = &Witch->getComponent<TransformComponent>();
        PlayerComponent* witch = &Witch->getComponent<PlayerComponent>();
        playerMovement(game, witchTransform);
        playerShooting(game, witchTransform, witch);
    });
}

void PlayerSystem::playerMovement(Game &game, TransformComponent* witchTransform)  {

    glm::vec2 forward(0.0f, 0.0f);
    forward.x += cos(glm::radians(witchTransform->localZRotation));
    forward.y += sin(glm::radians(witchTransform->localZRotation));
    forward = forward * game.getDeltaTime();

    if(Input::IsKeyDown(Input::KEY_A)) {
        if(witchTransform->localPosition.x < 0) isTooFarLeft = true;
        if(!isTooFarLeft) {
            witchTransform->localPosition.x -= forward.x * 200.0f;
            isTooFarRight = false;
        }
    }
    if(Input::IsKeyDown(Input::KEY_D)) {
        if(witchTransform->localPosition.x > 1150) isTooFarRight = true;
        if(!isTooFarRight) {
            witchTransform->localPosition.x += forward.x * 200.0f;
            isTooFarLeft = false;
        }
    }
    if(Input::IsKeyDown(Input::KEY_W)) {
        if(witchTransform->localPosition.y < 0) isTooFarUp = true;
        if(!isTooFarUp) {
            witchTransform->localPosition.y = witchTransform->localPosition.y - game.getDeltaTime() * 200.0f;
            isTooFarDown = false;
        }
    }
    if(Input::IsKeyDown(Input::KEY_S)) {
        if(witchTransform->localPosition.y > 580) isTooFarDown = true;
        if(!isTooFarDown) {
            float y = gl3::brewEngine::config::ScreenSize.y;
            witchTransform->localPosition.y = witchTransform->localPosition.y + game.getDeltaTime() * 200.0f;
            isTooFarUp = false;
        }
    }
}

void PlayerSystem::playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer) {
    countdown -= game.getDeltaTime();
    //Default Missiles
    if(countdown <= 0) {
        if(Input::IsKeyDown(Input::KEY_SPACE)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};

            Entity* DefaultMissile = &game.entityManager.createEntity();
            MissileComponent* defaultMissileComponent = &DefaultMissile->addComponent<MissileComponent>(400.0f, DEFAULT);
            TransformComponent* defaultMissileTransform =
                &DefaultMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - 90, glm::vec2(30, 30), 10);
            SpriteComponent* defaultMissileSprite =
                &DefaultMissile->addComponent<SpriteComponent>("sprites/witchMissile.png",
                    glm::vec2(400,400),
                    3,
                    10,
                    glm::vec4(1,1,1,1));
            ColliderComponent* defaultMissileCollider = &DefaultMissile->addComponent<ColliderComponent>
            (PLAYER, [&game, DefaultMissile]() {
                    if(DefaultMissile->isDeleted()) return;
                    game.entityManager.deleteEntity(*DefaultMissile);
                });

            countdown = countdownReset;
        }
        if(Input::IsKeyDown(Input::KEY_E)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};

            Entity* WaveMissile = nullptr;
            MissileComponent* waveMissiel = nullptr;
            TransformComponent* wavetMissileTransform = nullptr;
            SpriteComponent* waveMissileSprite = nullptr;
            ColliderComponent* waveMissileCollider = nullptr;
            for(int i = 0; i <= 8; i++) {
                WaveMissile = &game.entityManager.createEntity();
                waveMissiel = &WaveMissile->addComponent<MissileComponent>(400.0f, WAVE);
                wavetMissileTransform =
                &WaveMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - (45.0f + (i * 10.0f)), glm::vec2(15, 15), 5);
                waveMissileSprite = &WaveMissile->addComponent<SpriteComponent>("sprites/witchMissile.png",
                    glm::vec2(400,400),
                    3,
                    10,
                    glm::vec4(1,1,1,1));
                waveMissileCollider = &WaveMissile->addComponent<ColliderComponent>(PLAYER, [&game, WaveMissile, witchPlayer]{
                    if(WaveMissile->isDeleted()) return;
                    if(WaveMissile != nullptr) {
                        game.entityManager.deleteEntity(*WaveMissile);
                    }
                });
            }
            countdown = countdownReset;
        }
        if(Input::IsKeyDown(Input::KEY_F)) {
            witchPlayer->chargingMissile = true;
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y / 2 - 10};

            Entity* ChargeMissile = nullptr;
            MissileComponent* chargeMissile = nullptr;
            TransformComponent* chargeMissileTransform = nullptr;
            SpriteComponent* chargeMissileSprite= nullptr;
            HealthComponent* chargeMissileHealth= nullptr;
            ColliderComponent* chargeMissileCollider= nullptr;

            guid_t currMissileID = -1;

            if(!witchPlayer->isCreatingSingleMissile) {
                //Creating the Chargemissile
                ChargeMissile = &game.entityManager.createEntity();
                chargeMissile = &ChargeMissile->addComponent<MissileComponent>(400.0f, CHARGE);
                chargeMissileTransform =
                &ChargeMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - 90, glm::vec2(30, 30), 10);
                chargeMissileSprite = &ChargeMissile->addComponent<SpriteComponent>("sprites/witchMissile.png",
                    glm::vec2(400,400),
                    3,
                    10,
                    glm::vec4(1,1,1,1));
                chargeMissileHealth = &ChargeMissile->addComponent<HealthComponent>(3);
                chargeMissileCollider = &ChargeMissile->addComponent<ColliderComponent>
                (PLAYER, [&game, witchPlayer, chargeMissileHealth, ChargeMissile, chargeMissileTransform]() {
                    if(ChargeMissile->isDeleted()) return;
                    //TODO: it does not get inside this if loop because the keyRelease function is not working properly
                    if(!witchPlayer->chargingMissile) {
                        if(chargeMissileHealth->health == 0) {
                        game.entityManager.deleteEntity(*ChargeMissile);
                    }
                    else {
                        chargeMissileHealth->health--;
                        chargeMissileTransform->localScale.x -= chargeMissileTransform->localScale.x/3;
                        chargeMissileTransform->localScale.y -= chargeMissileTransform->localScale.y/3;
                        chargeMissileTransform->radius -= chargeMissileTransform->radius/3;
                    }
                    }
                });
                currMissileID = ChargeMissile->guid();
                witchPlayer->currentMissileID = currMissileID; // Store for later use

            }
            else {
                // preventing nullpointer exceptions
                currMissileID = witchPlayer->currentMissileID;
                if(currMissileID != -1) {
                    chargeMissileTransform = &game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>();
                }
            }

            if(currMissileID != -1 && chargeMissileTransform) {
                //While Key is down ChargingMissile grows in size, but only up to 50 x 50
                if(chargeMissileTransform->localScale.x <= 100.0f) {
                    witchPlayer->missileTempSize = (witchPlayer->missileTempSize + 100.0f) * game.getDeltaTime();
                    game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>().localScale += witchPlayer->missileTempSize;
                    game.entityManager.getEntity(currMissileID).getComponent<TransformComponent>().radius += witchPlayer->missileTempSize;
                }
                chargeMissileTransform->localPosition = witchTransform->localPosition + offset;
            }

            witchPlayer->isCreatingSingleMissile = true;

        }
        if(Input::IsKeyReleased(Input::KEY_F)) {
            //TODO: isKeyRealeased is broken: fix it
            std::cout << "released F" << std::endl;
            witchPlayer->chargingMissile = false;
            witchPlayer->isCreatingSingleMissile = false;
        }
    }
}
