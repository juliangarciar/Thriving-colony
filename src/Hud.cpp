#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>

using namespace irr;

Hud::Hud() {
    //Le botone iniciale
    buttonQuit = new Button(Rect2D<int>(1100, 50, 100, 30), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");

    //Los demas botones iniciales
    buttonBarn = new Button(Rect2D<int>(0, 0, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON, L"Barn", L"Add a new Building");
    buttonBarrack = new Button(Rect2D<int>(0, 60, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON, L"Barrack", L"Add a new Building");
    buttonHospital = new Button(Rect2D<int>(0, 120, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON, L"Hospital", L"Add a new Building");
    buttonHome = new Button(Rect2D<int>(0, 180, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON, L"Home", L"Add a new Building");
    buttonMarket = new Button(Rect2D<int>(0, 240, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON, L"Market", L"Add a new Building");
    buttonQuarry = new Button(Rect2D<int>(0, 300, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON, L"Quarry", L"Add a new Building");
    buttonSiderurgy = new Button(Rect2D<int>(0, 360, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON, L"Siderurgy", L"Add a new Building");
    buttonSchool = new Button(Rect2D<int>(0, 420, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON, L"School", L"Add a new Building");
    buttonTower = new Button(Rect2D<int>(0, 480, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON, L"Tower", L"Add a new Building");
    buttonWall = new Button(Rect2D<int>(0, 540, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON, L"Wall", L"Add a new Building");
    buttonWorkshop = new Button(Rect2D<int>(0, 600, 200, 60), Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON, L"Workshop", L"Add a new Building");

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

    tabs = new TabPanel(Rect2D<int>(300, 300, 400, 200), 11);

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

    //ToDo
    hallTroopText = new Text(Rect2D<int>(20, 10, 100, 15), L"Tropas en el ayuntamiento");
    mainBuildingMenu->addChild(hallTroopText);
    hallTroopList = new ListBox(Rect2D<int>(10, 40, 350, 150));
    mainBuildingMenu->addChild(hallTroopList);
    buttonDeployTroops = new Button(Rect2D<int>(120, 10, 100, 20), Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON, L"Deploy selected troop", L"Deploy a troop");
    mainBuildingMenu->addChild(buttonDeployTroops);

    tabs->disable();

    updateTimer = 0.5;
    resourceText = new Text(Rect2D<int>(200, 0, 100, 55), L"Hola mundo", true);
    // Solo de debug
    iaResourceText = new Text(Rect2D<int>(300, 0, 100, 55), L"Hola mundo", true);
    
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

    delete hallTroopText;
    delete hallTroopList;
    delete buttonDeployTroops;

    delete resourceText;
    delete iaResourceText;
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
                hallTroopList->addItem(L"Tropa melee a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
                hallTroopList->addItem(L"Tropa rango a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
                hallTroopList->addItem(L"Tropa melee en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
                hallTroopList->addItem(L"Tropa rango en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
                hallTroopList->addItem(L"Ente");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON:
            {
                Vector3<float> *vectorData = new Vector3<float>(300, 300, 300);
                Enumeration::UnitType unitData;
                unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                Human::getInstance() -> getUnitManager() -> createTroop(vectorData, unitData);
                hallTroopList->addItem(L"Maquina de guerra 1");
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON:
            {
                int index = hallTroopList->getSelected();
                if (index >= 0){
                    hallTroopList->removeItem(index);
                    Human::getInstance()->getUnitManager()->deployTroop(index);
                }
            }
        break;
    }
}

void Hud::update() {
    if (updateTimer <= 0) {
        //ToDo: añadir los metodos de getmetalamount y getcrystalamount
        std::wstringstream os;
        os << L"Player resources:\n" << "Metal: " << std::to_wstring(100) << "\nCrystal: " << std::to_wstring(100) << "\nCitizens: " << std::to_wstring(Human::getInstance() -> getCitizens()) << "\nHappiness: " << std::to_wstring(Human::getInstance() -> getHappiness());
        resourceText -> setText(os.str().c_str());
        std::wstringstream iaos;
        iaos << L"IA resources:\n" << "Metal: " << std::to_wstring(100) << "\nCrystal: " << std::to_wstring(100) << "\nCitizens: " << std::to_wstring(IA::getInstance() -> getCitizens()) << "\nHappiness: " << std::to_wstring(IA::getInstance() -> getHappiness());
        iaResourceText -> setText(iaos.str().c_str());
        updateTimer = 0.5;
    } else {
        updateTimer -= Window::Instance() ->getDeltaTime();
    }
}