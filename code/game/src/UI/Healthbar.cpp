#include "Healthbar.h"

#include "../rendering/SpriteRenderer.h"

void Healthbar::drawHealthbar(int entitiesHealth, float zRotation, glm::vec4 color) {

    //Background
    gl3::SpriteRenderer::Instance().DrawSprite(backgroundTexture, backgroundPosition, backgroundSize, zRotation, color);

    healthQuadPosition = glm::vec2(backgroundPosition.x + 5, backgroundPosition.y + backgroundSize.y/2 - healthQuadSize.y/2);

    //HealthQuads
    for(int i = 0; i < entitiesHealth; i++) {
        gl3::SpriteRenderer::Instance().DrawSprite(healthQuadTexture,
            glm::vec2(healthQuadPosition.x + (healthQuadSize.x + 10)*i, healthQuadPosition.y), healthQuadSize, zRotation, color);
    }
}
