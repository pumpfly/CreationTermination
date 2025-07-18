#include "CTGame.h"

#include "brewEngine/rendering/SpriteRenderer.h"
#include "brewEngine/Assets.h"


void CTGame::start() {
    renderSystem = std::make_unique<RenderingSystem>(*this);
    introSystem = std::make_unique<IntroSystem>(*this);

    //Background
    Background_Layer3 = &entityManager.createEntity();
    backgroundTransform_Layer3 = &Background_Layer3->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer3 = &Background_Layer3->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 400.0f, true, true);
    backgroundSprite_Layer3 = &Background_Layer3->addComponent<SpriteComponent>("background/forest_3dLayer.png");

    Background_Layer2 = &entityManager.createEntity();
    backgroundTransform_Layer2 = &Background_Layer2->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer2 = &Background_Layer2->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 600.0f, true, true);
    backgroundSprite_Layer2 = &Background_Layer2->addComponent<SpriteComponent>("background/forest_2dLayer.png");

    Background_Layer1 = &entityManager.createEntity();
    backgroundTransform_Layer1 = &Background_Layer1->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer1 = &Background_Layer1->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 800.0f, true, true);
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
    witchSprite = &Witch->addComponent<SpriteComponent>("sprites/witch_idleSprites.png",
        glm::vec2(680, 415),
        4,
        10,
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    witchHealth = &Witch->addComponent<HealthComponent>(5);
    //Drawing the UI representation of the Players Health
    for (int i = 0; i < witchHealth->health; i++)
    {
        WitchHealthQuad = &entityManager.createEntity();
        witchHealthQuadComponent = &WitchHealthQuad->addComponent<UiComponent>();
        witchHealthQuadTransform = &WitchHealthQuad->addComponent<TransformComponent>(
            witchBackgroundHealthBarTransform,
            glm::vec2(15 + 25 * i, 10),
            0,
            glm::vec2(11 * 2, 14 * 1.5));
        witchHealthQuadSprite = &WitchHealthQuad->addComponent<SpriteComponent>("sprites/HealthQuad.png");

        healthQuads.push_back(WitchHealthQuad);
    }
    witchCollider = &Witch->addComponent<ColliderComponent>(PLAYER, [this] {
        //This method will only be called on collision
            // this implementation reduces the health of the Player/Witch
        ColliderComponent* collider = &Witch->getComponent<ColliderComponent>();
        if (collider->isInvulnerable) { // the invulnerable state serves the prevention of immediate death
            while(collider->invulnerabilityTimer > 0) {
                collider->invulnerabilityTimer -= deltaTime;
            }
            collider->isInvulnerable = false;
        } else {
            if(witchHealth->health == 0) {
                return;
            }
            --witchHealth->health;
            collider->invulnerabilityTimer = collider->timeBetweenDamage;
            collider->isInvulnerable = true;

            //remove a HealthQuad
            this->entityManager.deleteEntity(this->entityManager.getEntity(healthQuads[witchHealth->health]->guid()));
        }
    });

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    creatureEnemyComponent = &Creature->addComponent<EnemyComponent>(CREATURE);
    creatureTransform = &Creature->addComponent<TransformComponent>(origin, glm::vec2(1100, 600), 0, glm::vec2(600/4, 500/4), 200);
    creatureSprite = &Creature->addComponent<SpriteComponent>("sprites/creature.png", glm::vec2(600, 500), 1, 1, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    creatureHealth = &Creature->addComponent<HealthComponent>(8);
    creatureCollider = &Creature->addComponent<ColliderComponent>(ENEMY, [this]() {
        //This method will only be called on collision
            // this implementation reduces the health of the Player/Witch
        if (creatureCollider->isInvulnerable) { // the invulnerable state serves the prevention of immediate death
            creatureCollider->invulnerabilityTimer -= deltaTime;
            if (creatureCollider->invulnerabilityTimer <= 0) creatureCollider->isInvulnerable = false;
        } else {
            if(this->currScore == maxScore) {
                return;
            }
            this->currScore = this->currScore + 150;
            creatureCollider->invulnerabilityTimer = creatureCollider->timeBetweenDamage;
            creatureCollider->isInvulnerable = true;
        }
    });
    // Loading a bigger font
    std::string path = gl3::brewEngine::resolveAssetPath("fonts/inter.ttf").string();
    bigfont = lf_load_font(path.c_str(), 30);

    //if(this->getGameState() != GAME_ACTIVE) return;
    collisionSystem = std::make_unique<CollisionSystem>(*this);
    missileSystem = std::make_unique<MissileSystem>(*this);
    enemySystem = std::make_unique<EnemySystem>(*this, Creature);
    playerSystem = std::make_unique<PlayerSystem>(*this, Witch);
}

void CTGame::update(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        lf_terminate();
        glfwSetWindowShouldClose(window, true);
    }
    if(this->getGameState() != GAME_ACTIVE) return;
    //UI
    // Starting leif context
    lf_begin();

    ////Score display
    std::string scoreText = "SCORE: " + std::to_string(this->currScore);
    {
        // Setting big font
        lf_push_font(&bigfont);
        LfUIElementProps scoreDisplay = lf_get_theme().text_props;
        scoreDisplay.text_color = LF_BLACK;
        // Center the text horizontally
        lf_set_ptr_x_absolute((this->getContext().getWindowWidth() - lf_text_dimension(scoreText.c_str()).x) / 2.0f);
        // Push the style props
        lf_push_style_props(scoreDisplay);

        // Render the text
        lf_text(scoreText.c_str());

        // Pop the style props
        lf_pop_style_props();

        // Unsetting big font
        lf_pop_font();

    }
}
