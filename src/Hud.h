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

        void showPopup(int tabId);
        void hidePopup();

        void getHUDEvents();
    private:
        Button *buttonBuilding;
        Button *buttonQuit;

        Button *buttonCloseTab1;
        Button *buttonCloseTab2;

        Button *createTroop1;
        Button *createTroop2;

        Panel *tabs;
        Tab *t1;
        Tab *t2;
};

#endif