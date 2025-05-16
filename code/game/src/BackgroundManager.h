#pragma once

#include "Game.h"
#include "glm/vec2.hpp"


class BackgroundManager {

public:
    explicit BackgroundManager( glm::vec2 position = glm::vec3(0.0f, 0.0f, 0.0f), float zRotation = 0.0f, glm::vec2 scale = glm::vec2(1920/1.5, 1080/1.5));
    ~BackgroundManager()= default;

    void update(float deltaTime);
    void draw(gl3::Game* game);

private:
    float layer1speed;
    float layer2speed;
    float layer3speed = 1.0f;

protected:
    glm::vec2 position;
    glm::vec2 scale;
    float zRotation;
};



