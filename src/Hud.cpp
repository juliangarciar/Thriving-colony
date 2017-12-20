#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "Enumeration.h"

using namespace irr;

Hud::Hud() {
    //Los dos botones iniciales
    buttonBuilding = new Button(Rect2D<int>(700, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILDING_BUTTON, L"New Building", L"Add a new Building");
    buttonQuit = new Button(Rect2D<int>(950, 600, 200, 60), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");
    //Los dos botones iniciales

    buttonSchool = new Button(Rect2D<int>(0, 0, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON, L"School", L"Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonMarket = new Button(Rect2D<int>(0, 60, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON, L"Market", L"Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonHospital = new Button(Rect2D<int>(0, 120, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON, L"Hospital", L"Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonSiderurgy = new Button(Rect2D<int>(0, 180, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON, L"Siderurgy", L"Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonQuarry = new Button(Rect2D<int>(0, 240, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON, L"Quarry", L"Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonHome = new Button(Rect2D<int>(0, 300, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON, L"Home", L"Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonBarrack = new Button(Rect2D<int>(0, 360, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON, L"Barrack", L"Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonBarn = new Button(Rect2D<int>(0, 420, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON, L"Barn", L"Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonWorkshop = new Button(Rect2D<int>(0, 480, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON, L"Workshop", L"Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonWall = new Button(Rect2D<int>(0, 540, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON, L"Wall", L"Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonTower = new Button(Rect2D<int>(0, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON, L"Tower", L"Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");

    createTroop1 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_1_BUTTON, L"Crear tropa 1", L"Probando");
    createTroop2 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_2_BUTTON, L"Crear tropa 2", L"Probando");

    buttonCloseTab1 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab2 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");

    tabs = new Panel(Rect2D<int>(300, 300, 400, 200), 11);
    t1 = tabs->addTab(L"Menu del primer edificio", 1);
    t2 = tabs->addTab(L"Menu del segundo edificio", 2);

    t1->addChild(buttonCloseTab1);
    t2->addChild(buttonCloseTab2);

    t1->addChild(createTroop1);
    t2->addChild(createTroop2);

    tabs->disable();
}

Hud::~Hud() {
    //Los dos botones iniciales
    delete buttonBuilding;
    delete buttonQuit;
    //Los dos botones iniciales
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