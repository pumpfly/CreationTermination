#pragma once

#include "Entity.h"

namespace gl3 {
    class Missile: public Entity {
    public:
        explicit Missile(Game *game, glm::vec2 position, float zRotation, glm::vec2 scale, Texture2D texture = Texture2D::FromFile("sprites/a.png"));
        void update(Game *game, float deltaTime) override;
    private:
        float speed = 5.0f;
    };
}



