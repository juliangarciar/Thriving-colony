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
        Panel *tabs;

        Tab *barrackMenu;
        Tab *barnMenu;
        Tab *workshopMenu;

        Button *buttonQuit;
        
        Button *buttonSchool;
        Button *buttonMarket;
        Button *buttonHospital;
        Button *buttonSiderurgy;
        Button *buttonQuarry;
        Button *buttonHome;
        Button *buttonBarrack;
        Button *buttonBarn;
        Button *buttonWorkshop;
        Button *buttonWall;
        Button *buttonTower;
        
        Button *buttonCloseTab1;
        Button *buttonCloseTab2;
        Button *buttonCloseTab3;

        Button *createTroop1;
        Button *createTroop2;
        Button *createTroop3;
};

#endif