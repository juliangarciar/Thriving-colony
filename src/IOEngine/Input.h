#ifndef INPUT_H
#define INPUT_H

#include <irrlicht.h>
#include <GraphicEngine/Screen.h>

using namespace irr;

class Input {
    public:
        Input();
        ~Input();

        bool OnEvent(const SEvent& event);
        bool IsKeyDown(EKEY_CODE keyCode) const;
        bool isMouseLDown() const;
        bool isMouseRDown() const;
        bool isWheelUp() const;
        bool getWheelState() const;
        void setWheelState(bool wheel1);
        
        gui::ICursorControl *getCursor();
        
    private:

        gui::ICursorControl *cursor;
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
        bool MouseDown[2];
        bool wheel[2];
};

#endif