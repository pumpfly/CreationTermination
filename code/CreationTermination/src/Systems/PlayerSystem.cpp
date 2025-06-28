#include "PlayerSystem.h"

#include "../Components/MissileComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::rendering::SpriteComponent;

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
            std::cout<< "got in" << std::endl;
            witchPlayer->madeFirstShot = true;
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};

            Entity* defaultMissile = &game.entityManager.createEntity();
            MissileComponent* defaultMissileComponent = &defaultMissile->addComponent<MissileComponent>(400.0f, DEFAULT);
            TransformComponent* defaultMissileTransform =
                &defaultMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - 90, glm::vec2(10, 10), 10);
            SpriteComponent* missileSprite = &defaultMissile->addComponent<SpriteComponent>("sprites/a.png");

            witchPlayer->missilesShot++;
            if(witchPlayer->missilesShot == 100) {
                auto &missile = game.entityManager.getEntity(defaultMissileComponent->entity());
                game.entityManager.deleteEntity(missile);
            }
            game.countdown = game.countdownReset;
        }
        if(Input::IsKeyDown(Input::KEY_R)) {
            auto angle = glm::radians(witchTransform->localZRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset = {forwardVec.x * witchTransform->localScale.x, witchTransform->localScale.y/2};
            for(int i = 0; i <= 8; i++) {
                Entity* defaultMissile = &game.entityManager.createEntity();
                MissileComponent* waveMissielComponent = &defaultMissile->addComponent<MissileComponent>(400.0f, WAVE);
                TransformComponent* defaultMissileTransform =
                &defaultMissile->addComponent<TransformComponent>(game.origin, witchTransform->localPosition + offset,
                    witchTransform->localZRotation - (45.0f + (i * 10.0f)), glm::vec2(5, 5), 5);
                SpriteComponent* missileSprite = &defaultMissile->addComponent<SpriteComponent>("sprites/a.png");
                if(witchPlayer->missilesShot == 150) {
                    auto &missile = game.entityManager.getEntity(waveMissielComponent->entity());
                    game.entityManager.deleteEntity(missile);
                }
                game.countdown = game.countdownReset;
            }
        }
        if(Input::IsKeyDown(Input::KEY_F)) {

        }
    }
}
