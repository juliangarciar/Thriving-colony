#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "Enumeration.h"

using namespace irr;

Hud::Hud() {
    //Los dos botones iniciales
    //buttonBuilding = new Button(Rect2D<int>(700, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonQuit = new Button(Rect2D<int>(1100, 50, 100, 30), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
    //Los dos botones iniciales

    buttonSchool = new Button(Rect2D<int>(0, 0, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON, L"School", L"Add a new Building");
    buttonMarket = new Button(Rect2D<int>(0, 60, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON, L"Market", L"Add a new Building");
    buttonHospital = new Button(Rect2D<int>(0, 120, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON, L"Hospital", L"Add a new Building");
    buttonSiderurgy = new Button(Rect2D<int>(0, 180, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON, L"Siderurgy", L"Add a new Building");
    buttonQuarry = new Button(Rect2D<int>(0, 240, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON, L"Quarry", L"Add a new Building");
    buttonHome = new Button(Rect2D<int>(0, 300, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON, L"Home", L"Add a new Building");
    buttonBarrack = new Button(Rect2D<int>(0, 360, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON, L"Barrack", L"Add a new Building");
    buttonBarn = new Button(Rect2D<int>(0, 420, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON, L"Barn", L"Add a new Building");
    buttonWorkshop = new Button(Rect2D<int>(0, 480, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON, L"Workshop", L"Add a new Building");
    buttonWall = new Button(Rect2D<int>(0, 540, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON, L"Wall", L"Add a new Building");
    buttonTower = new Button(Rect2D<int>(0, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON, L"Tower", L"Add a new Building");

    createTroop1 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_1_BUTTON, L"Crear tropa 1", L"Probando");
    createTroop2 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_2_BUTTON, L"Crear tropa 2", L"Probando");
    createTroop3 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_3_BUTTON, L"Crear tropa 3", L"Probando");

    buttonCloseTab1 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab2 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab3 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");

    tabs = new Panel(Rect2D<int>(300, 300, 400, 200), 11);
    barrackMenu = tabs->addTab(L"Barrack", 1);
    barnMenu = tabs->addTab(L"Barn", 2);
    workshopMenu = tabs->addTab(L"Workshop", 3); 

    barrackMenu->addChild(buttonCloseTab1);
    barnMenu->addChild(buttonCloseTab2);
    workshopMenu->addChild(buttonCloseTab3);

    barrackMenu->addChild(createTroop1);
    barnMenu->addChild(createTroop2);
    workshopMenu->addChild(createTroop3);

    tabs->disable();
}

Hud::~Hud() {
    //Los dos botones iniciales
    delete buttonQuit;

    //Los botones edificios
    delete buttonSchool;
    delete buttonMarket;
    delete buttonHospital;
    delete buttonSiderurgy;
    delete buttonQuarry;
    delete buttonHome;
    delete buttonBarrack;
    delete buttonBarn;
    delete buttonWorkshop;
    delete buttonWall;
    delete buttonTower;

    delete tabs;
    delete barrackMenu;
    delete barnMenu;
    delete workshopMenu;

    delete buttonCloseTab1;
    delete buttonCloseTab2;
    delete buttonCloseTab3;

    delete createTroop1;
    delete createTroop2;
    delete createTroop3;
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
        //Los dos botones iniciales
        case Enumeration::idGUI::GUI_ID_BUILDING_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::House);
        break;
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g->getWindow()->getDevice()->closeDevice();
        break;
        //Los dos botones iniciales
        //Los botones nuevos de cada edificio
        case Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::School);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Market);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Hospital);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Quarry);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::House);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Barrack);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Barn);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Workshop);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Wall);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON:
			Human::getInstance() -> getBuildings() -> setBuildingMode(Enumeration::BuildingType::Tower);
        break;
        //Los botones nuevos de cada edificio
        case Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON:
            tabs->disable();
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_TROOP_1_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(200, 200, 200);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Melee;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                Human::getInstance() -> getUnits() -> createTroop(vectorData, unitData);
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_TROOP_2_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                Human::getInstance() -> getUnits() -> createTroop(vectorData, unitData);
            }
        break;
        //break;
    }
}