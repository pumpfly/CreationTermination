//
// Created by Lisa B on 29/10/2024.
//

#pragma once
#include <soloud_wav.h>

#include "Entity.h"
#include "Missiles.h"

namespace gl3 {
    class bats : public Entity {
    public:
        explicit bats(glm::vec2 position = glm::vec2(400, 400), float zRotation = 0, glm::vec2 scale = glm::vec2(20, 20),
            float radius = 10, Texture2D texture = Texture2D::FromFile("sprites/testblock.png"), TYPE type = enemy);

        void update(Game *game, float deltaTime) override;

    private:
        float speed = 0.5f;
    };

}


