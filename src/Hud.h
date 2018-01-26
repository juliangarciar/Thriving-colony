#ifndef HUD_H
#define HUD_H

#include <irrlicht.h>
#include <GraphicEngine/Vector2.h>
#include <GraphicEngine/Vector3.h>
#include <GUIEngine/Rect2D.h>
#include <GUIEngine/TextBox.h>
#include <GUIEngine/Button.h>
#include <GUIEngine/TabPanel.h>
#include <GUIEngine/Tab.h>
#include <GUIEngine/Panel.h>
#include <GUIEngine/Label.h>
#include <IOEngine/Keyboard.h>
#include <IOEngine/Mouse.h>

using namespace irr;
       
static TextBox *warningText = 0;

class Hud {
    
    public:
        Hud();
        ~Hud();

        void addTab(int id, int type);

        void showPopup();
        void showPopup(int tabId);
        void hidePopup();

        void setHUDEvents();

        void update();
        void updatePositions();

        static void drawWarning();
        static void deleteWarning();
    private:
        std::vector<int> *menuIDs;
        std::vector<Button*> *buttons;

        Button *buttonQuit;

        Panel *buildingsPanel;

        Panel *generalPanel;
        Panel *servicePanel;
        Panel *militaryPanel;
        Panel *resourcePanel;
        Panel *defensePanel;

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
        Button *buttonExpandTerrain;
        Button *buttonOpenPanel;
        
        Label *resourceText;
        TextBox *iaResourceText;

        

        Panel *tabContainer;
        TabPanel *tabs;

        float updateTimer;
        float deleteTextTimer;

/*
        Text *hallTroopText;
        //ListBox *hallTroopList;

        //ToDo: mejorar*/
};

#endif