#include "Keyboard.h"

#include <GraphicEngine/Window.h>
#include <Game.h>

/// ==============================
/// Keyboard
/// ==============================
Keyboard::Keyboard() {
    GLFWwindow *window = Window::Instance() -> getWindow();

    for (i32 i = 0; i < GLFW_KEY_LAST;i++){
        keyState[i] = Enumeration::UP;
    }

    glfwSetKeyCallback(window,
        [](GLFWwindow *w, i32 key, i32 scancode, i32 action, i32 mods) {
            Window::Instance() -> getGUIEnvironment() -> keyCallbackEvent(key, scancode, action, mods);
            Keyboard *s = Game::Instance() -> getKeyboard();
            // Key actions
            if (action == GLFW_PRESS) {
                s -> keyState[key] = Enumeration::PRESSED;
            } else if (action == GLFW_RELEASE) {
                s -> keyState[key] = Enumeration::RELEASED;
            } else if (action == GLFW_REPEAT) {
                s -> keyState[key] = Enumeration::DOWN;
            }
        }
    );
}

Keyboard::~Keyboard() {

}

/// ==============================
/// Event functions
/// ==============================
bool Keyboard::keyPressed(i32 keycode) {
    if (keyState[(i32)keycode] == Enumeration::PRESSED || keyState[(i32)keycode] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}

bool Keyboard::keyReleased(i32 keycode) {
    if (keyState[(i32)keycode] == Enumeration::RELEASED) {
        return true;
    } else {
        return false;
    }
}

bool Keyboard::keyRepeat(i32 keycode) {
    if (keyState[(i32)keycode] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}