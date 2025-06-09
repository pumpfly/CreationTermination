//
// Created by pumf on 24/10/2024.
//

#include "Witch.h"

#include <iostream>
#include "../input/Input.h"
#include "Missiles.h"
#include "../Game.h"
#include "../Assets.h"
#include "../UI/Healthbar.h"

namespace gl3{
    Witch::Witch(Game* game, glm::vec2 position, float zRotation, glm::vec2 size, float radius, glm::vec4 color,
        Texture2D texture, int health, TYPE type)
        : Entity(position, zRotation, size, radius, color, texture, health, type){
        /*audio.init();
        audio.setGlobalVolume(0.1f);
        firingSound.load(resolveAssetPath("audio/shot.mp3").string().c_str());
        firingSound.setSingleInstance(true);*/
    }

    void Witch::update(Game *game, float deltaTime) {

        auto window = game->getWindow();
        glm::vec2 forward(0.0f, 0.0f);
        forward.x += cos(glm::radians(zRotation));
        forward.y += sin(glm::radians(zRotation));
        forward = forward * translationSpeed * deltaTime;

        // Movement
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

        // Normal shooting
        countdownUntilNextShot -= deltaTime;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && countdownUntilNextShot <= 0) {
            audio.play(firingSound);
            auto angle = glm::radians(zRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * getSize().x, getSize().y / 2};
            // - 90 because mesh up is +y (the missiles will fly to the ground otherwise)
            auto missile =
                std::make_unique<Missiles>(this->position + offset, zRotation - 90, glm::vec2(10, 10), 10);
            missiles.push_back(std::move(missile));
            countdownUntilNextShot = timeBetweenShots;
        }

        // Charging shot
        if(brew::Input::IsKeyDown(brew::Input::KEY_F)) {
            charging = true;
            auto angle = glm::radians(zRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * getSize().x, getSize().y / 2 - 10};
            if(!onlySingleMissile) {
                auto bigM =
                std::make_unique<Missiles>(this->position + offset,
                    zRotation - 90, glm::vec2(10, 10), 10);
                bigMissiles.push_back(std::move(bigM));
            }
            if(bigMissiles.back()->getSize().x <= 50.0f) {
                missileTempSize = (missileTempSize + 100.0f) * deltaTime;
                bigMissiles.back()->setSize(bigMissiles.back()->getSize() + missileTempSize);
                bigMissiles.back()->setRadius(bigMissiles.back()->getRadius() + missileTempSize);
            }
            //TODO: it should grow from the center
            bigMissiles.back()->setPosition(this->position + offset); //this->getPosition()
            onlySingleMissile = true;
        }
        if(brew::Input::IsKeyReleased(brew::Input::KEY_F) && charging) {
            onlySingleMissile = false;
        }

        //Wave shot
        if(brew::Input::IsKeyPressed(brew::Input::KEY_E)) {
            auto angle = glm::radians(zRotation);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset {forwardVec.x * getSize().x, getSize().y / 2 - 10};
            for(int i = 0; i <= 8; i++) {
                auto waveM =
                std::make_unique<Missiles>(this->position + offset, zRotation - (45.0f + (i * 10.0f)),
                    glm::vec2(5.0f, 5.0f), 5);
                waveMissiles.push_back(std::move(waveM));
            }
        }

        if(brew::Input::IsKeyDown(brew::Input::KEY_LEFT_CONTROL) || brew::Input::IsKeyPressed(brew::Input::KEY_RIGHT_CONTROL)) {
            shield =
                std::make_unique<Shield>(game,
                    this->position, zRotation, glm::vec2(120, 120), 120);
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

        // COLLISION
        this->handleCollision(game, deltaTime);

        // ANIMATION
        this->spriteAnimTimer += deltaTime;
        if (this->spriteAnimTimer >= 0.1f) {
            this->spriteAnimIndex = (this->spriteAnimIndex + 1) % 4;
            this->spriteAnimTimer = 0.0f;
        }
    }
    void Witch::draw() {
        SpriteRenderer::Instance().DrawSpritePro(texture, glm::vec4(this->spriteFrameSize.x*this->spriteAnimIndex, 0, this->spriteFrameSize),
                                                 glm::vec4(this->position, this->size), zRotation, this->color);
        for (auto &m: missiles) {
            m->draw();
        }
        for(auto &b: bigMissiles) {
            b->draw();
        }
        for(auto &w : waveMissiles) {
            w->draw();
        }
        Healthbar::Instance().backgroundPosition = glm::vec2(20.0f, 20.0f);
        Healthbar::Instance().drawHealthbar(health, 0, glm::vec4(1,1,1,1));
        if(shield) shield->draw();
    }
}
