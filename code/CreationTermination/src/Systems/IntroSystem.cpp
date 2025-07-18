#include "IntroSystem.h"
#include "brewEngine/rendering/SpriteComponent.h"

using gl3::brewEngine::rendering::SpriteComponent;

IntroSystem::IntroSystem(Game &game): System(game){
    game.onUpdate.addListener([&](Game &g, float deltaTime) {
        if(g.getGameState() == GAME_ACTIVE) return;
        Entity *CutScene = nullptr;
        TransformComponent *cutSceneTransform = nullptr;
        SpriteComponent *cutSceneSprite = nullptr;

        CutScene = &g.entityManager.createEntity();
        cutSceneTransform =
            &CutScene->addComponent<TransformComponent>(game.origin,
                    glm::vec2(0.0f, 0.0f),
                    0,
                    glm::vec2(g.getContext().getWindowWidth()/2,
                    g.getContext().getWindowHeight()/2),
                    0);

        std::string path = "sprites/cutScene_" + std::to_string(sceneIndex) + ".png";

        cutSceneSprite = &CutScene->addComponent<SpriteComponent>(path.c_str());
        sceneCountdown = sceneCountdown + deltaTime*2;
        if (sceneCountdown >= 5 && sceneIndex <=5) {
            sceneIndex++;
            sceneCountdown = 0;
        }
        if(sceneIndex == 6) {
            game.entityManager.deleteEntity(*CutScene);
            g.setGameState(GAME_ACTIVE);
        }
    });
}
