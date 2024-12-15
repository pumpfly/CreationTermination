#include "Entity.h"
#include "../Game.h"
#include "../rendering/SpriteRenderer.h"

namespace gl3 {
    Entity::Entity(Shader shader, Mesh mesh, glm::vec3 position, float zRotation, glm::vec3 scale, glm::vec4 color, Texture2D texture) : position(position),
            zRotation(zRotation),
            scale(scale),
            color(color),
            texture(texture),
            shader(std::move(shader)),
            mesh(std::move(mesh)) {
    }

    void Entity::draw(Game *game) {
        //SpriteRenderer::Instance().DrawSprite(game, texture, position, scale, zRotation, color);
        SpriteRenderer::Instance().DrawSprite(game, texture, glm::vec2(100, 100), glm::vec2(100, 400), zRotation, color);
    }
}
