#pragma once

#include "glm/vec3.hpp"
#include "../rendering/Mesh.h"
#include "../rendering/Shader.h"
#include "../rendering/Texture2D.h"

namespace gl3{
    class Game;

    class Entity {
    public:
        Entity(Shader shader,
               Mesh mesh,
               glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
               float zRotation = 0.0f,
               glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f),
               glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
               Texture2D texture = Texture2D::FromFile("sprites/testblock.png"));

        virtual ~Entity() = default;

        virtual void update(Game *game, float deltaTime) {}

        virtual void draw(Game *game);

        [[nodiscard]] const glm::vec3 &getPosition() const {return position; }
        [[nodiscard]] float getZRotation() const { return zRotation; }
        [[nodiscard]] const glm::vec3 &getScale() const { return scale; }
        void setPosition(const glm::vec3 &position) { Entity::position = position; }
        void setZRotation(float zRotation) { Entity::zRotation = zRotation; }
        void setScale(const glm::vec3 &scale) { Entity::scale = scale; }

    protected:
        glm::vec3 position;
        float zRotation;
        glm::vec3 scale;
        glm::vec4 color;
        Texture2D texture;

    private:
        Shader shader;
        Mesh mesh;
    };
}



