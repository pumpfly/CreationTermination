#pragma once
#include "Entity.h"
#include "glm/vec3.hpp"

namespace gl3 {
    class Shield : public Entity {
    public:
        explicit Shield(gl3::Game *game, glm::vec3 position, float zRotation, float size);
        void update(gl3::Game *game, float deltaTime) override;
    };
}
