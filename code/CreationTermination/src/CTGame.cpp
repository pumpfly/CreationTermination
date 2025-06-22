#include "CTGame.h"

#include "brewEngine/rendering/SpriteRenderer.h"


void CTGame::start() {
    //Player: Witch
    Witch = &entityManager.createEntity();
    WitchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120));
    WitchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4);

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    CreatureTransform = &Creature->addComponent<TransformComponent>(origin, glm::vec2(1100, 600), 0, glm::vec2(600/4, 500/4));
    CreatureSprite = &Creature->addComponent<SpriteComponent>("sprites/creature.png");

    //Background
    Background_Layer1 = &entityManager.createEntity();
    BackgroundSprite_Layer1 = &Background_Layer1->addComponent<SpriteComponent>("background/forest_1stLayer.png");
    BackgroundComponents_Layer1 = &Background_Layer1->addComponent<BackgroundComponent>();

}

void CTGame::update(GLFWwindow *window) {
    draw();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    //Layer1sprite->scrollBackgroundSprite(Layer1Transform, Layer1CopyTransform, 800.0f, true, true, deltaTime);
    //Layer2sprite->scrollBackgroundSprite(Layer2Transform, Layer2CopyTransform, 600.0f, true, true, deltaTime);
    //Layer3sprite->scrollBackgroundSprite(Layer3Transform, Layer3CopyTransform, 400.0f, true, true, deltaTime);
}

void CTGame::draw() {
    //Animating Witch
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSpriteSheet(
            WitchSprite->sprite,
            WitchSprite->animateSpriteSheet(WitchSprite, deltaTime),
            glm::vec4(WitchTransform->localPosition, WitchTransform->localScale),
            WitchTransform->localZRotation,
            glm::vec4(1,1,1,1)
    );

    //Creature
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        CreatureSprite->sprite,
        CreatureTransform->localPosition,
        CreatureTransform->localScale,
        0,
        glm::vec4(1,1,1,1)
        );

    //Background
    //The 3d layer is the furthest away which is why it has to be rendered first
    /*
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        Layer3sprite->sprite,
        Layer3Transform->localPosition,
        Layer3sprite->size,
        0,
        glm::vec4(1,1,1,1));
    //Copy
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        Layer3sprite->sprite,
        Layer3CopyTransform->localPosition,
        Layer3sprite->size,
        0,
        glm::vec4(1,1,1,1));
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        Layer2sprite->sprite,
        Layer2Transform->localPosition,
        Layer2sprite->size,
        0,
        glm::vec4(1,1,1,1));
    //Copy
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        Layer2sprite->sprite,
        Layer2CopyTransform->localPosition,
        Layer2sprite->size,
        0,
        glm::vec4(1,1,1,1));

    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        Layer1sprite->sprite,
        Layer1Transform->localPosition,
        Layer1sprite->size,
        0,
        glm::vec4(1,1,1,1));
    //Copy
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        Layer1sprite->sprite,
        Layer1CopyTransform->localPosition,
        Layer1sprite->size,
        0,
        glm::vec4(1,1,1,1));
        */
}
