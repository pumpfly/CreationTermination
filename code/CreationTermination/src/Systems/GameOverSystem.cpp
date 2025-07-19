#include "GameOverSystem.h"

#include <iostream>

#include "../Components/EnemyComponent.h"
#include "../Components/MissileComponent.h"
#include "brewEngine/rendering/SpriteComponent.h"

extern "C" {
#include <leif.h>
}

GameOverSystem::GameOverSystem(Game &game, Entity *EndScene, const Texture2D &gameOver, const Texture2D &gameWon) : System(game) {
    game.onUpdate.addListener([&, EndScene](Game &g, float deltaTime) {
        if(g.getGameState() == GAME_ACTIVE) return;
        if(g.getGameState() == GAME_OVER) {
          endSceneSprite = &EndScene->addComponent<SpriteComponent>(gameOver);
        }
        if(g.getGameState() == GAME_WIN) {
          endSceneSprite = &EndScene->addComponent<SpriteComponent>(gameWon);
        }
        /* Exit Button */
        const char* btntext = "Exit";
        // Defining properties of the button
        LfUIElementProps btnprops = lf_get_theme().button_props;
        btnprops.margin_left = 0.0f; btnprops.margin_top = 15.0f; btnprops.border_width = 0.0f; btnprops.corner_radius = 9.0f;
        btnprops.text_color = LF_WHITE;
        btnprops.color = (LfColor){90, 90, 90, 255};
        {
          const float width = 50.0f;

          lf_push_style_props(btnprops);
          // Center the button horizontally
          int windowWidth = g.getContext().getWindowWidth();
            int windowHeight = g.getContext().getWindowHeight();
          lf_set_ptr_x_absolute(static_cast<float>(windowWidth)/2 - (width + btnprops.padding * 4.0f));
            lf_set_ptr_y_absolute(static_cast<float>(windowHeight)/2);
          // Rendering a button with fixed scale (-1 stands for "use normal height")
          auto button_state = lf_button_fixed(btntext, width, -1);
          if(button_state == LF_CLICKED) {
              glfwSetWindowShouldClose(g.getWindow(), 1);
          }

          lf_pop_style_props();
        }
        /* Reset Button */
        const char* rtbtntext = "Restart";
        // Defining properties of the button
        LfUIElementProps rtbtnprops = lf_get_theme().button_props;
        rtbtnprops.margin_left = 0.0f; rtbtnprops.margin_top = 15.0f; rtbtnprops.border_width = 0.0f; rtbtnprops.corner_radius = 9.0f;
        rtbtnprops.text_color = LF_WHITE;
        rtbtnprops.color = (LfColor){90, 90, 90, 255};
        {
          const float width = 50.0f;

          lf_push_style_props(rtbtnprops);
          // Center the button horizontally
          int windowWidth = g.getContext().getWindowWidth();
            int windowHeight = g.getContext().getWindowHeight();
          lf_set_ptr_x_absolute(static_cast<float>(windowWidth)/2 - (width + rtbtnprops.padding * 4.0f)*3);
            lf_set_ptr_y_absolute(static_cast<float>(windowHeight)/2);
          // Rendering a button with fixed scale (-1 stands for "use normal height")
          auto button_state = lf_button_fixed(rtbtntext, width, -1);
          if(button_state == LF_CLICKED) {
              game.componentManager.forEachComponent<EnemyComponent>([&](EnemyComponent& component) {
                guid_t id =component.entity();
                if(id != -1) {
                  game.entityManager.deleteEntity(game.entityManager.getEntity(id));
                }
              });
              game.componentManager.forEachComponent<MissileComponent>([&](MissileComponent& component) {
                guid_t id =component.entity();
                if(id != -1) {
                  game.entityManager.deleteEntity(game.entityManager.getEntity(id));
                }
              });
            //Player

            //Creature
          }

          lf_pop_style_props();
        }
    });
}
