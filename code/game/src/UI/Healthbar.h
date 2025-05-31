#pragma once
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

class Texture2D;

class Healthbar {
public:
    static Healthbar &Instance() {
        static Healthbar instance = Healthbar();
        return instance;
    }

    void drawHealthbar(int entitiesHealth, Texture2D texture, glm::vec2 position,
        float zRotation, glm::vec4 color);

private:
    Healthbar() = default;
    ~Healthbar() = default;

    glm::vec2 backgroundPosition = glm::vec2(0, 0); //default values
    glm::vec2 healthQuadPosition = glm::vec2(backgroundPosition.x + 10, backgroundPosition.y + 10);

    const glm::vec2 backgroundSize = glm::vec2(40, 80);
    const glm::vec2 healthQuadSize = glm::vec2(20, 20);
};
