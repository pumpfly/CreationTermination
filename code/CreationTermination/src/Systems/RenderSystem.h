#pragma once
#include <iostream>
#include "brewEngine/ecs/System.h"


using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;
using gl3::brewEngine::sceneGraph::Transform;

class RenderSystem : public System {
public:
    explicit RenderSystem(Game &game) : System(game) {
        game.onAfterUpdate.addListener([&](Game&) {
            visitTransform(*game.origin);
        });
    }

    void visitTransform(Transform &transform, glm::mat4 parentLocalToWorld = glm::identity<glm::mat4>()) {
        if(transform.isDeleted()) return;
        auto localToWorld = transform.modelMatrix * parentLocalToWorld;
        auto worldPos = localToWorld * glm::vec4(0, 0, 0, 1);
        std::cout << "Entity " << transform.entity() << " is at (" << worldPos.x << ", " << worldPos.y << ")" << std::endl;
        for(auto child: transform.getChildTransforms()) {
            visitTransform(*child, localToWorld);
        }
    }
};