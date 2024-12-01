#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <stdexcept>
#include <string>
#include "Bitmanipulation.h"

#include "Window.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/transform.hpp"

namespace brew {

    Window::Window(int width, int height, std::string const &title)
    {
        /*
         * WINDOW HANDLING
         */
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if(window == nullptr) {
            throw std::runtime_error("Failed to create window");
        }

        glfwSetWindowUserPointer(window, this);

        glfwMakeContextCurrent(window);
        //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // NOTE: Required for window resizing
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        if(glGetError() != GL_NO_ERROR) {
            throw std::runtime_error("gl error");
        }
        glfwSetKeyCallback(window, key_callback);

        std::vector<float> vertices = {0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                     0.0f, 1.0f, 0.0f};
        std::vector<unsigned int> indices = {
                     0, 1, 2,
                     0, 2, 3
                     };

        shader.emplace(defaultVertexShaderSource, defaultFragmentShaderSource);
        mesh.emplace(vertices, indices);

    }

    void Window::BeginDrawing() {
        glfwSwapBuffers(window);
        // reset pressed bit = 0b00000011 -> 0b00000001 and release bit 0b00000100 -> 0b00000000
        for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) {
            // TODO: DO in one bit operation for performance
            Bitmanipulation::clearBit(currentKeyState[i], 1);
            Bitmanipulation::clearBit(currentKeyState[i], 2);
        }
        glfwPollEvents();
    }

    void Window::EndDrawing() {
    }

    bool Window::ShouldClose() {
        return glfwWindowShouldClose(window);
    }

    /*
     * DRAWING
     */
    glm::mat4 Window::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {
        glm::mat4 model = glm::mat4(1.0f);
        model = translate(model, position);
        model = glm::scale(model, scale);
        model = rotate(model, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 view = lookAt(glm::vec3(0.0, 0.0, 90.0f),
                                     glm::vec3(0.0f, 0.0f, 0.0),
                                     glm::vec3(0.0, 1.0, 0.0));

        glm::mat4 projection = glm::perspective(glm::radians(2.0f), 1000.0f / 600.0f, 0.1f, 100.0f);

        return projection * view * model;
    }

    void Window::ClearBackground(Color color) {
        glClearColor(
            static_cast<float>(color.r)/255,
            static_cast<float>(color.g)/255,
            static_cast<float>(color.b)/255,
            static_cast<float>(color.a)/255);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::DrawRectangle(float x, float y, float width, float height, Color color) {
        /*mesh = Mesh({x + width/2, y + height/2, 0.0f,
                    x + width/2, y - height/2, 0.0f,
                    x - width/2, y - height/2, 0.0f,
                    x - width/2, y + height/2, 0.0f},
                    {0, 1, 2,
                    3, 4, 5,
                    6, 7, 8,
                    9, 10, 11});*/
        auto mvpMatrix = calculateMvpMatrix(glm::vec3(x, y, 0), 0, glm::vec3(width, height, 0));
        shader.value().use();
        shader.value().setMatrix("mvp", mvpMatrix);
        mesh.value().draw();
    }

    /*
     * INPUT HANDLING
     */
    bool Window::IsKeyPressed(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 1);
    }

    bool Window::IsKeyDown(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 0);
    }

    bool Window::IsKeyReleased(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 2);
    }

    bool Window::IsKeyUp(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 2) || currentKeyState[key] == 0;
    }

    void Window::CloseWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        auto *self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        switch(action) {
            case GLFW_PRESS: {
                //                                   v pressed this frame flag
                self->currentKeyState[key] = 0b00000011;
                //                                    ^ hold flag
            }break;
            case GLFW_RELEASE: {
                self->currentKeyState[key] = 0b00000100;
            }break;
            case GLFW_REPEAT: {
                //TODO: Maybe implement. Now it is only needed for handling the repeat case.
            }break;
            default: {
                throw std::runtime_error("Unhandled key action: " + std::to_string(action));
            }
        }
    }

    void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    }

    void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    }

    Window::~Window() {
        CloseWindow();
    }
}
