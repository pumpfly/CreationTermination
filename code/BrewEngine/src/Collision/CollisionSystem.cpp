
#include "brewEngine/collision/CollisionSystem.h"

namespace gl3::brewEngine::collision {
    CollisionSystem::CollisionSystem(Game &game): System(game) {
        game.onUpdate.addListener([&] (Game & g, float deltaTime) {
            //SpatialGridManager::drawGrid(150, 1920/1.5, 1080/1.5);
            g.spatialGridManager.clearIDs();
            //filling spatialGrid
            g.componentManager.forEachComponent<ColliderComponent>([&](ColliderComponent& component){
                Entity* Entity = &g.entityManager.getEntity(component.entity());
                TransformComponent* entityTransform = &Entity->getComponent<TransformComponent>();
                glm::vec2 entityPosition = entityTransform->localPosition;
                int entityMinX = static_cast<int>(entityPosition.x);
                int entityMinY = static_cast<int>(entityPosition.y);
                int entityMaxX = static_cast<int>(entityPosition.x) + entityTransform->localScale.x;
                int entityMaxY = static_cast<int>(entityPosition.y) + entityTransform->localScale.y;

                //Cell Assignment
                // if entity is outside the grid than it should not be added to a spatialGrid cell
                if(entityMinX > 0 || entityMinY > 0
                   || entityMaxX < g.getContext().getWindowWidth() || entityMaxY < g.getContext().getWindowHeight())
                {
                    g.spatialGridManager.cellAssignment(entityMinX, entityMaxX, entityMinY, entityMaxY, Entity->guid());
                }
            });
            g.componentManager.forEachComponent<ColliderComponent>([&](ColliderComponent& component) {
                Entity* Entity = &g.entityManager.getEntity(component.entity());
                TransformComponent* entityTransform = &Entity->getComponent<TransformComponent>();
                glm::vec2 entityPosition = entityTransform->localPosition;
                int entityMinX = static_cast<int>(entityPosition.x);
                int entityMaxX = static_cast<int>(entityPosition.x) + entityTransform->localScale.x;
                int entityMinY = static_cast<int>(entityPosition.y);
                int entityMaxY = static_cast<int>(entityPosition.y) + entityTransform->localScale.y;

                std::vector<int> collisionCandidates = g.spatialGridManager.queryForCollisionCandidates(entityMinX,
                    entityMaxX, entityMinY, entityMaxY);
                size_t n_candidates = collisionCandidates.size();
                for(int collisionCandidate : collisionCandidates) {
                    auto other = &g.entityManager.getEntity(collisionCandidate);
                    if(Entity == other){continue;}
                    if(hasCollision(Entity, other)) {
                        component.currCollidingEntity = other;
                        component.handleCollision();
                    }
                }
            });
        });
    }

    bool CollisionSystem::hasCollision(Entity* entity, Entity* other) {
        TransformComponent* entityTransform = &entity->getComponent<TransformComponent>();
        TransformComponent* otherTransform = &other->getComponent<TransformComponent>();

        ColliderComponent* entityColliderComponent = &entity->getComponent<ColliderComponent>();
        ColliderComponent* otherColliderComponent = &other->getComponent<ColliderComponent>();

        glm::vec2 center1(entityTransform->localPosition + entityTransform->radius);
        glm::vec2 center2(otherTransform->localPosition + otherTransform->radius);

        glm::vec2 difference = center2 - center1;

        if(length(difference) < otherTransform->radius + entityTransform->radius) {
            if(entityColliderComponent->type != otherColliderComponent->type) {
                return true;
            }
        }
        return false;
    }
}
