#pragma once

#include <string>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


namespace gl3 {
    class BackgroundManager {

    public:
        explicit BackgroundManager(std::string layerName = "firstLayer", glm::vec2 scale = glm::vec2(1280*3, 720));
        ~BackgroundManager()= default;

        void update(float deltaTime);
        void draw();

        [[nodiscard]] const std::string &getLayerName() const { return layerName; }

    private:
        float layer1speed = 1000.0f;
        float layer2speed = 700.0f;
        float layer3speed = 400.0f;

        glm::vec2 layer1_position = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer1copy_position = glm::vec2(1280*3, 0.0f);

        glm::vec2 layer2_position = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer2copy_position = glm::vec2(1280*3, 0.0f);

        glm::vec2 layer3_position = glm::vec2(0.0f, 0.0f);
        glm::vec2 layer3copy_position = glm::vec2(1280*3, 0.0f);

    protected:
        glm::vec2 scale;
        std::string layerName;
    };
}
