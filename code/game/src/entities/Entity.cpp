#include "Entity.h"
#include "../Game.h"


namespace gl3 {
    Entity::Entity(glm::vec2 position, float zRotation, glm::vec2 scale, glm::vec4 color, Texture2D texture) : position(position),
            zRotation(zRotation),
            scale(scale),
            color(color),
            texture(texture){
    }

    void Entity::draw(Game *game) {
        SpriteRenderer::Instance().DrawSprite(game, texture, position,
            scale, zRotation, color);
    }
}
