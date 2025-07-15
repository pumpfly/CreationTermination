#pragma once

#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"
#include "TransformComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::sceneGraph::TransformComponent;

namespace gl3::brewEngine::sceneGraph {
    class SceneGraphUpdater : public System {
    public:
        explicit SceneGraphUpdater(Game &game) : System(game) {
            game.onUpdate.addListener([&](Game & g, float deltaTime) {
                updateTransforms(g);
            });
        }

        static void updateTransforms(Game &game) {
            game.componentManager.forEachComponent<TransformComponent>([&](TransformComponent &transform) {
                transform.modelMatrix = calculateModelMatrix(transform);
            });
        }

    private:
        static glm::mat4 calculateModelMatrix(TransformComponent &transform) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(transform.localPosition, 0));
            model = glm::scale(model, glm::vec3(transform.localScale, 0));
            model = glm::rotate(model, glm::radians(transform.localZRotation), glm::vec3(0, 0, 1));
            return model;
        }
    };
}