#include "Entity.h"

#include <iostream>

#include "../Game.h"


namespace gl3 {
    Entity::Entity(glm::vec2 position, float zRotation, glm::vec2 scale, float radius, glm::vec4 color,
        Texture2D texture, TYPE type):
            position(position),
            zRotation(zRotation),
            size(scale),
            radius(radius),
            color(color),
            texture(texture),
            type(type){
    }

    bool Entity::hasCollisionWith(Entity& other)
    {
        glm::vec2 center1(this->getPosition() + this->getRadius());
        glm::vec2 center2(other.getPosition() + other.getRadius());

        glm::vec2 difference = center2 - center1;

        if(glm::length(difference) < other.getRadius() + this->getRadius()) {
            if(this->type != other.type) {
                return true;
            }
        }
        return false;
    }

    void Entity::handleCollision(const std::vector<size_t>& collisionPair) {
        gotHit = !gotHit;
        //TODO:
        if(gotHit) {

        }
        if(!gotHit) {

        }
    }

    void Entity::draw() {
        SpriteRenderer::Instance().DrawSprite(texture, position,
            size, zRotation, color);
    }
}
