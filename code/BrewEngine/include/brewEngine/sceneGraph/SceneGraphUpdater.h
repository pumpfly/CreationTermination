#pragma once

#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"
#include "Transform.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::sceneGraph::Transform;

namespace gl3::brewEngine::sceneGraph {
    class SceneGraphUpdater : public System {
    public:
        explicit SceneGraphUpdater(Game &game) : System(game) {
            game.onUpdate.addListener([&](Game &) {
                updateTransforms(game);
            });
        }

        static void updateTransforms(Game &game) {
            game.componentManager.forEachComponent<Transform>([&](Transform &transform) {
                transform.modelMatrix = calculateModelMatrix(transform);
            });
        }

    private:
        static glm::mat4 calculateModelMatrix(Transform &transform) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.localPosition);
            model = glm::scale(model, transform.localScale);
            model = glm::rotate(model, glm::radians(transform.localZRotation), glm::vec3(0, 0, 1));
            return model;
        }
    };
}