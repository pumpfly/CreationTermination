#include "EnemySystem.h"

#include <random>
#include <ctime>
#include "../Components/EnemyComponent.h"

float lerp(float a, float b, float f){ return a + f * (b - a);}

void EnemySystem::creatureMovement(Game& game, TransformComponent* creatureTransform, EnemyComponent* creature)
{
    std::time_t elapsedTime = std::time(nullptr);
    //zRotation = glm::degrees(theta_radians) - 90.0f;

    std::random_device dev;
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

