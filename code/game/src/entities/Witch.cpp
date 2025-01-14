//
// Created by pumf on 24/10/2024.
//

#include "Witch.h"

#include <iostream>

#include "../input/Input.h"
#include "Missile.h"
#include "../Game.h"
#include "../Assets.h"

namespace gl3{
    Witch::Witch(Game* game, glm::vec2 position, float zRotation, glm::vec2 scale, glm::vec4 color, Texture2D texture)
    : Entity(position,zRotation,scale,color,texture){

        audio.init();
        audio.setGlobalVolume(0.1f);
        firingSound.load(resolveAssetPath("audio/shot.mp3").string().c_str());
        firingSound.setSingleInstance(true);

    }

    void Witch::update(Game *game, float deltaTime) {
        auto window = game->getWindow();
        glm::vec2 forward(0.0f, 0.0f);
        forward.x += cos(glm::radians(zRotation));
        forward.y += sin(glm::radians(zRotation));
        forward = forward * translationSpeed * deltaTime;

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            position -= forward * 200.0f;
        }

        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            position += forward * 200.0f;
        }

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            position.y = position.y - translationSpeed * deltaTime * 200;
        }

        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            position.y = position.y + translationSpeed * deltaTime * 200;
        }
        countdownUntilNextShot -= deltaTime;
        // Normal shooting
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && countdownUntilNextShot <= 0) {
            audio.play(firingSound);
            auto angle = glm::radians(zRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * getScale().x, getScale().y / 2};
            // - 90 because mesh up is +y
            auto missile =
                std::make_unique<Missile>(game, game->getShip()->position + offset, zRotation - 90, glm::vec2(10, 10));
            missiles.push_back(std::move(missile));
            countdownUntilNextShot = timeBetweenShots;
        }

        // Charging shot
        if(brew::Input::IsKeyDown(brew::Input::KEY_F)) {
            charging = true;
            auto angle = glm::radians(zRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * getScale().x, getScale().y / 2 - 10};
            if(!onlySingleMissile) {
                auto bigM =
                std::make_unique<Missile>(game,
                    game->getShip()->position + offset, zRotation - 90, glm::vec2(10, 10));
                bigMissiles.push_back(std::move(bigM));
            }
            if(bigMissiles.back()->getScale().x <= 50.0f) {
                missileTempSize = (missileTempSize + 33.0f) * deltaTime;
                bigMissiles.back()->setScale(bigMissiles.back()->getScale()* missileTempSize);
            }
            //TODO: it should grow from the center
            bigMissiles.back()->setPosition(game->getShip()->position + offset); //this->getPosition()
            onlySingleMissile = true;
        }
        if(brew::Input::IsKeyReleased(brew::Input::KEY_F) && charging) {
            std::cout << "f released" << std::endl;
            onlySingleMissile = false;
        }

        //Wave shot
        if(brew::Input::IsKeyPressed(brew::Input::KEY_E)) {
            auto angle = glm::radians(zRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * getScale().x, getScale().y / 2 - 10};
            for(int i = 0; i <= 8; i++) {
                auto waveM =
                std::make_unique<Missile>(game,
                    game->getShip()->position + offset, zRotation - (45.0f + (i * 10.0f)), glm::vec2(5.0f, 5.0f));
                waveMissiles.push_back(std::move(waveM));
            }
        }

        if(brew::Input::IsKeyDown(brew::Input::KEY_LEFT_CONTROL) || brew::Input::IsKeyPressed(brew::Input::KEY_RIGHT_CONTROL)) {
            shield =
                std::make_unique<Shield>(game,
                    game->getShip()->position, zRotation, glm::vec2(0.25, 0.25));
            shield->setPosition(this->getPosition());
        }
        if(brew::Input::IsKeyReleased(brew::Input::KEY_LEFT_CONTROL) || brew::Input::IsKeyReleased(brew::Input::KEY_RIGHT_CONTROL)) {
            shield.reset(nullptr);
        }

        // Normal Missiles
        for (auto &m: missiles) {
            m->update(game, deltaTime);

        }
        if (missiles.size() >= 100) {
            missiles.erase(missiles.begin());
        }
        // Big Missiles
        for(auto &b: bigMissiles) {
            b->update(game, deltaTime);
        }
        if (bigMissiles.size() >= 20) {
            bigMissiles.erase(bigMissiles.begin());
        }
        // Wave Missiles
        for(auto &w: waveMissiles) {
            w->update(game, deltaTime);
        }
        if (waveMissiles.size() >= 150) {
            waveMissiles.erase(waveMissiles.begin());
        }

        // Shield
        if(shield) shield->update(game, deltaTime);
    }
    void Witch::draw(Game *game) {
        Entity::draw(game);
        for (auto &m: missiles) {
            m->draw(game);
        }
        for(auto &b: bigMissiles) {
            b->draw(game);
        }
        for(auto &w : waveMissiles) {
            w->draw(game);
        }
        if(shield) shield->draw(game);
        //SpriteRenderer::Instance().DrawSprite(game, texture, position,
            //scale, zRotation, color);
    }
}
