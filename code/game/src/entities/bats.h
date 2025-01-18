//
// Created by Lisa B on 29/10/2024.
//

#pragma once
#include <soloud_wav.h>

#include "Entity.h"
#include "Missile.h"

namespace gl3 {
    class bats : public Entity {
    public:
        explicit bats(glm::vec2 position = glm::vec2(300, 300), float zRotation = 0,
            glm::vec2 scale = glm::vec2(20, 20), Texture2D texture = Texture2D::FromFile("sprites/testblock.png"));

        void update(Game *game, float deltaTime) override;

    private:
        float speed = 0.5f;
    };

}


