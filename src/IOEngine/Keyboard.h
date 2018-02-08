#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>
#include <Enumeration.h>
#include <Types.h>

class Keyboard {
    public:
        Keyboard();
        ~Keyboard();

        bool keyPressed(i32 keycode);
        bool keyReleased(i32 keycode);
        bool keyRepeat(i32 keycode);

		// Keyboard key states.
		Enumeration::ioStatesENUM keyState[GLFW_KEY_LAST];
    private:
};

#endif