#include "IntroSystem.h"

#include <iostream>
#include "brewEngine/rendering/SpriteComponent.h"

extern "C" {
#include <leif.h>
}


using gl3::brewEngine::rendering::SpriteComponent;

IntroSystem::IntroSystem(Game &game, Entity* CutScene): System(game){

    for(int i = 0; i<= 5; i++) {
        std::string path = "sprites/cutScene_" + std::to_string(i) + ".png";
        introSceneTextures.push_back( Texture2D::FromFile(path.c_str()));
    }

    game.onUpdate.addListener([&, CutScene](Game &g, float deltaTime) {
        if(g.getGameState() != gl3::brewEngine::GAME_INTRO) return;

        cutSceneSprite = &CutScene->addComponent<SpriteComponent>(introSceneTextures.at(sceneIndex), glm::vec4(1, 1, 1, 1));
        sceneCountdown = sceneCountdown + deltaTime*2;

        /* Skip Button */
        const char* btntext = "Skip";
        // Defining properties of the button
        LfUIElementProps btnprops = lf_get_theme().button_props;
        btnprops.margin_left = 0.0f; btnprops.margin_top = 15.0f; btnprops.border_width = 0.0f; btnprops.corner_radius = 9.0f;
        btnprops.text_color = LF_WHITE;
        btnprops.color = (LfColor){90, 90, 90, 255};
        {
          const float width = 50.0f;

          lf_push_style_props(btnprops);
          // Center the button horizontally
          int windowWidth = g.getWindowWidth();
          lf_set_ptr_x_absolute((static_cast<float>(windowWidth) - (width + btnprops.padding * 4.0f)));

          // Rendering a button with fixed scale (-1 stands for "use normal height")
          auto button_state = lf_button_fixed(btntext, width, -1);
          if(button_state == LF_CLICKED) {
            sceneIndex = 6;
          }

          lf_pop_style_props();
        }

        if (sceneCountdown >= 8 && sceneIndex <=8) {
            sceneIndex++;
            sceneCountdown = 0;
        }

        if(sceneIndex == 6) {
            game.entityManager.deleteEntity(*CutScene);
            g.setGameState(gl3::brewEngine::GAME_ACTIVE);
        }
    });
}
