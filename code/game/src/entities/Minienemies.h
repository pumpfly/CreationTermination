//
// Created by Lisa B on 29/10/2024.
//

#pragma once
#include <soloud_wav.h>

#include "Entity.h"
#include "Missile.h"

namespace gl3 {
    class Minienemies : public Entity {
    public:
        explicit Minienemies(glm::vec3 position = glm::vec3(0, 0, 0), float zRotation = 0,
            float size = 0.01);

        void update(Game *game, float deltaTime) override;

    private:
        float speed = 0.5f;
    };

}


