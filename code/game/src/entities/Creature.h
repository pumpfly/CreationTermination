//
// Created by Lisa B on 29/10/2024.
//

#pragma once
#include <soloud_wav.h>

#include "Entity.h"
#include "Missile.h"

namespace gl3 {
    class Creature : public Entity {
    public:
        explicit Creature(Game* game, glm::vec2 position = glm::vec2(100, 100), float zRotation = 0,
            glm::vec2 scale = glm::vec2(100, 100), Texture2D texture = Texture2D::FromFile("sprites/a.png"));

        void update(Game *game, float deltaTime) override;
        void draw(Game *game) override;

    private:
        float speed = 1.5f;

        const float timeBetweenShots = 0.1;
        float countdownUntilNextShot = timeBetweenShots;
        std::vector<std::unique_ptr<Missile>> missiles;

        SoLoud::Soloud audio;
        SoLoud::Wav firingSound;
    };

}


