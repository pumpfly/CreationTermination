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
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist{-50, 50};
    bool tooClose = false;

    auto distanceToWitch = glm::distance(smallEnemyTransfrom->localPosition, playerTransform->localPosition);

    if (distanceToWitch >= 0.5f && !tooClose)
    {
        smallEnemyTransfrom->localPosition.x = lerp(smallEnemyTransfrom->localPosition.x, playerTransform->localPosition.x, game.getDeltaTime());
        smallEnemyTransfrom->localPosition.y = lerp(smallEnemyTransfrom->localPosition.y, playerTransform->localPosition.y, game.getDeltaTime());
        if(distanceToWitch > 0.5 && distanceToWitch < 0.6) {
            tooClose = true;
        }
    }
    if(tooClose) {
        float newPosition = dist(rng);
        //TODO:: bats should not stay with the witch but should fly through her and back
        smallEnemyTransfrom->localPosition.x = lerp(smallEnemyTransfrom->localPosition.x,
            smallEnemyTransfrom->localPosition.x + newPosition, game.getDeltaTime());;
        smallEnemyTransfrom->localPosition.y = lerp(smallEnemyTransfrom->localPosition.y,
            smallEnemyTransfrom->localPosition.y + newPosition, game.getDeltaTime());;

        tooClose = false;
    }
}

