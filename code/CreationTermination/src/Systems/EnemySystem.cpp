#include "EnemySystem.h"

#include <ctime>
#include "../Components/EnemyComponent.h"


void EnemySystem::creatureMovement(Game& game, TransformComponent* creatureTransform, EnemyComponent* creature)
{
    std::time_t elapsedTime = std::time(nullptr);
    //zRotation = glm::degrees(theta_radians) - 90.0f;

    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{-1.2f, 500.0f};

    creature->countdown -= game.getDeltaTime();
    for(int i = 0; i < 20; i++) {
        if(creature->countdown <= 0) {
            creature->newPosition = dist(rng);
            creature->countdown = creature->positionChangeTime;
        }
    }
    creatureTransform->localPosition.y = lerp(creatureTransform->localPosition.y, creature->newPosition,
        game.getDeltaTime() * creature->speed);

}

void EnemySystem::smallEnemyBehavior(Game& game, TransformComponent* playerTransform, TransformComponent* smallEnemyTransfrom, float speed)
{
    auto distanceToWitch = glm::distance(smallEnemyTransfrom->localPosition, playerTransform->localPosition);

    if (distanceToWitch >= 0.5f || distanceToWitch <= -0.5f)
    {
        smallEnemyTransfrom->localPosition.x = EnemySystem::lerp(smallEnemyTransfrom->localPosition.x, playerTransform->localPosition.x, game.getDeltaTime() * speed);
        smallEnemyTransfrom->localPosition.y = EnemySystem::lerp(smallEnemyTransfrom->localPosition.y, playerTransform->localPosition.y, game.getDeltaTime() * speed);
    }
}

