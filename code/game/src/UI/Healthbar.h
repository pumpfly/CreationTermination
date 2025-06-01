#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include "../rendering/Texture2D.h"

class Healthbar {
public:
    static Healthbar &Instance() {
        static Healthbar instance = Healthbar();
        return instance;
    }

    void drawHealthbar(int entitiesHealth, float zRotation, glm::vec4 color);

    Texture2D backgroundTexture = Texture2D::FromFile("sprites/a.png");
    Texture2D healthQuadTexture = Texture2D::FromFile("sprites/testblock.png");
    glm::vec2 backgroundPosition = glm::vec2(0, 0);
    const glm::vec2 backgroundSize = glm::vec2(100, 40);

private:
    Healthbar() = default;
    ~Healthbar() = default;

    glm::vec2 healthQuadPosition = glm::vec2(0, 0);

    const glm::vec2 healthQuadSize = glm::vec2(10, 10);
};
