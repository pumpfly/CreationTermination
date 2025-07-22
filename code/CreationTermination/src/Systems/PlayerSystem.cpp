#include "PlayerSystem.h"

#include <iostream>

#include "../Components/MissileComponent.h"
#include "../Components/ShieldComponent.h"
#include "brewEngine/Config.h"
#include "brewEngine/collision/ColliderComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::rendering::SpriteComponent;
using gl3::brewEngine::collision::ColliderComponent;

PlayerSystem::PlayerSystem(Game &game, Entity *Witch, int& shieldCooldownUINumber): System(game) {

    //Loading Sprites
    missileSprite = gl3::brewEngine::rendering::Texture2D::FromFile("sprites/witchMissile.png");
    shieldSprite = gl3::brewEngine::rendering::Texture2D::FromFile("sprites/shield.png");

    game.onBeforeUpdate.addListener([&, Witch] (Game& g) {
        if(game.getGameState() != GAME_ACTIVE) return;
        TransformComponent* witchTransform = &Witch->getComponent<TransformComponent>();
        PlayerComponent* witch = &Witch->getComponent<PlayerComponent>();
        ColliderComponent* witchCollider = &Witch->getComponent<ColliderComponent>();
        SpriteComponent* witchSprite = &Witch->getComponent<SpriteComponent>();
        playerMovement(game, witchTransform);
        playerShooting(game, witchTransform, witch);
        playerShield(game, witchTransform, witchCollider, shieldCooldownUINumber);

        if(witchCollider->isInvulnerable && witchCollider->invulnerabilityTimer > 0) {
            witchCollider->invulnerabilityTimer -= g.getDeltaTime();
            witchSprite->color = glm::vec4(1, 0, 0, 1);
        }
        else {
            witchSprite->color = glm::vec4(1, 1, 1, 1);
            witchCollider->invulnerabilityTimer = witchCollider->timeBetweenDamage;
            witchCollider->isInvulnerable = false;
        }
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
        if(witchTransform->localPosition.x > game.getContext().getWindowWidth()) isTooFarRight = true;
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

void PlayerSystem::playerShield(Game& game, TransformComponent* witchTransform, ColliderComponent* witchCollider, int& shieldCooldownUINumber) {
    // SHIELD
    shieldCooldown -= game.getDeltaTime();
    if(shieldCooldown <= -1) shieldCooldown = -1;
    if (shieldCooldown >= 0) {
        (shieldCooldownUINumber) = (int)shieldCooldown;
    } else (shieldCooldownUINumber) = 0;

    if(Input::IsKeyDown(Input::KEY_LEFT_SHIFT) && shieldCooldown <= 0) {
        witchCollider->isShielded = true;
        shieldCooldown = 12;

        Entity* shieldEntity = nullptr;
        ShieldComponent* shieldComponent = nullptr;
        TransformComponent* shieldTransformComponent = nullptr;
        SpriteComponent* shieldSpriteComponent = nullptr;
        ColliderComponent* shieldColliderComponent = nullptr;
        shieldEntity = &game.entityManager.createEntity();
        shieldComponent = &shieldEntity->addComponent<ShieldComponent>(witchTransform, glm::vec2(40,40), [witchCollider] {
            witchCollider->isShielded = false;
        });
        shieldTransformComponent = &shieldEntity->addComponent<TransformComponent>(game.origin,
                witchTransform->localPosition - shieldComponent->offset,
                0,
                glm::vec2(700/3, 600/3),
                150);
        shieldSpriteComponent = &shieldEntity->addComponent<SpriteComponent>(shieldSprite);
        shieldColliderComponent = &shieldEntity->addComponent<ColliderComponent>(PLAYER, 0, [&game, shieldEntity, witchCollider] {

        });
    }
}

void PlayerSystem::playerShooting(Game &game, TransformComponent* witchTransform, PlayerComponent* witchPlayer) {
    countdown -= game.getDeltaTime();
    //Default Missiles
    if(countdown <= 0) {
        if(Input::IsKeyDown(Input::KEY_SPACE) && !Input::IsKeyDown(Input::KEY_E) && !Input::IsKeyDown(Input::KEY_F)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};

            Entity* DefaultMissile = &game.entityManager.createEntity();
            MissileComponent* defaultMissileComponent =
                &DefaultMissile->addComponent<MissileComponent>(true, 400.0f, 2.0f, DEFAULT);
            TransformComponent* defaultMissileTransform =
                &DefaultMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    0, glm::vec2(30, 30), 10);
            SpriteComponent* defaultMissileSprite =
                &DefaultMissile->addComponent<SpriteComponent>(
                    missileSprite,
                    glm::vec2(400,400),
                    3,
                    10,
                    glm::vec4(1,1,1,1));
            ColliderComponent* defaultMissileCollider = &DefaultMissile->addComponent<ColliderComponent>
            (PLAYER, 0, [&game, DefaultMissile]() {
                    if(DefaultMissile->isDeleted()) return;
                    game.entityManager.deleteEntity(*DefaultMissile);
                });

            countdown = countdownReset;
        }
        if(Input::IsKeyDown(Input::KEY_E) && !Input::IsKeyDown(Input::KEY_SPACE) && !Input::IsKeyDown(Input::KEY_F)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};

            Entity* WaveMissile = nullptr;
            MissileComponent* waveMissiel = nullptr;
            TransformComponent* wavetMissileTransform = nullptr;
            SpriteComponent* waveMissileSprite = nullptr;
            ColliderComponent* waveMissileCollider = nullptr;
            for(int i = 0; i <= 5; i++) {
                WaveMissile = &game.entityManager.createEntity();
                waveMissiel = &WaveMissile->addComponent<MissileComponent>(true, 400.0f, 0.5, WAVE);
                wavetMissileTransform =
                &WaveMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - (-45.0f + (i * 20.0f)), glm::vec2(15, 15), 5);
                waveMissileSprite = &WaveMissile->addComponent<SpriteComponent>(missileSprite,
                    glm::vec2(400,400),
                    3,
                    10,
                    glm::vec4(1,1,1,1));
                waveMissileCollider = &WaveMissile->addComponent<ColliderComponent>(PLAYER, 0, [&game, WaveMissile, witchPlayer]{
                    if(WaveMissile->isDeleted()) return;
                    if(WaveMissile != nullptr) {
                        game.entityManager.deleteEntity(*WaveMissile);
                    }
                });
            }
            countdown = countdownReset;
        }
        if(Input::IsKeyDown(Input::KEY_F) && !Input::IsKeyDown(Input::KEY_SPACE) && !Input::IsKeyDown(Input::KEY_E)) {
            witchPlayer->chargingMissile = true;

            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y / -30};

            guid_t currMissileID = -1;

            if(!witchPlayer->isCreatingSingleMissile) {
                Entity* ChargeMissile = &game.entityManager.createEntity();
                chargeMissile = &ChargeMissile->addComponent<MissileComponent>(true, true, 400.0f, CHARGE);

                auto* chargeMissileTransform = &ChargeMissile->addComponent<TransformComponent>(
                    game.origin,
                    witchTransform->localPosition + offset,
                    0,
                    glm::vec2(30, 30),
                    10);

                auto* chargeMissileSprite = &ChargeMissile->addComponent<SpriteComponent>(
                    missileSprite,
                    glm::vec2(400,400),
                    3,
                    10,
                    glm::vec4(1,1,1,1));

                auto* chargeMissileHealth = &ChargeMissile->addComponent<HealthComponent>(1);

                guid_t missileID = ChargeMissile->guid();

                //Trying to prevent corrupted stacks or function pointer corruption with a bunch of try catches
                auto* chargeMissileCollider = &ChargeMissile->addComponent<ColliderComponent>(
                    PLAYER, 0.3, [this, &game, missileID]() {
                        try {
                            auto& entity = game.entityManager.getEntity(missileID);
                            if (entity.isDeleted()) return;

                            auto& health = entity.getComponent<HealthComponent>();
                            auto& transform = entity.getComponent<TransformComponent>();
                            auto& collider = entity.getComponent<ColliderComponent>();
                            auto& missile = entity.getComponent<MissileComponent>();

                            if (collider.isInvulnerable) return;
                            if (missile.isBeingCharged) return;

                            if(health.health == 0) {
                                game.entityManager.deleteEntity(entity);
                            } else {
                                health.health--;
                                transform.localScale.x -= transform.localScale.x/3;
                                transform.localScale.y -= transform.localScale.y/3;
                                transform.radius -= transform.radius/3;
                                collider.invulnerabilityTimer = collider.timeBetweenDamage;
                                collider.isInvulnerable = true;
                            }
                        } catch(...) {
                            // ChargeMissile or component doesn't exist
                            return;
                        }
                    });

                currMissileID = missileID;
                witchPlayer->currentMissileID = currMissileID;
                witchPlayer->isCreatingSingleMissile = true;
            } else {
                currMissileID = witchPlayer->currentMissileID;
            }

            if(currMissileID != -1) {
                try {
                    auto& entity = game.entityManager.getEntity(currMissileID);
                    if (!entity.isDeleted()) {
                        auto& transform = entity.getComponent<TransformComponent>();
                        auto& collider = entity.getComponent<ColliderComponent>();
                        auto& health = entity.getComponent<HealthComponent>();

                        // Update missile size
                        if(transform.localScale.x <= 100.0f) {
                            witchPlayer->missileTempSize = (witchPlayer->missileTempSize + 100.0f) * game.getDeltaTime();
                            transform.localScale += witchPlayer->missileTempSize;
                            transform.radius += witchPlayer->missileTempSize;
                            collider.isInvulnerable = false;
                        }

                        transform.localPosition = witchTransform->localPosition + offset;

                        if(health.health <= 5) {
                            health.health++;
                        }
                    }
                } catch(...) {
                    // ChargeMissile doesn't exist anymore
                    witchPlayer->currentMissileID = -1;
                }
            }
        }

        if(Input::IsKeyReleased(Input::KEY_F)) {
            if(witchPlayer->currentMissileID != -1) {
                try {
                    auto& entity = game.entityManager.getEntity(witchPlayer->currentMissileID);
                    if (!entity.isDeleted()) {
                        auto& missile = entity.getComponent<MissileComponent>();
                        missile.isBeingCharged = false;
                    }
                } catch(...) {
                    // ChargeMissile doesn't exist
                }
            }
            witchPlayer->isCreatingSingleMissile = false;
        }
    }
}
