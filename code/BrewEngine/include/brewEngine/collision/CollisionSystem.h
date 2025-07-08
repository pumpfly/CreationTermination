
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
                game.spatialGridManager.clearIDs();
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
                game.componentManager.forEachComponent<ColliderComponent>([&](ColliderComponent& component) {
                    Entity* Entity = &game.entityManager.getEntity(component.entity());
                    TransformComponent* entityTransform = &Entity->getComponent<TransformComponent>();
                    glm::vec2 entityPosition = entityTransform->localPosition;
                    int entityMinX = static_cast<int>(entityPosition.x);
                    int entityMaxX = static_cast<int>(entityPosition.x) + entityTransform->localScale.x;
                    int entityMinY = static_cast<int>(entityPosition.y);
                    int entityMaxY = static_cast<int>(entityPosition.y) + entityTransform->localScale.y;

                    std::vector<int> collisionCandidates = game.spatialGridManager.queryForCollisionCandidates(entityMinX,
                        entityMaxX, entityMinY, entityMaxY);
                    size_t n_candidates = collisionCandidates.size();
                    for(int collisionCandidate : collisionCandidates) {
                        auto other = &game.entityManager.getEntity(collisionCandidate);
                        if(Entity == other){continue;}
                        if(hasCollision(game, Entity, other)) {
                            //TODO: Why is hasCollision always false
                            component.handleCollision();
                        }
                    }
                });
            });
        }

        bool hasCollision(Game& game, Entity* entity, Entity* other);

    };
}

