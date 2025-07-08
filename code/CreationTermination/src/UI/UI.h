#pragma once
#include "vec2.hpp"
#include "brewEngine/rendering/Texture2D.h"

using gl3::brewEngine::rendering::Texture2D;

class UI {

    public:
    UI();
    void drawUIelements();

    private:
    Texture2D backgroundBarTexture = Texture2D::FromFile("sprites/a.png");
    Texture2D healthQuadTexture = Texture2D::FromFile("sprites/testblock.png");

    const glm::vec2 backgroundBarSize = glm::vec2(100, 40);
    const glm::vec2 healthQuadSize = glm::vec2(10, 10);

    glm::vec2 backgroundPosition = glm::vec2(0, 0);
    glm::vec2 healthQuadPosition = glm::vec2(backgroundPosition.x + 5,
        backgroundPosition.y + backgroundBarSize.y/2 - healthQuadSize.y/2);
};
