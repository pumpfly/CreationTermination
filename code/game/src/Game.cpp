//
// Created by Lisa B on 22/10/2024.
//
#include "Game.h"

#include <array>
#include <iostream>

#include <random>
#include <stdexcept>
#include "Assets.h"
#include "SpatialGridManager.h"
#include "entities/Creature.h"
#include "entities/bats.h"
#include "input/Input.h"
#include "rendering/GeometryRenderer.h"
#include "rendering/ResourceManager.h"

namespace gl3 {

    void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Game::Game(int width, int height, const std::string &title) :
        projectionMatrix(glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f)),
        width(width),
        height(height)
    {
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            throw std::runtime_error("Failed to create window");
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        if(glGetError() != GL_NO_ERROR) {
            throw std::runtime_error("gl error");
        }

        //audio.init();
        //audio.setGlobalVolume(0.1f);

        glfwSetKeyCallback(window, brew::Input::key_callback);

    };

    glm::mat4 Game::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {

        // View Transform
        glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 90.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0),
                                     glm::vec3(0.0, 1.0, 0.0));
        // Projection Transform
        glm::mat4 projection = glm::perspective(glm::radians(2.0f), 1000.0f/600.0f, 0.1f, 100.0f);

        auto model = glm::mat4(1.0f);
        model = translate(model, position);
        model = glm::scale(model, scale);
        model = rotate(model, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

        return projection * view * model;
    }

    glm::mat4 Game::projection() const {
        return projectionMatrix;
    }

    void Game::init() {
        ResourceManager::LoadTexture("background/CreationTermination_background.png", true, "background");
    };

    void Game::run() {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glEnableVertexAttribArray(0);
        glBindVertexArray(VAO);

        glEnable(GL_BLEND);

        BackgroundManager b(glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec2(1920/1.5, 1080/1.5));
        background = b;

        auto witch = std::make_unique<Witch>(nullptr);
        w = witch.get();
        entities.push_back(std::move(witch));

        auto creature = std::make_unique<Creature>(nullptr);
        entities.push_back(std::move(creature));

        auto miniEnemy = std::make_unique<bats>();
        entities.push_back(std::move(miniEnemy));


        /*backgroundMusic = std::make_unique<SoLoud::Wav>();
        backgroundMusic->load(resolveAssetPath("audio/electronic-wave.mp3").string().c_str());
        audio.playBackground(*backgroundMusic);*/

        glfwSetTime(1.0 /200);

        while(!glfwWindowShouldClose(window)) {
            auto start = std::chrono::steady_clock::now();

            update();
            draw();
            updateDeltaTime();
            brew::Input::inputUpdate();

            auto end = std::chrono::steady_clock::now();
            //std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << '\n';
        }

        glDeleteVertexArrays(1, &VAO);
    };

    void Game::update() {
        background.update(deltaTime);
        draw();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        // Updating the spatial Grid for collision detection:

        SpatialGridManager currentGrid(150, 1280, 720);
        tempSpatialGrid = currentGrid;

        tempSpatialGrid.clearIDs();
        int cellSize = tempSpatialGrid.getCellSize();

        for(size_t i = 0; i < entities.size(); i++) {
            Entity entity = *entities[i];

            //Bounding Box calculation:
            int entitySizeX = static_cast<int>(entity.getSize().x);
            int entitySizeY = static_cast<int>(entity.getSize().y);

            int entityMinX = static_cast<int>(entity.getPosition().x);
            int entityMinY = static_cast<int>(entity.getPosition().y);

            int entityMaxX = static_cast<int>(entity.getPosition().x) + entitySizeX;
            int entityMaxY = static_cast<int>(entity.getPosition().y) + entitySizeY;

            //Cell Assignment
            // if entity is outside the grid than it should not be added to a spatialGrid cell
            if(entityMinX > 0 || entityMinY > 0
                || entityMinX < width || entityMinY < height)
            {
                tempSpatialGrid.cellAssignment(entityMinX, entityMaxX, entityMinY, entityMaxY, i);
            }
            entities[i]->update(this, deltaTime);
        }

    };

    void Game::draw() {
        //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        //SpriteRenderer::Instance().DrawSprite(this, ResourceManager::GetTexture("background"),
        //    glm::vec2(0.0f, 0.0f), glm::vec2(1920/1.5, 1080/1.5), 0.0f, glm::vec4(1, 1, 1, 1));
        background.draw(this);
         for(auto &entity: entities) {
            entity->draw(this);
        }

        SpatialGridManager::drawGrid(this, 150, 1280, 720);
        glfwSwapBuffers(window);
    };

    void Game::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    Game::~Game() {
        glfwTerminate();
    }
}

