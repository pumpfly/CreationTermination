#pragma once
#include <string>
#include <functional>
#include <GLFW/glfw3.h>

extern "C" {
#include <leif.h>
}

namespace gl3::brewEngine::context {
    class Context {
    public:
        using Callback = std::function<void(Context&)>;

        explicit Context(int width = 1920/1.5, int height = 1080/1.5, const std::string &title = "Game");
        virtual ~Context();
        void run(const Callback& update);
        [[nodiscard]] GLFWwindow *getWindow() { return window; }
        [[nodiscard]] int getWindowWidth() { return width; }
        [[nodiscard]] int getWindowHeight() { return height; }

    private:
        GLFWwindow *window = nullptr;
        int width, height;
    };
}