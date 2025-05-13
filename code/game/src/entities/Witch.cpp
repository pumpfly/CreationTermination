//
// Created by pumf on 24/10/2024.
//

#include "Witch.h"

#include <iostream>

#include "../input/Input.h"
#include "Missiles.h"
#include "../Game.h"
#include "../Assets.h"

namespace gl3{
    Witch::Witch(Game* game, glm::vec2 position, float zRotation, glm::vec2 size, float radius, glm::vec4 color,
        Texture2D texture, TYPE type)
    : Entity(position,zRotation,size, radius, color,texture, type){

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
            // - 90 because mesh up is +y
            auto missile =
                std::make_unique<Missiles>(game->getWitch()->position + offset, zRotation - 90, glm::vec2(10, 10), 10);
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
                std::make_unique<Missiles>(game->getWitch()->position + offset,
                    zRotation - 90, glm::vec2(10, 10), 10);
                bigMissiles.push_back(std::move(bigM));
            }
            if(bigMissiles.back()->getSize().x <= 50.0f) {
                missileTempSize = (missileTempSize + 100.0f) * deltaTime;
                bigMissiles.back()->setSize(bigMissiles.back()->getSize() + missileTempSize);
                bigMissiles.back()->setRadius(bigMissiles.back()->getRadius() + missileTempSize);
            }
            //TODO: it should grow from the center
            bigMissiles.back()->setPosition(game->getWitch()->position + offset); //this->getPosition()
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
                std::make_unique<Missiles>(game->getWitch()->position + offset, zRotation - (45.0f + (i * 10.0f)),
                    glm::vec2(5.0f, 5.0f), 5);
                waveMissiles.push_back(std::move(waveM));
            }
        }

        if(brew::Input::IsKeyDown(brew::Input::KEY_LEFT_CONTROL) || brew::Input::IsKeyPressed(brew::Input::KEY_RIGHT_CONTROL)) {
            shield =
                std::make_unique<Shield>(game,
                    game->getWitch()->position, zRotation, glm::vec2(120, 120), 120);
            shield->setPosition(this->getPosition());
        }
        if(brew::Input::IsKeyReleased(brew::Input::KEY_LEFT_CONTROL) || brew::Input::IsKeyReleased(brew::Input::KEY_RIGHT_CONTROL)) {
            shield.reset(nullptr);
        }

        // Normal Missiles
        for (auto &m: missiles) {
            //m->setID();
            m->update(game, deltaTime);
        }
        if (missiles.size() >= 100) {
            missiles.erase(missiles.begin());
        }

        // Big Missiles
        for(auto &b: bigMissiles) {
            b->update(game, deltaTime);
            /*for(auto &other: game->getEntities()) {
                if(b != other && b->checkCollision(*other)) {
                    std::cout << b->checkCollision(*other) << std::endl;
                    b->setColor({1, 0, 0, 1});
                }
            }*/
        }
        if (bigMissiles.size() >= 20) {
            bigMissiles.erase(bigMissiles.begin());
        }

        // Wave Missiles
        for(auto &w: waveMissiles) {
            w->update(game, deltaTime);
            /*for(auto &other: game->getEntities()) {
                if(w != other && w->checkCollision(*other)) {
                    std::cout << w->checkCollision(*other) << std::endl;
                    w->setColor({1, 0, 0, 1});
                }
            }*/

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
    }
}
