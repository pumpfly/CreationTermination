//
// Created by pumf on 24/10/2024.
//
#pragma once
#include "Entity.h"
#include "Missile.h"
#include <soloud.h>
#include <soloud_wav.h>

#include "Shield.h"

namespace gl3 {
    class Witch : public Entity{
    public:
        explicit Witch(Game* game, glm::vec2 position = glm::vec2(100.0f, 100.0f),
             float zRotation = 0.0f,
             glm::vec2 scale = glm::vec2(100, 100), glm::vec4 color = glm::vec4(1, 1, 1, 1.0f),
             Texture2D texture = Texture2D::FromFile("sprites/witch.png"));

        void update(Game *game, float deltaTime) override;
        void draw(Game *game) override;

    private:
        float translationSpeed = 1.0f;
        float rotationSpeed = 120.0f;

        bool charging = false;
        bool onlySingleMissile = false;
        float missileTempSize = 0.05f;

        //Missiles
        const float timeBetweenShots = 0.1;
        float countdownUntilNextShot = timeBetweenShots;
        std::vector<std::unique_ptr<Missile>> missiles;
        std::vector<std::unique_ptr<Missile>> bigMissiles;
        std::vector<std::unique_ptr<Missile>> waveMissiles;

        //Shield
        std::unique_ptr<Shield> shield;

        SoLoud::Soloud audio;
        SoLoud::Wav firingSound;
    };
}



