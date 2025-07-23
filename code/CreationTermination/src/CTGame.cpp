#include "CTGame.h"

#include <iostream>

#include "brewEngine/rendering/SpriteRenderer.h"
#include "brewEngine/Assets.h"
#include "Systems/ShieldSystem.h"

extern "C" {
#include <leif.h>
}

void CTGame::start() {
    //Loading Textures
    witchTexture = Texture2D::FromFile("sprites/witch_idleSprites.png");
    creatureTexture = Texture2D::FromFile("sprites/creature.png");
    backgroundTexture_Layer1 = Texture2D::FromFile("background/forest_1stLayer.png");
    backgroundTexture_Layer2 = Texture2D::FromFile("background/forest_2dLayer.png");
    backgroundTexture_Layer3 = Texture2D::FromFile("background/forest_3dLayer.png");
    endSceneTexture_Lost = Texture2D::FromFile("sprites/gameOverScreen_Lost.png");
    endSceneTexture_Won = Texture2D::FromFile("sprites/gameOverScreen_Won.png");;
    witchBackgroundHealthbarTexture = Texture2D::FromFile("sprites/healthbarBase.png");
    witchHealthQuadTexture = Texture2D::FromFile("sprites/HealthQuad.png");
    shieldCoolDownBarTexture = Texture2D::FromFile("sprites/ShieldBase.png");
    shieldQuadTexture = Texture2D::FromFile("sprites/ShieldQuad.png");

    renderSystem = std::make_unique<RenderingSystem>(*this);

    //Background
    Background_Layer3 = &entityManager.createEntity();
    backgroundTransform_Layer3 = &Background_Layer3->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer3 = &Background_Layer3->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 400.0f, true, true);
    backgroundSprite_Layer3 = &Background_Layer3->addComponent<SpriteComponent>(backgroundTexture_Layer3, glm::vec4(1,1,1,1));

    Background_Layer2 = &entityManager.createEntity();
    backgroundTransform_Layer2 = &Background_Layer2->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer2 = &Background_Layer2->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 600.0f, true, true);
    backgroundSprite_Layer2 = &Background_Layer2->addComponent<SpriteComponent>(backgroundTexture_Layer2, glm::vec4(1,1,1,1));

    Background_Layer1 = &entityManager.createEntity();
    backgroundTransform_Layer1 = &Background_Layer1->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(1280*3, 720));
    backgroundComponents_Layer1 = &Background_Layer1->addComponent<BackgroundComponent>(glm::vec2(1280*3, 0), 800.0f, true, true);
    backgroundSprite_Layer1 = &Background_Layer1->addComponent<SpriteComponent>(backgroundTexture_Layer1, glm::vec4(1,1,1,1));

    //Player: Witch
    Witch = &entityManager.createEntity();
    witchPlayer = &Witch->addComponent<PlayerComponent>();
    witchTransform = &Witch->addComponent<TransformComponent>(origin, glm::vec2(100, 100), 0, glm::vec2(120*1.6, 120), 60);
    witchSprite = &Witch->addComponent<SpriteComponent>(witchTexture,
        glm::vec2(witchTexture.getImageWidth()/4, witchTexture.getImageHeight()),
        4,
        10,
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    witchHealth = &Witch->addComponent<HealthComponent>(7);
    witchCollider = &Witch->addComponent<ColliderComponent>(PLAYER, 1.0f, [this] {
        //This method will only be called on collision
            // this implementation reduces the health of the Player/Witch

        // getting a new collider pointer to prevent having to stash it inside the lambda function
        ColliderComponent* collider = &Witch->getComponent<ColliderComponent>();

        // the invulnerable state serves the prevention of immediate death
        if (collider->isInvulnerable || collider->isShielded) return;

        --witchHealth->health;
        collider->invulnerabilityTimer = collider->timeBetweenDamage;
        collider->isInvulnerable = true;

        if(witchHealth->health == 0) {
            this->setGameState(gl3::brewEngine::GAME_OVER);
            EndScene = &this->entityManager.createEntity();
            endSceneTransform = &EndScene->addComponent<TransformComponent>(origin,
                glm::vec2(0, 0),
                0,
                glm::vec2(this->getWindowWidth(), this->getWindowHeight()));
            gameOverSystem = std::make_unique<GameOverSystem>(*this, EndScene, Witch, endSceneTexture_Lost, endSceneTexture_Won);
        }
    });

    //UI
    ////Healthbar
    WitchBackgroundHealthBar = &entityManager.createEntity();
    witchBackgroundHealthBarTransform =
        &WitchBackgroundHealthBar->addComponent<TransformComponent>(origin, glm::vec2(0, 0), 0, glm::vec2(100 * 2.0f, 30 * 2.0f));
    witchBackgroundHealthBarSprite = &WitchBackgroundHealthBar->addComponent<SpriteComponent>(witchBackgroundHealthbarTexture, glm::vec4(1,1,1,1));
    // The background of the healthbar does not have an UIComponent, because it is not interactive or changes
    //Drawing the UI representation of the Players Health
    WitchHealthQuad = &entityManager.createEntity();
    witchHealthQuadTransform = &WitchHealthQuad->addComponent<TransformComponent>(
        witchBackgroundHealthBarTransform,
        glm::vec2(22, 20),
        0,
        glm::vec2(14 * 2.5f * witchHealth->health, 12 * 2.0f));
    witchHealthQuadSprite = &WitchHealthQuad->addComponent<SpriteComponent>(witchHealthQuadTexture, glm::vec4(1,1,1,1));
    witchHealthQuadComponent = &WitchHealthQuad->addComponent<UiComponent>();

    ////ShieldCooldownBar
    /////Drawing the UI representation of the shield cooldown
    ShieldBar = &entityManager.createEntity();
    shieldBarTransform =
        &ShieldBar->addComponent<TransformComponent>(origin,
            witchBackgroundHealthBarTransform->localPosition + glm::vec2(witchBackgroundHealthBarTransform->localScale.x + 20, 0),
            0,
            glm::vec2(100 * 2.0f, 30 * 2.0f));
    shieldBarSprite = &ShieldBar->addComponent<SpriteComponent>(shieldCoolDownBarTexture, glm::vec4(1,1,1,1));

    ShieldQuad = &entityManager.createEntity();
    shieldQuadTransform = &ShieldQuad->addComponent<TransformComponent>(
        shieldBarTransform,
        shieldBarTransform->localPosition + glm::vec2(22, 20),
        0,
        glm::vec2(120, 12 * 2.0f));
    shieldQuadSprite = &ShieldQuad->addComponent<SpriteComponent>(shieldQuadTexture, glm::vec4(1,1,1,1));
    shieldQuad = &ShieldQuad->addComponent<UiComponent>();
    shieldQuadMaxX = shieldQuadTransform->localScale.x;

    //Main Enemy: Creature
    Creature = &entityManager.createEntity();
    creatureEnemyComponent = &Creature->addComponent<EnemyComponent>(CREATURE);
    creatureTransform = &Creature->addComponent<TransformComponent>(origin,
        glm::vec2(1100, 600),
        0,
        glm::vec2(600/4, 500/4),
        70);
    creatureSprite = &Creature->addComponent<SpriteComponent>(
        creatureTexture,
        glm::vec2(600, 500),
        1,
        1,
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    creatureHealth = &Creature->addComponent<HealthComponent>(8);
    creatureCollider = &Creature->addComponent<ColliderComponent>(ENEMY, 1.0f, [this]{
        //This method will only be called on collision
            // this implementation reduces the health of the Player/Witch
        if (creatureCollider->isInvulnerable) return;

        ColliderComponent* colliderComponent = &Creature->getComponent<ColliderComponent>();
        if(!colliderComponent || !colliderComponent->currCollidingEntity) return;

        Entity* collidingEntity = colliderComponent->currCollidingEntity;
        if(collidingEntity && !collidingEntity->isDeleted()) {
            if(this->componentManager.hasComponent<MissileComponent>(collidingEntity->guid())) {
                MissileComponent& missile = collidingEntity->getComponent<MissileComponent>();
                if(missile.type == WAVE) {
                    currScore += 20;
                }
                else if(missile.type == CHARGE && !missile.isBeingCharged){
                    currScore += 150;
                }
                else if(missile.type != CHARGE){
                    currScore += 40;
                }
            }
        }

        if(currScore >= maxScore) {
            this->setGameState(gl3::brewEngine::GAME_WIN);
            EndScene = &this->entityManager.createEntity();
            endSceneTransform = &EndScene->addComponent<TransformComponent>(origin,
                glm::vec2(0, 0),
                0,
                glm::vec2(this->getWindowWidth(), this->getWindowHeight()));
            gameOverSystem =
                std::make_unique<GameOverSystem>(*this, EndScene, Witch, endSceneTexture_Lost, endSceneTexture_Won);
        }
        creatureCollider->isInvulnerable = true;

    });

    CutScene = &this->entityManager.createEntity();
    cutSceneTransform =
            &CutScene->addComponent<TransformComponent>(origin,
                    glm::vec2(0.0f, 0.0f),
                    0,
                    glm::vec2(this->getWindowWidth(),
                    this->getWindowHeight()),
                    0);

    introSystem = std::make_unique<IntroSystem>(*this, CutScene);
    enemySystem = std::make_unique<EnemySystem>(*this, Creature);
    playerSystem = std::make_unique<PlayerSystem>(*this, Witch, shieldCooldownUiNumber);
    collisionSystem = std::make_unique<CollisionSystem>(*this);
    missileSystem = std::make_unique<MissileSystem>(*this);
    shieldSystem = std::make_unique<ShieldSystem>(*this);
    // Loading a bigger font
    std::string path = gl3::brewEngine::resolveAssetPath("fonts/inter.ttf").string();
    bigfont = lf_load_font(path.c_str(), 30);
    mediumfont = lf_load_font(path.c_str(), 20);
}

void CTGame::update(GLFWwindow *window) {
    witchHealthQuadTransform->localScale.x = 19 * witchHealth->health;
    if(shieldCooldownUiNumber <= 20) {
        shieldQuadTransform->localScale.x = shieldQuadMaxX - static_cast<float>(shieldCooldownUiNumber) * 6.0f;
    }
    //draw();
}

void CTGame::draw() {
    if (this->getGameState() == gl3::brewEngine::GAME_ACTIVE) {
        //Score display
        std::string scoreText = "SCORE: " + std::to_string(currScore) + "  GOAL: 5000";
        {
            // Setting big font
            lf_push_font(&bigfont);
            LfUIElementProps scoreDisplay = lf_get_theme().text_props;
            scoreDisplay.text_color = LF_BLACK;
            // Center the text horizontally
            lf_set_ptr_x_absolute((this->getWindowWidth() - lf_text_dimension(scoreText.c_str()).x) / 2.0f);
            lf_set_ptr_y_absolute(0);
            // Push the style props
            lf_push_style_props(scoreDisplay);

            // Render the text
            lf_text(scoreText.c_str());

            // Pop the style props
            lf_pop_style_props();

            // Unsetting big font
            lf_pop_font();
        }
        //Controls
        std::string bottomText = "[W][A][S][D] = MOVEMENT     [SPACE] = DEFAULT SHOT     [E] = SPREAD SHOT     [F] = CHARGE SHOT     [L_SHIFT] = SHIELD";
        {
            // Setting big font
            lf_push_font(&mediumfont);
            LfUIElementProps bottomInfoDisplay = lf_get_theme().text_props;
            bottomInfoDisplay.text_color = LF_BLACK;
            lf_set_ptr_x_absolute(this->getWindowWidth() - 100);
            lf_set_ptr_y_absolute(this->getWindowHeight() - 64);
            // Push the style props
            lf_push_style_props(bottomInfoDisplay);

            // Render the text
            lf_text(bottomText.c_str());

            // Pop the style props
            lf_pop_style_props();

            // Unsetting big font
            lf_pop_font();
        }

    }
}
