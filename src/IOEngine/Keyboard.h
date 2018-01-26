#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <GLFW/glfw3.h>
#include <Enumeration.h>

class Keyboard {
    public:
        Keyboard();
        ~Keyboard();

        bool keyPressed(int keycode);
        bool keyReleased(int keycode);
        bool keyRepeat(int keycode);

		// Keyboard key states.
		Enumeration::ioStatesENUM keyState[GLFW_KEY_LAST];
    private:
};

#endif