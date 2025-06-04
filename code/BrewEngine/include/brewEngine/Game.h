#pragma once
#include <memory>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gl3::engine {

    enum GameState {
        GAME_ACTIVE,
        GAME_MENU,
        GAME_WIN,
        GAME_OVER
    };

    class Game {
    public:
        GLFWwindow *getWindow() { return window; }

    private:
        float lastFrameTime = 1.0f / 60;

    protected:
        Game(int width, int height, const std::string &title);
        virtual ~Game();
        void init();
        virtual void run(){}
        virtual void update() {}
        virtual void draw() {}
        void updateDeltaTime();

        GLFWwindow *window = nullptr;
        //SoLoud::Soloud audio;
        float deltaTime = 1.0f / 60;
    };
}