
#include "brewEngine/collision/CollisionSystem.h"

namespace gl3::brewEngine::collision {
    bool CollisionSystem::hasCollision(Game &game, Entity* entity, Entity* other) {
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
