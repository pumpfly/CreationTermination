//
// Created by pumf on 24/10/2024.
//
#pragma once
#include "Entity.h"
#include "Missiles.h"
#include <soloud.h>
#include <soloud_wav.h>
#include <vector>

#include "Shield.h"

namespace gl3 {
    class Witch : public Entity{
    public:
        explicit Witch(Game* game, glm::vec2 position = glm::vec2(100.0f, 100.0f),
             float zRotation = 0.0f, glm::vec2 size = glm::vec2(100, 100),
             float radius = 50, glm::vec4 color = glm::vec4(1, 1, 1, 1.0f),
             Texture2D texture = Texture2D::FromFile("sprites/witch.png"),
             TYPE type = witch);

        void update(Game *game, float deltaTime) override;
        void draw() override;

    private:
        float translationSpeed = 1.0f;
        float rotationSpeed = 120.0f;

        bool charging = false;
        bool onlySingleMissile = false;
        float missileTempSize = 1.0f;

        //Missiles
        const float timeBetweenShots = 0.1;
        float countdownUntilNextShot = timeBetweenShots;
        std::vector<std::unique_ptr<Missiles>> missiles;
        std::vector<std::unique_ptr<Missiles>> bigMissiles;
        std::vector<std::unique_ptr<Missiles>> waveMissiles;

        //Shield
        std::unique_ptr<Shield> shield;

        SoLoud::Soloud audio;
        SoLoud::Wav firingSound;
    };
}



