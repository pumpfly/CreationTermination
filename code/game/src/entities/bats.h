//
// Created by Lisa B on 29/10/2024.
//

#pragma once

#include "Entity.h"

namespace gl3 {
    class bats : public Entity {
    public:
        explicit bats(glm::vec2 position = glm::vec2(400, 400), float zRotation = 0, glm::vec2 scale = glm::vec2(60, 50),
            float radius = 10, Texture2D texture = Texture2D::FromFile("sprites/bat_Sprites.png"), int health = 1,
            TYPE type = enemy);

        void update(Game *game, float deltaTime) override;
        void draw() override;

    private:

        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;

        glm::vec2 spriteFrameSize = glm::vec2(600, 500);
        float speed = 0.5f;
    };

}


