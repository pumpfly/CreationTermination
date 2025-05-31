//
// Created by pumf on 29/05/2025.
//

#include "Healthbar.h"

#include "../rendering/SpriteRenderer.h"

void Healthbar::drawHealthbar(int entitiesHealth, Texture2D texture, glm::vec2 position,
    float zRotation, glm::vec4 color) {

    //Background
    gl3::SpriteRenderer::Instance().DrawSprite(texture, position, backgroundSize, zRotation, color);

    //HealthQuads
    for(int i = 0; i < entitiesHealth; i++) {
        gl3::SpriteRenderer::Instance().DrawSprite(texture, healthQuadPosition, backgroundSize, zRotation, color);
        healthQuadPosition.x += healthQuadSize.x + 5;
    }
}
