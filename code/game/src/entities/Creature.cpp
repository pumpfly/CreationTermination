//
// Created by Lisa B on 29/10/2024.
//

#include "Creature.h"

#include <iostream>
#include <random>
#include "../Assets.h"
#include "../Game.h"
#include <iostream>
#include <cmath>

namespace gl3 {
    Creature::Creature(Game * game, glm::vec2 position, float zRotation, glm::vec2 scale, Texture2D texture)
    : Entity(position, zRotation, scale, color, texture){

        audio.init();
        audio.setGlobalVolume(0.1f);
        firingSound.load(resolveAssetPath("audio/shot.mp3").string().c_str());
        firingSound.setSingleInstance(true);

    }
     float lerp(float a, float b, float f)
    {
        return a - f*(b - a);
    }

    void Creature::update(Game* game, float deltaTime)
    {
        std::time_t elapsedTime = std::time(nullptr);
        const auto shipPosition = game->getShip()->getPosition();
        auto distanceToShip = glm::distance(position, shipPosition);
        float delta_x = this->getPosition().x - shipPosition.x;
        float delta_y = this->getPosition().y - shipPosition.y;
        float theta_radians = atan2(delta_y, delta_x);

        zRotation = glm::degrees(theta_radians) - 90.0f;

        if(position.y < 1.2 && position.y > -1.2) {
            position.y = lerp(position.y, shipPosition.y, deltaTime * speed);
            if(position.y == shipPosition.y) {
                if(shipPosition.y == 0) {
                    std::cout << "they are equal and 0" << std::endl;
                    position.y = lerp(position.y+0.02f, shipPosition.y, deltaTime * speed * 2);
                }
                else {
                    position.y = lerp(position.y*0.02f, shipPosition.y, deltaTime * speed* 2.0f);
                }
            }
        }
        else if (position.y >= 1.2 || position.y <= -1.2) {
            if(position.y >= 1.2 && lerp(position.y, shipPosition.y, deltaTime * speed) < position.y) {
                position.y = lerp(position.y, shipPosition.y, deltaTime * speed);
            }
            else if(position.y <= -1.2 && lerp(position.y, shipPosition.y, deltaTime * speed) > position.y){
                position.y = lerp(position.y, shipPosition.y, deltaTime * speed);
            }
        }

        //std::cout << position.y << std::endl;
        /*
         * Shooting
         */
        countdownUntilNextShot -= deltaTime;
        if (elapsedTime % 5 == 0 && countdownUntilNextShot <= 0)
        {
            // -90 because mesh forward is +y
            auto angle = glm::radians(zRotation - 90);
            glm::vec2 forwardVec = {glm::cos(angle), glm::sin(angle)};
            glm::vec2 offset{forwardVec.x * getScale().x, forwardVec.y * getScale().y};
            auto missile =
                    std::make_unique<Missile>(game, position + offset, zRotation - 180, glm::vec2(0.05f, 0.05f));
            missiles.push_back(std::move(missile));
            countdownUntilNextShot = timeBetweenShots;
        }

        for (auto& m: missiles)
        {
            m->update(game, deltaTime);
        }
        if (missiles.size() >= 100)
        {
            missiles.erase(missiles.begin());
        }

    }

    void Creature::draw(Game* game)
    {
        Entity::draw(game);
        for (auto& m: missiles)
        {
            m->draw(game);
        }
    }

}
