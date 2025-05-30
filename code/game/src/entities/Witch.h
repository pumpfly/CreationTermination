//
// Created by pumf on 24/10/2024.
//
#pragma once
#include "Entity.h"
#include "Missiles.h"
#include <soloud.h>
#include <soloud_wav.h>
#include <vector>

#include "Shield.h"

namespace gl3 {
    class Witch : public Entity{
    public:
        explicit Witch(Game* game, glm::vec2 position = glm::vec2(100.0f, 100.0f),
             float zRotation = 0.0f, glm::vec2 size = glm::vec2(120*1.6, 120),
             float radius = 50, glm::vec4 color = glm::vec4(1, 1, 1, 1.0f),
             Texture2D texture = Texture2D::FromFile("sprites/witch_idleSprites.png"),
             int health = 5,
             TYPE type = witch);

        void update(Game *game, float deltaTime) override;
        void draw() override;

    private:
        float spriteAnimTimer = 0.0f;
        int spriteAnimIndex = 0;

        glm::vec2 spriteFrameSize = glm::vec2(680, 415);

        float translationSpeed = 1.0f;
        float rotationSpeed = 120.0f;

        int entitySizeX = static_cast<int>(size.x);
        int entitySizeY = static_cast<int>(size.y);

        // bounding boxes for collision grid calculations
        int MinX = static_cast<int>(position.x);
        int MinY = static_cast<int>(position.y);
        int MaxX = static_cast<int>(position.x) + entitySizeX;
        int MaxY = static_cast<int>(position.y) + entitySizeY;

        //Collision
        const float timeBetweenDamage = 0.5f;
        float countdownTilNextDamage = timeBetweenDamage;
        std::vector<size_t> collsionCandidatesIDs;
        SpatialGridManager *spatialGrid{};

        bool charging = false;
        bool onlySingleMissile = false;
        float missileTempSize = 1.0f;

        //Missiles
        const float timeBetweenShots = 0.1f;
        float countdownUntilNextShot = timeBetweenShots;
        bool isInvulnerable = false;
        std::vector<std::unique_ptr<Missiles>> missiles;
        std::vector<std::unique_ptr<Missiles>> bigMissiles;
        std::vector<std::unique_ptr<Missiles>> waveMissiles;

        //Shield
        std::unique_ptr<Shield> shield;

        SoLoud::Soloud audio;
        SoLoud::Wav firingSound;
    };
}



