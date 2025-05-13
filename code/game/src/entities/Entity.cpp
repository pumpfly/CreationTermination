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

    bool Entity::checkCollision(Entity &other) {
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

    void Entity::handleCollision(std::array<gl3::Entity, 2> collisionPair) {
        gotHit = !gotHit;

        if(gotHit) {
            collisionPair[0].setColor({1.0, 0.0, 0.0, 1.0});
            collisionPair[1].setColor({1.0, 0.0, 0.0, 1.0});

            //Debugging
            std::cout << "got Hit" << std::endl;
            std::cout << collisionPair[0].type << std::endl;
            std::cout << collisionPair[1].type << std::endl;
        }
        if(!gotHit) {
            collisionPair[0].setColor({1, 1, 1, 1.0f});
            collisionPair[1].setColor({1, 1, 1, 1.0f});
        }
    }

    void Entity::draw(Game *game) {
        SpriteRenderer::Instance().DrawSprite(game, texture, position,
            size, zRotation, color);
    }

}
