
#pragma once
#include "ColliderComponent.h"
#include "brewEngine/Game.h"
#include "brewEngine/ecs/System.h"

using gl3::brewEngine::ecs::System;
using gl3::brewEngine::Game;

namespace gl3::brewEngine::collision {
    class CollisionSystem : public System {
        public:
        explicit CollisionSystem(Game &game) : System(game) {
            game.onUpdate.addListener([&] (Game &) {
                //filling spatialGrid
                game.componentManager.forEachComponent<ColliderComponent>([&](ColliderComponent& component){
                    Entity* Entity = &game.entityManager.getEntity(component.entity());
                    TransformComponent* entityTransform = &Entity->getComponent<TransformComponent>();
                    glm::vec2 entityPosition = entityTransform->localPosition;
                    int entityMinX = static_cast<int>(entityPosition.x);
                    int entityMinY = static_cast<int>(entityPosition.y);
                    int entityMaxX = static_cast<int>(entityPosition.x) + entityTransform->localScale.x;
                    int entityMaxY = static_cast<int>(entityPosition.y) + entityTransform->localScale.y;

                    //Cell Assignment
                    // if entity is outside the grid than it should not be added to a spatialGrid cell
                    if(entityMinX > 0 || entityMinY > 0
                        || entityMaxX < game.getContext().getWindowWidth() || entityMaxY < game.getContext().getWindowHeight())
                    {
                        game.spatialGridManager.cellAssignment(entityMinX, entityMaxX, entityMinY, entityMaxY, Entity->guid());
                    }
                });
            });
            game.onUpdate.addListener([&] (Game &) {
                    game.componentManager.forEachComponent<ColliderComponent>([&](ColliderComponent& component) {
                        Entity* Entity = &game.entityManager.getEntity(component.entity());
                        TransformComponent* entityTransform = &Entity->getComponent<TransformComponent>();
                        glm::vec2 entityPosition = entityTransform->localPosition;
                        int entityMinX = static_cast<int>(entityPosition.x);
                        int entityMaxX = static_cast<int>(entityPosition.x) + entityTransform->localScale.x;
                        int entityMinY = static_cast<int>(entityPosition.y);
                        int entityMaxY = static_cast<int>(entityPosition.y) + entityTransform->localScale.y;

                        std::vector<guid_t> collisionCandidates = game.spatialGridManager.queryForCollisionCandidates(entityMinX,
                            entityMaxX, entityMinY, entityMaxY);

                        for(int collisionCandidate : collisionCandidates) {
                            auto other = &game.entityManager.getEntity(collisionCandidate);
                            if(Entity == other){continue;}
                            if(hasCollision(game, Entity, other)) {
                                component.handleCollision();
                            }
                        }
                    });
                });
        }

        bool hasCollision(Game& game, Entity* entity, Entity* other);

    };
}

