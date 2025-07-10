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

    //UI
    ////Healthbar
    WitchBackgroundHealthBar = &entityManager.createEntity();
    witchBackgroundHealthBarTransform =
        &WitchBackgroundHealthBar->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(100 * 1.5f, 30 * 1.5f));
    witchBackgroundHealthBarSprite = &WitchBackgroundHealthBar->addComponent<SpriteComponent>("sprites/healthbarBase.png");
    // The background of the healthbar does not have an UIComponent, because it is not interactive or changes

    //Player: Witch
    Witch = &entityManager.createEntity();
    witchPlayer = &Witch->addComponent<PlayerComponent>();
    witchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120), 70);
    witchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png", glm::vec2(680, 415), 4, 10);
    witchHealth = &Witch->addComponent<HealthComponent>(5);
    //Drawing the UI representation of the Players Health
    for (int i = 0; i < witchHealth->health; i++)
    {
        WitchHealthQuad = &entityManager.createEntity();
        witchHealthQuadComponent = &WitchHealthQuad->addComponent<UiComponent>();
        witchHealthQuadTransform = &WitchHealthQuad->addComponent<TransformComponent>(witchBackgroundHealthBarTransform, glm::vec2(15 + 25 * i, 10), 0,
                                                     glm::vec2(11 * 2, 14 * 1.5));
        witchHealthQuadSprite = &WitchHealthQuad->addComponent<SpriteComponent>("sprites/HealthQuad.png");

        healthQuads.push_back(WitchHealthQuad);
    }
    witchCollider = &Witch->addComponent<ColliderComponent>(PLAYER, [this]() {
        //This method will only be called on collision
            // this implementation reduces the health of the Player/Witch
        if (witchCollider->isInvulnerable) { // the invulnerable state serves the prevention of immediate death
            witchCollider->invulnerabilityTimer -= deltaTime;
            if (witchCollider->invulnerabilityTimer <= 0) witchCollider->isInvulnerable = false;
        } else {
            if(witchHealth->health == 0) {
                return;
            }
            --witchHealth->health;
            witchCollider->invulnerabilityTimer = witchCollider->timeBetweenDamage;
            witchCollider->isInvulnerable = true;

            //remove a HealthQuad
            this->entityManager.deleteEntity(this->entityManager.getEntity(healthQuads[witchHealth->health]->guid()));
        }
    });

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    creatureEnemyComponent = &Creature->addComponent<EnemyComponent>(CREATURE);
    creatureTransform = &Creature->addComponent<TransformComponent>(origin, glm::vec2(1100, 600), 0, glm::vec2(600/4, 500/4));
    creatureSprite = &Creature->addComponent<SpriteComponent>("sprites/creature.png", glm::vec2(600, 500), 1, 1);
    creatureHealth = &Creature->addComponent<HealthComponent>(8);
    creatureCollider = &Creature->addComponent<ColliderComponent>(ENEMY, [this](){});

    // Systems that have to be initialized after the creation of Entities
    playerSystem = std::make_unique<PlayerSystem>(*this, Witch);
    enemySystem = std::make_unique<EnemySystem>(*this, Creature, Witch);

}

void CTGame::update(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    currentTime += deltaTime;

    renderSystem->scrollBackgroundSprite(backgroundTransform_Layer1, backgroundComponents_Layer1, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(backgroundTransform_Layer2, backgroundComponents_Layer2, true, true, deltaTime);
    renderSystem->scrollBackgroundSprite(backgroundTransform_Layer3, backgroundComponents_Layer3, true, true, deltaTime);

}
