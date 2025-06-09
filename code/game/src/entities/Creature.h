//
// Created by Lisa B on 29/10/2024.
//

#pragma once
#include <memory>
#include <random>

#include <soloud_wav.h>

#include "Entity.h"
#include "Missiles.h"

namespace gl3 {
    class Creature : public Entity {
    public:
        explicit Creature(Game* game, glm::vec2 position = glm::vec2(1100, 600), float zRotation = 0,
            glm::vec2 scale = glm::vec2(600/4, 500/4), float radius = 50, glm::vec4 color = glm::vec4(1, 1, 1, 1.0f),
            Texture2D texture = Texture2D::FromFile("sprites/creature.png"), int health = 5, TYPE type = enemy);

        void update(Game *game, float deltaTime) override;
        void draw() override;


    private:
        float speed = 1.5f;

        float positionChangeTime = 1.0f;
        float countdown = positionChangeTime;
        float newPosition = 500;

        const float timeBetweenShots = 0.1;
        float countdownUntilNextShot = timeBetweenShots;
        std::vector<std::unique_ptr<Missiles>> missiles;

        SoLoud::Soloud audio;
        SoLoud::Wav firingSound;
    };

}


