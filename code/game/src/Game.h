//
// Created by Lisa B on 22/10/2024.
//

#pragma once

#include <glad/glad.h>
#include <memory>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BackgroundManager.h"
#include "SpatialGridManager.h"
#include "entities/Witch.h"

namespace gl3 {
    // Represents the current state of the game
    enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN
    };
    class Game {
    public:

        Game(int width, int height, const std::string &title = "Creation Termination");
        void init();
        void run();

        virtual ~Game();

        [[nodiscard]] Witch *getWitch() const { return w; }
        [[nodiscard]] GLFWwindow *getWindow() const { return window; }
        [[nodiscard]] std::vector<std::unique_ptr<Entity>> &getEntities() { return entities; }
        [[nodiscard]] SpatialGridManager &getSpatialGrid() { return tempSpatialGrid; }

        SpatialGridManager tempSpatialGrid = SpatialGridManager(150, 1280, 720);

        //// Background
        BackgroundManager layer1;
        BackgroundManager layer2;
        BackgroundManager layer3;

    private:
        static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
        void update();
        void draw();
        void updateDeltaTime();

        SoLoud::Soloud audio;
        std::unique_ptr<SoLoud::Wav> backgroundMusic;

        GLFWwindow *window = nullptr;
        int width;
        int height;

        Witch* w = nullptr;

        float zRotation = 0.0f;
        float rotationSpeed = 120.0f;
        float xTranslate = 0.0f;
        float yTranslate = 0.0f;
        float translationSpeed = 1.0f;

        float lastFrameTime = 1.0f/60;
        float deltaTime = 1.0f/60;

        std::vector<std::unique_ptr<Entity>> entities;
        };

    };



