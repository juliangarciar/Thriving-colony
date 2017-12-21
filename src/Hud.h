#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/Text.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/TabPanel.h>
#include <GUIEngine/Tab.h>
#include <GUIEngine/ListBox.h>
#include <IOEngine/InputManager.h>
#include <IOEngine/Mouse.h>

using namespace irr;

class Hud {
    
    public:
        Hud();
        ~Hud();

        void addTab(int id, int type);

        void showPopup(int tabId);
        void hidePopup();

        void getHUDEvents();

        void update();
    private:
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
        
        TabPanel *tabs;

        Text *hallTroopText;
        ListBox *hallTroopList;

        //ToDo: mejorar
        std::vector<Tab*> *menus;
        std::vector<Button*> *buttons;
        
        Text *resourceText;
        Text *iaResourceText;

        float updateTimer;
};

#endif