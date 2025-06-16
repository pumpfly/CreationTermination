#pragma once
#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"
#include "TransformComponent.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::sceneGraph::TransformComponent;

namespace gl3::brewEngine::sceneGraph {
    class SceneGraphPruner : public System {
    public:
        explicit SceneGraphPruner(Game &game) : System(game) {
            game.onBeforeUpdate.addListener([&](Game &game) {
                pruneTransforms(game);
            });
        }

        void pruneTransforms(Game &game) {
            game.componentManager.forEachComponent<TransformComponent>([&](TransformComponent &transform) {
                if(transform.isDeleted()) {
                    auto &entity = game.entityManager.getEntity(transform.entity());
                    game.entityManager.deleteEntity(entity);
                }
            });
        }
    };
}