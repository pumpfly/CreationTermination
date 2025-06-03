//
// Created by pumf on 14/05/2025.
//

#include "BackgroundManager.h"

#include <iostream>

#include "rendering/ResourceManager.h"
#include "rendering/SpriteRenderer.h"

namespace gl3 {
    BackgroundManager::BackgroundManager(std::string layerName, glm::vec2 scale)
    : layerName(layerName), scale(scale) {
    }

    void BackgroundManager::update(float deltaTime){
        glm::vec2 backward(1.0f * deltaTime, 0.0f);

        if(layerName == "firstLayer") {
            layer1_position.x -= backward.x * layer1speed;
            layer1copy_position.x -= backward.x * layer1speed;

            if(layer1_position.x <= -scale.x) {
                layer1_position.x = layer1copy_position.x + scale.x;
            }
            if(layer1copy_position.x <= -scale.x) {
                layer1copy_position.x = layer1_position.x + scale.x;
            }
        }

        if(layerName == "secondLayer") {
            layer2_position.x -= backward.x * layer2speed;
            layer2copy_position.x -= backward.x * layer2speed;
            if(layer2_position.x <= -scale.x) {
                layer2_position.x = layer2copy_position.x + scale.x;
            }
            if(layer2copy_position.x <= -scale.x) {
                layer2copy_position.x = layer2_position.x + scale.x;
            }
        }
        if(layerName == "thirdLayer") {
            layer3_position.x -= backward.x * layer3speed;
            layer3copy_position.x -= backward.x * layer3speed;

            if(layer3_position.x <= -scale.x) {
                layer3_position.x = layer3copy_position.x + scale.x;
            }
            if(layer3copy_position.x <= -scale.x) {
                layer3copy_position.x = layer3_position.x + scale.x;
            }
        }

    }

    void BackgroundManager::draw() {
        if(layerName == "firstLayer") {
            SpriteRenderer::Instance().DrawSprite(ResourceManager::GetTexture(layerName),
            layer1_position, scale, 0.0f, glm::vec4(1, 1, 1, 1));
            SpriteRenderer::Instance().DrawSprite(ResourceManager::GetTexture(layerName),
                layer1copy_position, scale, 0.0f, glm::vec4(1, 1, 1, 1));
        }
        if(layerName == "secondLayer") {
            SpriteRenderer::Instance().DrawSprite(ResourceManager::GetTexture(layerName),
            layer2_position, scale, 0.0f, glm::vec4(1, 1, 1, 1));
            SpriteRenderer::Instance().DrawSprite(ResourceManager::GetTexture(layerName),
                layer2copy_position, scale, 0.0f, glm::vec4(1, 1, 1, 1));
        }
        if(layerName == "thirdLayer") {
            SpriteRenderer::Instance().DrawSprite(ResourceManager::GetTexture(layerName),
            layer3_position, scale, 0.0f, glm::vec4(1, 1, 1, 1));
            SpriteRenderer::Instance().DrawSprite(ResourceManager::GetTexture(layerName),
                layer3copy_position, scale, 0.0f, glm::vec4(1, 1, 1, 1));
        }
    }
};