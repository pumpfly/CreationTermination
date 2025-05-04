#pragma once

#include "Entity.h"

namespace gl3 {
    class Missiles: public Entity {
    public:
        explicit Missiles(glm::vec2 position, float zRotation, glm::vec2 scale, float radius,
            glm::vec4 color = {0, 0, 0, 1}, Texture2D texture = Texture2D::FromFile("sprites/a.png"),
            TYPE type = witch, int ID = 0);
        void update(Game *game, float deltaTime) override;

        bool gotHit = false;
    private:
        float speed = 400.0f;
    };
}



