#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "Enumeration.h"

using namespace irr;

Hud::Hud() {
    //Le botone iniciale
    buttonQuit = new Button(Rect2D<int>(1100, 50, 100, 30), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");

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
/*
    createTroop1 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_1_BUTTON, L"Crear tropa 1", L"Probando");
    createTroop2 = new Button(Rect2D<int>(10, 10, 100, 30), Enumeration::idGUI::GUI_ID_CREATE_TROOP_2_BUTTON, L"Crear tropa 2", L"Probando");
*/
    buttonCloseTab0 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab1 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab2 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab3 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab4 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab5 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab6 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab7 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab8 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab9 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab10 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
    buttonCloseTab11 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");

    createMelee = new Button(Rect2D<int>(10, 10, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON, L"Crear tropa a pie. Ataque cuerpo a cuerpo.", L"Probando");
    createRanged = new Button(Rect2D<int>(10, 50, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON, L"Crear tropa a pie. Ataque a distancia.", L"Probando");
    createMountedMelee = new Button(Rect2D<int>(10, 10, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON, L"Crear tropa montada. Ataque cuerpo a cuerpo.", L"Probando");
    createMountedRanged = new Button(Rect2D<int>(10, 50, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON, L"Crear tropa montada. Ataque a distancia.", L"Probando");
    createMonster = new Button(Rect2D<int>(10, 90, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON, L"Crear ente.", L"Probando");
    createMachine = new Button(Rect2D<int>(10, 10, 200, 30), Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON, L"Crear maquina de asedio.", L"Probando");

    tabs = new Panel(Rect2D<int>(300, 300, 400, 200), 11);

    mainBuildingMenu = tabs->addTab(L"Main Building", Enumeration::BuildingType::MainBuilding);
    barnMenu = tabs->addTab(L"Barn", Enumeration::BuildingType::Barn);
    barrackMenu = tabs->addTab(L"Barrack", Enumeration::BuildingType::Barrack);
    hospitalMenu = tabs->addTab(L"Hospital", Enumeration::BuildingType::Hospital);
    homeMenu = tabs->addTab(L"Home", Enumeration::BuildingType::House);
    marketMenu = tabs->addTab(L"Market", Enumeration::BuildingType::Market); 
    quarryMenu = tabs->addTab(L"Quarry", Enumeration::BuildingType::Quarry); 
    siderurgyMenu = tabs->addTab(L"Siderurgy", Enumeration::BuildingType::Siderurgy);
    schoolMenu = tabs->addTab(L"School", Enumeration::BuildingType::School);
    towerMenu = tabs->addTab(L"Tower", Enumeration::BuildingType::Tower); 
    wallMenu = tabs->addTab(L"Wall", Enumeration::BuildingType::Wall); 
    workshopMenu = tabs->addTab(L"Workshop", Enumeration::BuildingType::Workshop); 

    mainBuildingMenu->addChild(buttonCloseTab0);
    barnMenu->addChild(buttonCloseTab1);
    barrackMenu->addChild(buttonCloseTab2);
    hospitalMenu->addChild(buttonCloseTab3);
    homeMenu->addChild(buttonCloseTab4);
    marketMenu->addChild(buttonCloseTab5);
    quarryMenu->addChild(buttonCloseTab6);
    siderurgyMenu->addChild(buttonCloseTab7);
    schoolMenu->addChild(buttonCloseTab8);
    towerMenu->addChild(buttonCloseTab9);
    wallMenu->addChild(buttonCloseTab10);
    workshopMenu->addChild(buttonCloseTab11);

    barrackMenu->addChild(createMelee);
    barrackMenu->addChild(createRanged);
    barnMenu->addChild(createMountedMelee);
    barnMenu->addChild(createMountedRanged);
    barnMenu->addChild(createMonster);
    workshopMenu->addChild(createMachine);

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
    
    delete mainBuildingMenu;
    delete barnMenu;
    delete barrackMenu;
    delete hospitalMenu;
    delete homeMenu;
    delete marketMenu;
    delete quarryMenu;
    delete siderurgyMenu;
    delete schoolMenu;
    delete towerMenu;
    delete wallMenu;
    delete workshopMenu;

    delete buttonCloseTab0;
    delete buttonCloseTab1;
    delete buttonCloseTab2;
    delete buttonCloseTab3;
    delete buttonCloseTab4;
    delete buttonCloseTab5;
    delete buttonCloseTab6;
    delete buttonCloseTab7;
    delete buttonCloseTab8;
    delete buttonCloseTab9;
    delete buttonCloseTab10;
    delete buttonCloseTab11;

    delete createMelee;
    delete createRanged;
    delete createMountedMelee;
    delete createMountedRanged;
    delete createMonster;
    delete createMachine;
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
        //Le botone iniciale
        case Enumeration::idGUI::GUI_ID_QUIT_BUTTON:
            g->getWindow()->getDevice()->closeDevice();
        break;
        //Los botones nuevos de cada edificio
        case Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::School);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Market);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Hospital);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Quarry);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::House);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barrack);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barn);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Workshop);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Wall);
        break;
        case Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON:
			Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Tower);
        break;
        //Los botones de cada tab
        case Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON:
            tabs->disable();
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(200, 200, 200);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Melee;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardM;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
            }
        break;
    }
}