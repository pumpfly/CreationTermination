#include "CTGame.h"

#include "brewEngine/rendering/SpriteRenderer.h"


void CTGame::start() {
    //Systems
    renderSystem = std::make_unique<RenderingSystem>(*this);
    missileSystem = std::make_unique<MissileSystem>(*this);
    collisionSystem = std::make_unique<CollisionSystem>(*this);

    //Background
    Background_Layer3 = &entityManager.createEntity();
    backgroundTransform_Layer3 = &Background_Layer3->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer3 = &Background_Layer3->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 400.0f);
    backgroundSprite_Layer3 = &Background_Layer3->addComponent<SpriteComponent>("background/forest_3dLayer.png");

    Background_Layer2 = &entityManager.createEntity();
    backgroundTransform_Layer2 = &Background_Layer2->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer2 = &Background_Layer2->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 600.0f);
    backgroundSprite_Layer2 = &Background_Layer2->addComponent<SpriteComponent>("background/forest_2dLayer.png");

    Background_Layer1 = &entityManager.createEntity();
    backgroundTransform_Layer1 = &Background_Layer1->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer1 = &Background_Layer1->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 800.0f);
    backgroundSprite_Layer1 = &Background_Layer1->addComponent<SpriteComponent>("background/forest_1stLayer.png");

    //Player: Witch
    Witch = &entityManager.createEntity();
    witchPlayer = &Witch->addComponent<PlayerComponent>();
    witchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120));
    witchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4, 10);
    witchHealth = &Witch->addComponent<HealthComponent>(5);
    witchCollider = &Witch->addComponent<ColliderComponent>(PLAYER, [this]() {
        witchHealth->health--;
    });

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    creatureEnemyComponent = &Creature->addComponent<EnemyComponent>(CREATURE);
    creatureTransform = &Creature->addComponent<TransformComponent>(origin, glm::vec2(1100, 600), 0, glm::vec2(600/4, 500/4));
    creatureSprite = &Creature->addComponent<SpriteComponent>("sprites/creature.png", glm::vec2(600, 500), 1, 1);
    creatureHealth = &Creature->addComponent<HealthComponent>(8);
    creatureCollider = &Creature->addComponent<ColliderComponent>(ENEMY, [this](){});

    playerSystem = std::make_unique<PlayerSystem>(*this, Witch);
    enemySystem = std::make_unique<EnemySystem>(*this, Creature, Witch);

}

void CTGame::update(GLFWwindow *window) {
    draw();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    std::cout << witchHealth->health << std::endl;

    currentTime += deltaTime;

    renderSystem->scrollBackgroundSprite(backgroundTransform_Layer1, backgroundComponents_Layer1, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(backgroundTransform_Layer2, backgroundComponents_Layer2, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(backgroundTransform_Layer3, backgroundComponents_Layer3, true, true, deltaTime);

}

void CTGame::draw() {
}
