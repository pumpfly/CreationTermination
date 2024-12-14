#pragma once

#include "Entity.h"

namespace gl3 {
    class Missile: public Entity {
    public:
        explicit Missile(Game *game, glm::vec3 position, float zRotation, float size);
        void update(Game *game, float deltaTime) override;
    private:
        float speed = 5.0f;
    };
}



