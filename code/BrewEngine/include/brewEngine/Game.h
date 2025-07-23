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
    enum GameState
    {
        GAME_INTRO,
        GAME_ACTIVE,
        GAME_OVER,
        GAME_WIN
    };

    class Game {

    public:
        using event_t = events::Events<Game, Game&>;
        using update_event_t = events::Events<Game, Game&, float>;

        /// call function run() to start the program and the game loop
        void run();
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
        GLFWwindow* getWindow() { return context.getWindow(); }
        int getWindowWidth(){ return context.getWindowWidth(); }
        int getWindowHeight(){ return context.getWindowHeight(); }
        [[nodiscard]] float getDeltaTime() const { return deltaTime;}

        /// Game states are being represented by a simple enum @class GameStates.
        /// @function getGameState() returns the current state. The default state is the @enum GAME_INTRO state.
        /// With this method one can gate keep access of code blocks that are only meant for a specific game state.
        /// @function setGameState() allows to change the current State.
        GameState getGameState(){return currentState;}
        void setGameState(GameState newState){currentState = newState;}

        /// These are all the events, which can be used to add listeners to.
        /// brewEngine::Game is the owner of those events and so they can only be invoked by the game.
        /// Additionally, they pass a reference of a game to the event listeners (Systems)
        /// Therefore in order to use the events properly, the user should make their own game file inherit the brewEngine::Game class
        event_t onStartup;
        event_t onAfterStartup;
        event_t onBeforeUpdate;
        update_event_t onUpdate;
        event_t onAfterUpdate;
        event_t onBeforeShutdown;
        event_t onShutdown;

        ecs::ComponentManager componentManager;
        ecs::EntityManager entityManager;
        collision::SpatialGridManager spatialGridManager;
        TransformComponent *origin = nullptr;

    protected:
        Game(int width, int height, const std::string &title);
        /// @function start() will be called once at the start of the game.
        /// To use it, the user should create an override function inside their own game file.
        virtual void start() {}
        /// @function update gets called every frame.
        virtual void update(GLFWwindow *window) {}
        /// @function draw gets called every frame.
        virtual void draw() {}
        virtual ~Game();

        SoLoud::Soloud audio;
        float deltaTime = 1.0f / 60;

    private:
        void updateDeltaTime();

        GameState currentState = GAME_INTRO;
        context::Context context;
        float lastFrameTime = 1.0f / 60;
    };
}
