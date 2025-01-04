#include "Entity.h"
#include "../Game.h"


namespace gl3 {
    Entity::Entity(Shader shader, Mesh mesh, glm::vec2 position, float zRotation, glm::vec2 scale, glm::vec4 color, Texture2D texture) : position(position),
            zRotation(zRotation),
            scale(scale),
            color(color),
            shader(std::move(shader)),
            mesh(std::move(mesh)),
            texture(texture){
    }

    void Entity::draw(Game *game) {
        SpriteRenderer::Instance().DrawSprite(game, texture, glm::vec2(200, 100),
            glm::vec2(100, 100), zRotation, color);
    }
}
