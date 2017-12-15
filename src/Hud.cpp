#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "Enumeration.h"

using namespace irr;

Hud::Hud() {
    buttonBuilding = new Button(Rect2D<int>(700, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonQuit = new Button(Rect2D<int>(950, 600, 200, 60), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");

    buttonCloseTab1 = new Button(Rect2D<int>(10, 10, 200, 60), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab2 = new Button(Rect2D<int>(10, 10, 200, 60), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");

    tabs = new Panel(Rect2D<int>(300, 300, 400, 200), 11);
    t1 = tabs->addTab(L"Menu del primer edificio", 1);
    t2 = tabs->addTab(L"Menu del segundo edificio", 2);

    t1->addChild(buttonCloseTab1);
    t2->addChild(buttonCloseTab2);

    tabs->disable();
}

Hud::~Hud() {
    delete buttonBuilding;
    delete tabs;
    delete t1;
    delete t2;
}

void Hud::showPopup(int tabId){
    tabs->changeActiveTab(tabId);
    tabs->enable();
}

void Hud::hidePopup(){
    tabs->disable();
}

void Hud::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g->getIO()->getGUIClickedID();
    switch(id){
        case Enumeration::idGUI::GUI_ID_BUILDING_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(true);
        break;
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g->getWindow()->getDevice()->closeDevice();
        break;
        case Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON:
            tabs->disable();
        break;
        case Enumeration::idGUI::GUI_ID_UNIT_BUTTON:
            //g->getGameState()->getUnitManager()->setUnitMode(true);
        break;
        //break;
    }
}