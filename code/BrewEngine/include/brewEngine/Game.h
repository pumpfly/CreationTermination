#pragma once

#include <glad/glad.h>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <soloud.h>
#include <soloud_wav.h>
#include "brewEngine/Context.h"
#include "brewEngine/Events.h"
#include "brewEngine/ecs/ComponentManager.h"
#include "brewEngine/ecs/EntityManager.h"
#include "brewEngine/collision/SpatialGridManager.h"
#include "brewEngine/sceneGraph/TransformComponent.h"

using gl3::brewEngine::sceneGraph::TransformComponent;

namespace gl3::brewEngine {
    namespace ecs {
        class EntityManager;
        class ComponentManager;
    }
    namespace collision {
        class SpatialGridManager;
    }

    class Game {
    public:
        using event_t = events::Events<Game, Game&>;

        void run();
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
        GLFWwindow* getWindow() { return context.getWindow(); }
        context::Context& getContext() { return context; }
        [[nodiscard]] float getDeltaTime() const { return deltaTime;}

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_t onUpdate;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        ecs::ComponentManager componentManager;
        ecs::EntityManager entityManager;
        collision::SpatialGridManager spatialGridManager;
        TransformComponent *origin = nullptr;

        //countdown
        const float countdownReset = 0.1f;
        float countdown = countdownReset;
        //Stopwatch/Timer
        float currentTime = 0;

    protected:
        Game(int width, int height, const std::string &title);
        virtual void start() {}
        virtual void update(GLFWwindow *window) {}
        virtual void draw() {}
        virtual ~Game();

        SoLoud::Soloud audio;
        float deltaTime = 1.0f / 60;

    private:
        void updateDeltaTime();

        context::Context context;
        float lastFrameTime = 1.0f / 60;
    };
}
