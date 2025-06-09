#pragma once

#pragma once
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
#include "brewEngine/sceneGraph/Transform.h"

namespace gl3::brewEngine {

    enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN,
        GAME_OVER
    };

    class Game {
    public:
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
        using event_t = brewEngine::events::Events<Game, Game&>;

        void run();
        GLFWwindow *getWindow() { return window; }

        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        event_t onUpdate;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        ecs::ComponentManager componentManager;
        ecs::EntityManager entityManager;

    private:
        float lastFrameTime = 1.0f / 60;
        void updateDeltaTime();

        context::Context context;

    protected:
        Game(int width, int height, const std::string &title);
        virtual void start(){}
        void init();
        virtual void update(GLFWwindow * window) {}
        virtual void draw() {}
        virtual ~Game();

        GLFWwindow *window = nullptr;
        //SoLoud::Soloud audio;
        float deltaTime = 1.0f / 60;
    };
}
