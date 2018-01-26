#include "Keyboard.h"

#include <GraphicEngine/Window.h>
#include <Game.h>

using namespace irr;

/// ==============================
/// Keyboard
/// ==============================
Keyboard::Keyboard() {
    GLFWwindow *window = Window::Instance() -> getWindow();

    for (int i = 0; i < GLFW_KEY_LAST;i++){
        keyState[i] = Enumeration::UP;
    }

    glfwSetKeyCallback(window,
        [](GLFWwindow *w, int key, int scancode, int action, int mods) {
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
bool Keyboard::keyPressed(int keycode) {
    if (keyState[(int)keycode] == Enumeration::PRESSED || keyState[(int)keycode] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}

bool Keyboard::keyReleased(int keycode) {
    if (keyState[(int)keycode] == Enumeration::RELEASED) {
        return true;
    } else {
        return false;
    }
}

bool Keyboard::keyRepeat(int keycode) {
    if (keyState[(int)keycode] == Enumeration::DOWN) {
        return true;
    } else {
        return false;
    }
}