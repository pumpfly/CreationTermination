//
// Created by pumf on 16/05/2025.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "brewEngine/Config.h"


namespace gl3 {
    const glm::mat4 ProjectionMatrix =
        glm::ortho(0.0f, brewEngine::config::ScreenSize.x, brewEngine::config::ScreenSize.y, 0.0f, -1.0f, 1.0f);
}
