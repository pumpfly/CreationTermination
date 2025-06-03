//
// Created by Lisa B on 29/10/2024.
//

#include "Creature.h"

#include <iostream>
#include <random>
#include "../Assets.h"
#include "../Game.h"
#include "../UI/Healthbar.h"

namespace gl3 {
    Creature::Creature(Game * game, glm::vec2 position, float zRotation, glm::vec2 scale, float radius,
        glm::vec4 color, Texture2D texture, int health, TYPE type)
    : Entity(position, zRotation, scale, radius, color, texture, health, type){

        /*audio.init();
        audio.setGlobalVolume(0.1f);
        firingSound.load(resolveAssetPath("audio/shot.mp3").string().c_str());
        firingSound.setSingleInstance(true);*/

    }
     float lerp(float a, float b, float f)
    {
        return a + f * (b - a);
    }

    void Creature::update(Game* game, float deltaTime)
    {
        std::time_t elapsedTime = std::time(nullptr);
        const auto witchPosition = game->getWitch()->getPosition();

        //zRotation = glm::degrees(theta_radians) - 90.0f;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_real_distribution<> dist{-1.2f, 500.0f};

        countdown -= deltaTime;
        for(int i = 0; i < 20; i++) {
            if(countdown <= 0) {
                newPosition = dist(rng);
                countdown = positionChangeTime;
            }
        }
        position.y = lerp(position.y, newPosition, deltaTime * speed);


        //std::cout << position.y << std::endl;
        /*
         * Defense
         *
        */

    }

    void Creature::draw()
    {
        Entity::draw();
        for (auto& m: missiles)
        {
            m->draw();
        }
        Healthbar::Instance().backgroundPosition =
            glm::vec2(1280 - Healthbar::Instance().backgroundSize.x - 20, 20.0f);
        Healthbar::Instance().drawHealthbar(health, 0, glm::vec4(1,1,1,1));
    }

}
