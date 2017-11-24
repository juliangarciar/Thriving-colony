#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <irrlicht.h>

using namespace irr;

class InputManager : public IEventReceiver {
    public:
        InputManager();
        ~InputManager();

        bool OnEvent(const SEvent& event);
        bool IsKeyDown(EKEY_CODE keyCode) const;
        bool isMouseLDown() const;
        bool isMouseRDown() const;
        bool isWheelUp() const;
        bool getWheelState() const;
        void setWheelState(bool wheel1);
        
    private:
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
        bool MouseDown[2];
        bool wheel[2];
};

#endif