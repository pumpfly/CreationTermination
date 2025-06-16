#pragma once
#include <iostream>

#include "brewEngine/rendering/SpriteRenderer.h"
#include "brewEngine/rendering/SpriteComponent.h"
#include "Systems/AnimationSystem.h"
#include "Systems/RenderSystem.h"

using gl3::brewEngine::Game;
using gl3::brewEngine::ecs::Entity;
using gl3::brewEngine::sceneGraph::TransformComponent;
using gl3::brewEngine::rendering::SpriteComponent;

class CTGame : public Game {
public:
    CTGame(int width, int height, const std::string &title) : Game(width, height, title) {
    }

private:
    void start() override {
        renderSystem = std::make_unique<RenderSystem>(*this);
        animationSystem = std::make_unique<AnimationSystem>(*this);

        //Player: Witch
        Witch = &entityManager.createEntity();
        WitchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(0, 0));
        WitchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4);

        //Main Enemy: Creature
        Creature = &entityManager.createEntity().addComponent<TransformComponent>(origin, glm::vec2(1100, 600));
    }

    void update(GLFWwindow *window) override {
        draw();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
    }

    void draw() override {
        gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
            WitchSprite->sprite,
            WitchTransform->localPosition,
            WitchTransform->localScale,
            WitchTransform->localZRotation,
            glm::vec4(1, 0, 0, 1));

        //Player:
        /*gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSpriteSheet(
        WitchSprite->sprite,
        animationSystem->animateSpriteSheet(*WitchSprite, deltaTime),
        glm::vec4(WitchTransform->localPosition, WitchTransform->localScale),
        WitchTransform->localZRotation,
        glm::vec4(1,1,1,1));*/

    }

    std::unique_ptr<RenderSystem> renderSystem;
    std::unique_ptr<AnimationSystem> animationSystem;
    Entity *Witch = nullptr;
    TransformComponent *WitchTransform = nullptr;
    SpriteComponent *WitchSprite = nullptr;
    TransformComponent *Creature = nullptr;
    std::vector<TransformComponent> bats;

};
