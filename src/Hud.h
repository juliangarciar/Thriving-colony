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

        Tab *mainBuildingMenu;
        Tab *barnMenu;
        Tab *barrackMenu;
        Tab *hospitalMenu;
        Tab *homeMenu;
        Tab *marketMenu;
        Tab *quarryMenu;
        Tab *siderurgyMenu;
        Tab *schoolMenu;
        Tab *towerMenu;
        Tab *wallMenu;
        Tab *workshopMenu;

        Button *buttonQuit;
        
        Button *buttonBarn;
        Button *buttonBarrack;
        Button *buttonHospital;
        Button *buttonHome;
        Button *buttonMarket;
        Button *buttonQuarry;
        Button *buttonSiderurgy;
        Button *buttonSchool;
        Button *buttonTower;
        Button *buttonWall;
        Button *buttonWorkshop;
        
        Button *buttonCloseTab0;
        Button *buttonCloseTab1;
        Button *buttonCloseTab2;
        Button *buttonCloseTab3;
        Button *buttonCloseTab4;
        Button *buttonCloseTab5;
        Button *buttonCloseTab6;
        Button *buttonCloseTab7;
        Button *buttonCloseTab8;
        Button *buttonCloseTab9;
        Button *buttonCloseTab10;
        Button *buttonCloseTab11;

        Button *createTroop1;
        Button *createTroop2;
        Button *createTroop3;
};

#endif