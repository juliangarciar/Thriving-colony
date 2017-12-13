#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "Enumeration.h"

using namespace irr;

Hud::Hud() {
<<<<<<< HEAD
    buttonBuilding = new Button(Rect2D<int>(700, 600, 200, 60), GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonBuilding = new Button(Rect2D<int>(950, 600, 200, 60), GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
    buttonBuilding = new Button(Rect2D<int>(450, 600, 200, 60), GUI_ID_UNIT_BUTTON, L"New unit", L"Add a new unit");
=======
    buttonBuilding = new Button(Rect2D<int>(700, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonQuit = new Button(Rect2D<int>(950, 600, 200, 60), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
>>>>>>> master
}

Hud::~Hud() {
    delete buttonBuilding;
}

void Hud::getHUDEvents(){
    Game *g = Game::Instance();
    int id = g->getIO()->getGUIClickedID();
    switch(id){
<<<<<<< HEAD
        case GUI_ID_BUILDING_BUTTON:
			g->getGameState()->getBuildingManager()->setBuildingMode(true);
            break;
        case GUI_ID_QUIT_BUTTON:
=======
        case Enumeration::idGUI::GUI_ID_BUILDING_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(true);
        break;
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
>>>>>>> master
            g->getWindow()->getDevice()->closeDevice();
            break;
        case GUI_ID_UNIT_BUTTON:
            //g->getGameState()->getUnitManager()->setUnitMode(true);
            break;
        //break;
    }
}