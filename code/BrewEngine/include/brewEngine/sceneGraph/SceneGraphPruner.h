#pragma once
#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"
#include "Transform.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::sceneGraph::Transform;

namespace gl3::brewEngine::sceneGraph {
    class SceneGraphPruner : public System {
    public:
        explicit SceneGraphPruner(Game &game) : System(game) {
            game.onBeforeUpdate.addListener([&](Game &game) {
                pruneTransforms(game);
            });
        }

        void pruneTransforms(Game &game) {
            game.componentManager.forEachComponent<Transform>([&](Transform &transform) {
                if(transform.isDeleted()) {
                    auto &entity = game.entityManager.getEntity(transform.entity());
                    game.entityManager.deleteEntity(entity);
                }
            });
        }
    };
}