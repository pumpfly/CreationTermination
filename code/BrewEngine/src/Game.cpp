#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "brewEngine/Game.h"
#include "brewEngine/sceneGraph/SceneGraphUpdater.h"
#include "brewEngine/sceneGraph/SceneGraphPruner.h"


namespace gl3::brewEngine {
    using Context = brewEngine::context::Context;
    using ecs::ComponentManager;
    using ecs::EntityManager;
    using sceneGraph::SceneGraphUpdater;
    using sceneGraph::SceneGraphPruner;

    Game::Game(int width, int height, const std::string &title) :
            context(width, height, title),
            componentManager(*this),
            entityManager(componentManager, *this) {
        //audio.init();
        //audio.setGlobalVolume(0.1f);
        origin = &entityManager.createEntity().addComponent<TransformComponent>();
    }

    void Game::run() {
        SceneGraphUpdater sceneGraphUpdater(*this);
        SceneGraphPruner sceneGraphPruner(*this);
        onStartup.invoke(*this);
        start();
        onAfterStartup.invoke(*this);
        gl3::brewEngine::sceneGraph::SceneGraphUpdater::updateTransforms(*this);
        context.run([&](Context &ctx){
            onBeforeUpdate.invoke(*this);
            update(getWindow());
            onUpdate.invoke(*this);
            draw();
            updateDeltaTime();
            onAfterUpdate.invoke(*this);
        });
        onBeforeShutdown.invoke(*this);
        onShutdown.invoke(*this);
    }

    void Game::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    glm::mat4 Game::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 90.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0),
                                     glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 projection = glm::perspective(glm::radians(2.0f), 1000.0f / 600.0f, 0.1f, 100.0f);

        return projection * view * model;
    }

    Game::~Game() {
        context.~Context();
    }
}