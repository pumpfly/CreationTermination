#include "CTGame.h"

#include "brewEngine/rendering/SpriteRenderer.h"


void CTGame::start() {
    //Systems
    renderSystem = std::make_unique<RenderingSystem>(*this);
    missileSystem = std::make_unique<MissileSystem>(*this);

    //Background
    Background_Layer3 = &entityManager.createEntity();
    BackgroundTransform_Layer3 = &Background_Layer3->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    BackgroundComponents_Layer3 = &Background_Layer3->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 400.0f);
    BackgroundSprite_Layer3 = &Background_Layer3->addComponent<SpriteComponent>("background/forest_3dLayer.png");

    Background_Layer2 = &entityManager.createEntity();
    BackgroundTransform_Layer2 = &Background_Layer2->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    BackgroundComponents_Layer2 = &Background_Layer2->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 600.0f);
    BackgroundSprite_Layer2 = &Background_Layer2->addComponent<SpriteComponent>("background/forest_2dLayer.png");

    Background_Layer1 = &entityManager.createEntity();
    BackgroundTransform_Layer1 = &Background_Layer1->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    BackgroundComponents_Layer1 = &Background_Layer1->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 800.0f);
    BackgroundSprite_Layer1 = &Background_Layer1->addComponent<SpriteComponent>("background/forest_1stLayer.png");

    //Player: Witch
    Witch = &entityManager.createEntity();
    WitchPlayer = &Witch->addComponent<PlayerComponent>();
    WitchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120));
    WitchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4, 10);

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    CreatureEnemyComponent = &Creature->addComponent<EnemyComponent>(CREATURE);
    CreatureTransform = &Creature->addComponent<TransformComponent>(origin, glm::vec2(1100, 600), 0, glm::vec2(600/4, 500/4));
    CreatureSprite = &Creature->addComponent<SpriteComponent>("sprites/creature.png", glm::vec2(600, 500), 1, 1);

    playerSystem = std::make_unique<PlayerSystem>(*this, Witch);
    enemySystem = std::make_unique<EnemySystem>(*this, Creature, Witch);

}

void CTGame::update(GLFWwindow *window) {
    draw();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    currentTime += deltaTime;

    renderSystem->scrollBackgroundSprite(BackgroundTransform_Layer1, BackgroundComponents_Layer1, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(BackgroundTransform_Layer2, BackgroundComponents_Layer2, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(BackgroundTransform_Layer3, BackgroundComponents_Layer3, true, true, deltaTime);

}

void CTGame::draw() {
}
