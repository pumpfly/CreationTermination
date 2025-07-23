#pragma once
#include "GLFW/glfw3.h"

#define MAX_KEYBOARD_KEYS 512

namespace gl3::brewEngine::input {
    class Input {
    public:
        /// To access a Key this engine uses custom names, but are just openGL macros in disguise
        static enum {
            KEY_NULL            = 0,        // Key: NULL, used for no key pressed
            // Alphanumeric keys
            KEY_ZERO            = GLFW_KEY_0,       // Key: 0
            KEY_ONE             = GLFW_KEY_1,       // Key: 1
            KEY_TWO             = GLFW_KEY_2,       // Key: 2
            KEY_THREE           = GLFW_KEY_3,       // Key: 3
            KEY_FOUR            = GLFW_KEY_4,       // Key: 4
            KEY_FIVE            = GLFW_KEY_5,       // Key: 5
            KEY_SIX             = GLFW_KEY_6,       // Key: 6
            KEY_SEVEN           = GLFW_KEY_7,       // Key: 7
            KEY_EIGHT           = GLFW_KEY_8,       // Key: 8
            KEY_NINE            = GLFW_KEY_9,       // Key: 9
            KEY_A               = GLFW_KEY_A,       // Key: A | a
            KEY_B               = GLFW_KEY_B,       // Key: B | b
            KEY_C               = GLFW_KEY_C,       // Key: C | c
            KEY_D               = GLFW_KEY_D,       // Key: D | d
            KEY_E               = GLFW_KEY_E,       // Key: E | e
            KEY_F               = GLFW_KEY_F,       // Key: F | f
            KEY_G               = GLFW_KEY_G,       // Key: G | g
            KEY_H               = GLFW_KEY_H,       // Key: H | h
            KEY_I               = GLFW_KEY_I,       // Key: I | i
            KEY_J               = GLFW_KEY_J,       // Key: J | j
            KEY_K               = GLFW_KEY_K,       // Key: K | k
            KEY_L               = GLFW_KEY_L,       // Key: L | l
            KEY_M               = GLFW_KEY_M,       // Key: M | m
            KEY_N               = GLFW_KEY_N,       // Key: N | n
            KEY_O               = GLFW_KEY_O,       // Key: O | o
            KEY_P               = GLFW_KEY_P,       // Key: P | p
            KEY_Q               = GLFW_KEY_Q,       // Key: Q | q
            KEY_R               = GLFW_KEY_R,       // Key: R | r
            KEY_S               = GLFW_KEY_S,       // Key: S | s
            KEY_T               = GLFW_KEY_T,       // Key: T | t
            KEY_U               = GLFW_KEY_U,       // Key: U | u
            KEY_V               = GLFW_KEY_V,       // Key: V | v
            KEY_W               = GLFW_KEY_W,       // Key: W | w
            KEY_X               = GLFW_KEY_X,       // Key: X | x
            KEY_Y               = GLFW_KEY_Z,       // Key: Y | y
            KEY_Z               = GLFW_KEY_Y,       // Key: Z | z
            // Function keys
            KEY_SPACE           = GLFW_KEY_SPACE,           // Key: Space
            KEY_ESCAPE          = GLFW_KEY_ESCAPE,          // Key: Esc
            KEY_ENTER           = GLFW_KEY_ENTER,           // Key: Enter
            KEY_TAB             = GLFW_KEY_TAB,             // Key: Tab
            KEY_BACKSPACE       = GLFW_KEY_BACKSPACE,       // Key: Backspace
            KEY_INSERT          = GLFW_KEY_INSERT,          // Key: Ins
            KEY_DELETE          = GLFW_KEY_DELETE,          // Key: Del
            KEY_RIGHT           = GLFW_KEY_RIGHT,           // Key: Cursor right
            KEY_LEFT            = GLFW_KEY_LEFT,            // Key: Cursor left
            KEY_UP              = GLFW_KEY_UP,              // Key: Cursor up
            KEY_SCROLL_LOCK     = GLFW_KEY_SCROLL_LOCK,     // Key: Scroll down
            KEY_LEFT_SHIFT      = GLFW_KEY_LEFT_SHIFT,      // Key: Shift left
            KEY_LEFT_CONTROL    = GLFW_KEY_LEFT_CONTROL,    // Key: Control left
            KEY_RIGHT_SHIFT     = GLFW_KEY_RIGHT_SHIFT,     // Key: Shift right
            KEY_RIGHT_CONTROL   = GLFW_KEY_RIGHT_CONTROL,   // Key: Control right
        }keys;

        //Keyboard
        /// The methods that track Inputs are limited to keyboard only.
        static bool IsKeyPressed(int key);
        static bool IsKeyDown(int key);
        static bool IsKeyReleased(int key);
        static bool IsKeyUp(int key);

        static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods); //For input handling

        static void inputUpdate();

    private:
        static uint8_t currentKeyState[MAX_KEYBOARD_KEYS];
    };
}


