//
// Created by pumf on 14/05/2025.
//

#include "BackgroundManager.h"

#include "rendering/ResourceManager.h"
#include "rendering/SpriteRenderer.h"

    BackgroundManager::BackgroundManager(glm::vec2 position, float zRotation, glm::vec2 scale) : position(position), zRotation(zRotation), scale(scale) {
    }

    void BackgroundManager::update(float deltaTime){
        glm::vec2 forward(0.0f, 0.0f);
        forward.x += cos(glm::radians(zRotation));
        forward.y += sin(glm::radians(zRotation));
        forward = forward * layer3speed * deltaTime;

        position += forward * deltaTime;
    }

    void BackgroundManager::draw(gl3::Game* game) {
        SpriteRenderer::Instance().DrawSprite(game, ResourceManager::GetTexture("forest_3dLayer"),
            glm::vec2(0.0f, 0.0f), glm::vec2(1920/1.5, 1080/1.5), 0.0f, glm::vec4(1, 1, 1, 1));
    }

