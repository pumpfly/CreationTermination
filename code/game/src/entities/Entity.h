#pragma once

#include <array>

#include "glm/vec3.hpp"
#include "../rendering/Texture2D.h"
#include "../rendering/SpriteRenderer.h"

class SpatialGridManager;

namespace gl3{
    class Game;

    enum TYPE {
        enemy,
        witch,
        missile
    };

    class Entity {
    public:
        Entity(glm::vec2 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float zRotation = 0.0f,
               glm::vec2 scale = glm::vec3(1.0f, 1.0f, 1.0f),
               float radius = 1.0f,
               glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
               Texture2D texture = Texture2D::FromFile("sprites/a.png"),
               TYPE type = witch);

        virtual ~Entity() = default;

        virtual void update(Game *game, float deltaTime) {};

        bool hasCollisionWith(Entity& other);
        void handleCollision(const std::vector<size_t>& collisionPair);
        void collisionEffect();

        virtual void draw(Game *game);

        [[nodiscard]] const glm::vec2 &getPosition() const {return position; }
        [[nodiscard]] float getZRotation() const { return zRotation; }
        [[nodiscard]] const glm::vec2 &getSize() const { return size; }
        [[nodiscard]] const float &getRadius() const { return radius; }
        [[nodiscard]] const TYPE &getType() const { return type; }
        [[nodiscard]] const glm::vec4 &getColor() const { return color; }
        void setPosition(const glm::vec2 &position) { Entity::position = position; }
        void setZRotation(float zRotation) { Entity::zRotation = zRotation; }
        void setSize(const glm::vec2 &scale) { Entity::size = scale; }
        void setRadius(const float &radius) { Entity::radius = radius; }
        void setColor(const glm::vec4 &color) { Entity::color = color; }

    private:
        bool gotHit = false;

    protected:
        glm::vec2 position;
        float zRotation;
        glm::vec2 size;
        float radius;
        glm::vec4 color;
        Texture2D texture;
        TYPE type;
    };
}



