//
// Created by Lisa B on 29/10/2024.
//

#pragma once
#include <soloud_wav.h>

#include "Entity.h"
#include "Missile.h"

namespace gl3 {
    class Enemy : public Entity {
    public:
        explicit Enemy(Game* game, glm::vec3 position = glm::vec3(0, 0, 0), float zRotation = 0, float size = 3.0);

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


