#include "CTGame.h"


void CTGame::start() {
    animationSystem = std::make_unique<AnimationSystem>(*this);

    //Player: Witch
    Witch = &entityManager.createEntity();
    WitchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120));
    WitchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4);

    //Main Enemy: Creature
    Creature = &entityManager.createEntity().addComponent<TransformComponent>(origin, glm::vec2(1100, 600));
}

void CTGame::update(GLFWwindow *window) {
    draw();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void CTGame::draw() {
        //Animating Witch
        gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSpriteSheet(
                WitchSprite->sprite,
                animationSystem->animateSpriteSheet(WitchSprite, deltaTime),
                glm::vec4(WitchTransform->localPosition, WitchTransform->localScale),
                WitchTransform->localZRotation,
                glm::vec4(1,1,1,1)
        );
}
