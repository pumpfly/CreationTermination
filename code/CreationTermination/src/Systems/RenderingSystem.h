#pragma once

#include <iostream>
#include "brewEngine/ecs/System.h"

using gl3::brewEngine::ecs::System;

class RenderSystem : public System {
    void scrollBackgroundSprite(bool isScrollingSideways, bool goesLeftOrUp, float deltaTime);
};
