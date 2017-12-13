#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Rect2D.h>
#include <GraphicEngine/Button.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>

using namespace irr;

class Hud {
    
    public:
        Hud();
        ~Hud();

        void getHUDEvents();
    private:
        /*
        enum idGUI {
            ID0,
            GUI_ID_BUILDING_BUTTON,
            GUI_ID_QUIT_BUTTON
        }; */
        
        Button *buttonBuilding;
        Button *buttonQuit;
};

#endif