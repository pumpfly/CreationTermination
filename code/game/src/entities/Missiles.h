#pragma once

#include "Entity.h"

namespace gl3 {
    class Missiles: public Entity {
    public:
        explicit Missiles(glm::vec2 position, float zRotation, glm::vec2 size, float radius,
            glm::vec4 color = {0, 0, 0, 1}, Texture2D texture = Texture2D::FromFile("sprites/a.png"), int health = 1,
            TYPE type = witch);
        void update(Game *game, float deltaTime) override;

        bool gotHit = false;

    private:
        int MinX = static_cast<int>(position.x);
        int MinY = static_cast<int>(position.y);
        int MaxX = static_cast<int>(position.x) + static_cast<int>(size.x);
        int MaxY = static_cast<int>(position.y) + static_cast<int>(size.y);

        float speed = 400.0f;
        bool hitTarget = false;
    };
}



