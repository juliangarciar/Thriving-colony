#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/Panel.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>

using namespace irr;

class Hud {
    
    public:
        Hud();
        ~Hud();

        void getHUDEvents();

        Button *getInfoButton(); //ESTO ES TEMPORAL
    private:
        Button *buttonBuilding;
        Button *buttonQuit;

        Button *buttonInfo; //ESTO ES TEMPORAL

        Panel *tabs;
};

#endif