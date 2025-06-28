#include "CTGame.h"

#include "brewEngine/rendering/SpriteRenderer.h"


void CTGame::start() {
    //Systems
    renderSystem = std::make_unique<RenderingSystem>(*this);
    playerSystem = std::make_unique<PlayerSystem>(*this);
    missileSystem = std::make_unique<MissileSystem>(*this);

    //Player: Witch
    Witch = &entityManager.createEntity();
    WitchPlayer = &Witch->addComponent<PlayerComponent>();
    WitchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120));
    WitchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4);

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    CreatureEnemyComponent = &Creature->addComponent<EnemyComponent>(Creature->guid());
    CreatureTransform = &Creature->addComponent<TransformComponent>(origin, glm::vec2(1100, 600), 0, glm::vec2(600/4, 500/4));
    CreatureSprite = &Creature->addComponent<SpriteComponent>("sprites/creature.png");

    //Background
    Background_Layer1 = &entityManager.createEntity();
    BackgroundComponents_Layer1 = &Background_Layer1->addComponent<BackgroundComponent>(glm::vec2(0, 0), glm::vec2(1280*3, 0), 800.0f, glm::vec2(1280*3, 720));
    BackgroundSprite_Layer1 = &Background_Layer1->addComponent<SpriteComponent>("background/forest_1stLayer.png");

    Background_Layer2 = &entityManager.createEntity();
    BackgroundComponents_Layer2 = &Background_Layer2->addComponent<BackgroundComponent>(glm::vec2(0, 0), glm::vec2(1280*3, 0), 600.0f, glm::vec2(1280*3, 720));
    BackgroundSprite_Layer2 = &Background_Layer2->addComponent<SpriteComponent>("background/forest_2dLayer.png");

    Background_Layer3 = &entityManager.createEntity();
    BackgroundComponents_Layer3 = &Background_Layer3->addComponent<BackgroundComponent>(glm::vec2(0, 0), glm::vec2(1280*3, 0), 400.0f, glm::vec2(1280*3, 720));
    BackgroundSprite_Layer3 = &Background_Layer3->addComponent<SpriteComponent>("background/forest_3dLayer.png");

}

void CTGame::update(GLFWwindow *window) {
    draw();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    renderSystem->scrollBackgroundSprite(BackgroundComponents_Layer1, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(BackgroundComponents_Layer2, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(BackgroundComponents_Layer3, true, true, deltaTime);
}

void CTGame::draw() {
    //Background
    //The 3d layer is the furthest away which is why it has to be rendered first
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        BackgroundSprite_Layer3->sprite,
        BackgroundComponents_Layer3->position,
        BackgroundComponents_Layer3->scale,
        0,
        glm::vec4(1,1,1,1));
    //Copy
     gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
         BackgroundSprite_Layer3->sprite,
         BackgroundComponents_Layer3->copyPosition,
         BackgroundComponents_Layer3->scale,
         0,
         glm::vec4(1,1,1,1));
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        BackgroundSprite_Layer2->sprite,
        BackgroundComponents_Layer2->position,
        BackgroundComponents_Layer2->scale,
        0,
        glm::vec4(1,1,1,1));
    //Copy
     gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
         BackgroundSprite_Layer2->sprite,
         BackgroundComponents_Layer2->copyPosition,
         BackgroundComponents_Layer2->scale,
         0,
         glm::vec4(1,1,1,1));
    gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
        BackgroundSprite_Layer1->sprite,
        BackgroundComponents_Layer1->position,
        BackgroundComponents_Layer1->scale,
        0,
        glm::vec4(1,1,1,1));
    //Copy
     gl3::brewEngine::rendering::SpriteRenderer::Instance().DrawSprite(
         BackgroundSprite_Layer1->sprite,
         BackgroundComponents_Layer1->copyPosition,
         BackgroundComponents_Layer1->scale,
         0,
         glm::vec4(1,1,1,1));

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
}
