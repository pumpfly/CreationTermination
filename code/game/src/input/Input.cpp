//
// Created by pumf on 05/12/2024.
//

#include "Input.h"
#include <stdexcept>
#include <string>

#include "Bitmanipulation.h"

namespace brew {
    /*Input::Input(GLFWwindow *window) {
        glfwSetKeyCallback(window, key_callback);
    }*/

    uint8_t Input::currentKeyState[MAX_KEYBOARD_KEYS]{};

    void Input::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        switch(action) {
            case GLFW_PRESS: {
                //                             v pressed this frame flag
                currentKeyState[key] = 0b00000011;
                //                              ^ hold flag
            }break;
            case GLFW_RELEASE: {
                currentKeyState[key] = 0b00000100;
            }break;
            case GLFW_REPEAT: {
                //TODO: Maybe implement. Now it is only needed for handling the repeat case.
            }break;
            default: {
                throw std::runtime_error("Unhandled key action: " + std::to_string(action));
            }
        }
    }

    void Input::inputUpdate() {
        for (int i = 0; i < MAX_KEYBOARD_KEYS; i++) {
            // TODO: DO in one bit operation for performance
            Bitmanipulation::clearBit(currentKeyState[i], 1);
            Bitmanipulation::clearBit(currentKeyState[i], 2);
        }
        glfwPollEvents();
    }

    bool Input::IsKeyPressed(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 1);
    }

    bool Input::IsKeyDown(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 0);
    }

    bool Input::IsKeyReleased(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 2);
    }

    bool Input::IsKeyUp(int key) {
        return Bitmanipulation::isBitSet(currentKeyState[key], 2) || currentKeyState[key] == 0;
    }
}
