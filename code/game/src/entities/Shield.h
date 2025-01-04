#pragma once
#include "Entity.h"
#include "glm/vec3.hpp"

namespace gl3 {
    class Shield : public Entity {
    public:
        explicit Shield(gl3::Game *game, glm::vec2 position, float zRotation,
            glm::vec2 scale, Texture2D texture = Texture2D::FromFile("sprites/a.png"));
        void update(gl3::Game *game, float deltaTime) override;
    };
}
