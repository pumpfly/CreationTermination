//
// Created by Lisa B on 22/10/2024.
//
#include "Game.h"

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
        windowWidth(width),
        windowHeight(height)
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

    void Game::init() {
        //First Layer
        ResourceManager::LoadTexture("background/forest_1stLayer.png", true, "firstLayer");
        //Second Layer
        ResourceManager::LoadTexture("background/forest_2dLayer.png", true, "secondLayer");
        //Third Layer
        ResourceManager::LoadTexture("background/forest_3dLayer.png", true, "thirdLayer");
    };

    void Game::run() {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glEnableVertexAttribArray(0);
        glBindVertexArray(VAO);

        glEnable(GL_BLEND);

        ////Background Layers
        BackgroundManager bg1("firstLayer");
        BackgroundManager bg2("secondLayer");
        BackgroundManager bg3("thirdLayer");

        layer1 = bg1;
        layer2 = bg2;
        layer3 = bg3;

        ////Entities
        auto witch = std::make_unique<Witch>(nullptr);
        //Witch* w = witch.get();
        entities.push_back(std::move(witch));

        auto creature = std::make_unique<Creature>(nullptr);
        entities.push_back(std::move(creature));

        auto miniEnemy = std::make_unique<bats>();
        entities.push_back(std::move(miniEnemy));

        tempSpatialGrid = SpatialGridManager(150, 1280, 720);

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
        draw();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        //Update Backgrounds
        layer1.update(deltaTime);
        layer2.update(deltaTime);
        layer3.update(deltaTime);

        // Updating the spatial Grid for collision detection:

        tempSpatialGrid.clearIDs();
        int cellSize = tempSpatialGrid.getCellSize();

        for(size_t i = 0; i < entities.size(); i++) {
            Entity entity = *entities[i];

            //Bounding Box calculation:
            int entityMinX = static_cast<int>(entity.getPosition().x);
            int entityMinY = static_cast<int>(entity.getPosition().y);
            int entityMaxX = static_cast<int>(entity.getPosition().x) + entity.getSize().x;
            int entityMaxY = static_cast<int>(entity.getPosition().y) + entity.getSize().y;

            //Cell Assignment
            // if entity is outside the grid than it should not be added to a spatialGrid cell
            if(entityMinX > 0 || entityMinY > 0
                || entityMaxX < windowWidth || entityMaxY < windowHeight)
            {
                tempSpatialGrid.cellAssignment(entityMinX, entityMaxX, entityMinY, entityMaxY, i);
            }
        }
        for(const auto & entitie : entities) {
            entitie->update(this, deltaTime);
        }

    };

    void Game::draw() {
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Drawing Background
        layer3.draw();
        layer2.draw();
        layer1.draw();
        // Drawing Entities
         for(auto &entity: entities) {
            entity->draw();
        }

        //For Debugging:
        SpatialGridManager::drawGrid(150, 1280, 720);

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

