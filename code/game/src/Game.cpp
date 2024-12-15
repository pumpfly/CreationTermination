//
// Created by Lisa B on 22/10/2024.
//
#include "Game.h"

#include <iostream>

#include <random>
#include <stdexcept>

#include "Assets.h"
#include "input/Input.h"

namespace gl3 {

    void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Game::Game(int width, int height, const std::string &title) :
        projectionMatrix(glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f))
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

        audio.init();
        audio.setGlobalVolume(0.1f);

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

    void Game::run() {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glEnableVertexAttribArray(0);
        glBindVertexArray(VAO);

        glEnable(GL_BLEND);

        std::mt19937 randomNumberEngine{ static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
        std::uniform_real_distribution positionDist{-1.5, 2.0};
        std::uniform_real_distribution scaleDist{0.2, 5.0};
        std::uniform_real_distribution colorDist{0.5, 1.0};
        std::uniform_real_distribution extraNumber{0.3, 0.8};
        /*for(auto i = 0; i < 50; ++i) {
            auto randomPosition = glm::vec3(static_cast<float>(positionDist(randomNumberEngine) * 1.5), static_cast<float>(positionDist(randomNumberEngine) * 1.5) , 0);
            auto randomScale = static_cast<float>(scaleDist(randomNumberEngine));
            auto c = colorDist(randomNumberEngine);
            auto r = extraNumber(randomNumberEngine);
            auto randomColor = glm::vec4( c/r, c/2.0, c, 1.0);
            auto entity = std::make_unique<Planet>(nullptr, randomPosition, randomScale, randomColor);
            entities.push_back(std::move(entity));
        }*/

        auto spaceShip = std::make_unique<Ship>(nullptr, glm::vec3(-2, 0, 0));
        ship = spaceShip.get();
        entities.push_back(std::move(spaceShip));

        /*auto enemy = std::make_unique<Enemy>(nullptr, glm::vec3(2, 0, 0), -90, 0.25);
        entities.push_back(std::move(enemy));*/

        /*for(int i = 0; i < 2000; i++) {
            auto miniEnemy = std::make_unique<Minienemies>(glm::vec3(1, 0, 0), -90, 0.07);
            entities.push_back(std::move(miniEnemy));
        }*/

        backgroundMusic = std::make_unique<SoLoud::Wav>();
        backgroundMusic->load(resolveAssetPath("audio/electronic-wave.mp3").string().c_str());
        audio.playBackground(*backgroundMusic);


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
        for(auto &entity: entities) {
            entity->update(this, deltaTime);
        }
    };

    void Game::draw() {
        glClearColor(0.87f, 0.95f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for(auto &entity: entities) {
            entity->draw(this);
        }

        glfwSwapBuffers(window);
    };

    void Game::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    Game::~Game() {
        glfwTerminate();
    };
}

