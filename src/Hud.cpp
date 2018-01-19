#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>

using namespace irr;

Text *Hud::warningText = 0;//new Text(Rect2D<int>(200, 60, 50, 20), L"Edificio construido", true);

Hud::Hud() {
    //Le botone iniciale
    //buttonQuit = new Button(Rect2D<int>(1150, 20, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_QUIT_BUTTON, L"Quit", L"Quit Game");

    buttonBarn = new Button(Rect2D<int>(746, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_BARN_BUTTON, L"Barn", L"Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonBarrack = new Button(Rect2D<int>(642, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_BARRACK_BUTTON, L"Barrack", L"Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonHome = new Button(Rect2D<int>(538, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_HOME_BUTTON, L"Home", L"Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonHospital = new Button(Rect2D<int>(226, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_HOSPITAL_BUTTON, L"Hospital", L"Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonMarket = new Button(Rect2D<int>(122, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_MARKET_BUTTON, L"Market", L"Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonQuarry = new Button(Rect2D<int>(434, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_QUARRY_BUTTON, L"Quarry", L"Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonSchool = new Button(Rect2D<int>(18, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_SCHOOL_BUTTON, L"School", L"Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonSiderurgy = new Button(Rect2D<int>(330, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_SIDERURGY_BUTTON, L"Siderurgy", L"Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonTower = new Button(Rect2D<int>(1058, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_TOWER_BUTTON, L"Tower", L"Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");
    buttonWall = new Button(Rect2D<int>(954, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_WALL_BUTTON, L"Wall", L"Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonWorkshop = new Button(Rect2D<int>(850, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_BUILD_WORKSHOP_BUTTON, L"Workshop", L"Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonExpandTerrain = new Button(Rect2D<int>(1162, 680, 100, 30).getFixed(), Enumeration::idGUI::GUI_ID_EXPAND_TERRAIN_BUTTON, L"Expand terrain", L"Purchase a terrain expansion that will allow you to build a bigger city.\n Metal cost: 500.");

    menus = new std::vector<Tab*>();
    buttons = new std::vector<Button*>();

    tabs = new TabPanel(Rect2D<int>(300, 300, 400, 200).getFixed(), 0);
    tabs->disable();

    //this->addTab(0, Enumeration::BuildingType::MainBuilding);
    
    updateTimer = 0.5;
    resourceText = new Text(Rect2D<int>(0, 0, 100, 91).getFixed(), L"Hola mundo", true);
    // Solo de debug
    iaResourceText = new Text(Rect2D<int>(100, 0, 100, 91).getFixed(), L"Hola mundo", true);

    hallTroopList = new ListBox(Rect2D<int>(10, 40, 350, 150).getFixed());

    warningText = new Text(Rect2D<int>(200, 100, 100, 10).getFixed(), L"Edificio construido", true);
    //warningText -> disable();
    deleteWarning();

    deleteTextTimer = 0;
}

Hud::~Hud() {
    //Los dos botones iniciales
    //delete buttonQuit;

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
    delete buttonExpandTerrain;

    delete tabs;

    delete hallTroopText;
    delete hallTroopList;
    
    delete resourceText;
    delete iaResourceText;

    delete warningText;
}

void Hud::addTab(int id, int type){
    switch (type) {
        case Enumeration::BuildingType::MainBuilding:
        {
            Tab *t = tabs->addTab(L"Main Building", id);
            menus -> push_back(t);

            Button *b = new Button(Rect2D<int>(350, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(100, 10, 100, 20).getFixed(), Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON, L"Deploy selected troop", L"Deploy a troop");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(200, 10, 75, 20), Enumeration::idGUI::GUI_ID_DEPLOY_ALL_TROOPS_BUTTON, L"Deploy all troops", L"Deploy all troops");
            t -> addChild(b);
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(275, 10, 75, 20), Enumeration::idGUI::GUI_ID_RETRACT_ALL_TROOPS_BUTTON, L"Retract troops", L"Retract troops");
            t -> addChild(b);
            buttons -> push_back(b);

            hallTroopText = new Text(Rect2D<int>(20, 10, 100, 15).getFixed(), L"Tropas en el ayuntamiento");
            t->addChild(hallTroopText);
            t->addChild(hallTroopList);
        }
        break;
        case Enumeration::BuildingType::Barn:
        {
            Tab *t = tabs->addTab(L"Barn", id);
            menus->push_back(t);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON, L"Crear tropa montada. Ataque cuerpo a cuerpo.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 50, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON, L"Crear tropa montada. Ataque a distancia.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 90, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON, L"Crear ente.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
        }
        break;
        case Enumeration::BuildingType::Barrack:
        {
            Tab *t = tabs->addTab(L"Barrack", id);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON, L"Crear tropa a pie. Ataque cuerpo a cuerpo.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 50, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON, L"Crear tropa a pie. Ataque a distancia.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
        }
        break;
        case Enumeration::BuildingType::Workshop:
        {
            Tab *t = tabs->addTab(L"Workshop", id);

            Button *b = new Button(Rect2D<int>(340, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t->addChild(b);
            buttons->push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON, L"Crear maquina de asedio.", L"Probando");
            t->addChild(b);
            buttons->push_back(b);
        }
        break;
        default: break;
    }
}

void Hud::showPopup(int tabId){
    if (tabs->changeActiveTab(tabId))
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
                Enumeration::UnitType unitData = Enumeration::UnitType::StandardM;
                
                //unitData.unitClass = Enumeration::UnitType::Class::Melee;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa melee a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::StandardR;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa rango a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedM;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa melee en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedR;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Tropa rango en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::Idol;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Ente");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::Launcher;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList->addItem(L"Maquina de guerra 1");
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON:
            {
                int index = hallTroopList->getSelected();
                if (index >= 0){
                    hallTroopList->removeItem(index);
                    Human::getInstance()->getUnitManager()->startDeployingTroop(index);
                }
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_ALL_TROOPS_BUTTON:
            {
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::DeployTroopsHuman);
                hallTroopList -> removeAllItems();
            }
        break;
        case Enumeration::idGUI::GUI_ID_RETRACT_ALL_TROOPS_BUTTON:
            {
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::RetractTroopsHuman);
            }
        break;
        case Enumeration::idGUI::GUI_ID_EXPAND_TERRAIN_BUTTON:
			//ToDo: hacer que se expanda el terreno edificable y que el susodicho exista
        break;
    }
}

void Hud::update() {
    float dt = Game::Instance() ->getWindow() -> getDeltaTime();
    if (updateTimer <= 0) {
        //ToDo: añadir los metodos de getmetalamount y getcrystalamount
        std::wstringstream os;
        os << L"Player resources:\n" << "Metal: " << std::to_wstring(Human::getInstance() -> getMetalAmount()) << "\nCrystal: " << std::to_wstring(Human::getInstance() -> getCrystalAmount()) << "\nCitizens: " << std::to_wstring(Human::getInstance() -> getCitizens()) << "\nHappiness: " << std::to_wstring(Human::getInstance() -> getHappiness()) << "\nArmy size: " << std::to_wstring(Human::getInstance() -> getArmySize()) << "\n - Melees: " << std::to_wstring(Human::getInstance() -> getMeleeAmount()) << "\n - Ranged: " << std::to_wstring(Human::getInstance() -> getRangeAmount()) << "\n - Siege: " << std::to_wstring(Human::getInstance() -> getSiegeAmount());
        resourceText -> setText(os.str().c_str());
        std::wstringstream iaos;
        iaos << L"IA resources:\n" << "Metal: " << std::to_wstring(IA::getInstance() -> getMetalAmount()) << "\nCrystal: " << std::to_wstring(IA::getInstance() -> getCrystalAmount()) << "\nCitizens: " << std::to_wstring(IA::getInstance() -> getCitizens()) << "\nHappiness: " << std::to_wstring(IA::getInstance() -> getHappiness()) << "\nArmy size: " << std::to_wstring(IA::getInstance() -> getArmySize()) << "\n - Melees: " << std::to_wstring(IA::getInstance() -> getMeleeAmount()) << "\n - Ranged: " << std::to_wstring(IA::getInstance() -> getRangeAmount()) << "\n - Siege: " << std::to_wstring(IA::getInstance() -> getSiegeAmount());
        iaResourceText -> setText(iaos.str().c_str());
        updateTimer = 0.5;

        
        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DisableText);
    } else {
        updateTimer -= dt;
    }
    
}

void Hud::updatePositions(){
    //buttonQuit -> setPosition(Vector2<int>(1150, 20).getFixed());

    buttonBarn -> setPosition(Vector2<int>(746, 680).getFixed());
    buttonBarrack -> setPosition(Vector2<int>(642, 680).getFixed());
    buttonHospital -> setPosition(Vector2<int>(538, 680).getFixed());
    buttonHome -> setPosition(Vector2<int>(226,680).getFixed());
    buttonMarket -> setPosition(Vector2<int>(122,680).getFixed());
    buttonQuarry -> setPosition(Vector2<int>(434,680).getFixed());
    buttonSiderurgy -> setPosition(Vector2<int>(18,680).getFixed());
    buttonSchool -> setPosition(Vector2<int>(330,680).getFixed()); 
    buttonTower -> setPosition(Vector2<int>(1058,680).getFixed());
    buttonWall -> setPosition(Vector2<int>(954,680).getFixed());
    buttonWorkshop -> setPosition(Vector2<int>(850,680).getFixed());
    buttonExpandTerrain -> setPosition(Vector2<int>(1162,680).getFixed());
}

void Hud::drawWarning() {
    // <<  "¡Se ha construido un edificio!" << std::endl;
    warningText -> enable();
}

void Hud::deleteWarning() {
    //std::cout << "¡Se ha borrado un texto que dice que se ha dibujado un texto!" << std::endl;
    warningText -> disable();
}

/*hospitalMenu = tabs->addTab(L"Hospital", Enumeration::BuildingType::Hospital);
hospitalMenu->addChild(buttonCloseTab3);
homeMenu = tabs->addTab(L"Home", Enumeration::BuildingType::House);
homeMenu->addChild(buttonCloseTab4);
marketMenu = tabs->addTab(L"Market", Enumeration::BuildingType::Market);
marketMenu->addChild(buttonCloseTab5);
quarryMenu = tabs->addTab(L"Quarry", Enumeration::BuildingType::Quarry);
quarryMenu->addChild(buttonCloseTab6);
siderurgyMenu = tabs->addTab(L"Siderurgy", Enumeration::BuildingType::Siderurgy);
siderurgyMenu->addChild(buttonCloseTab7);
schoolMenu = tabs->addTab(L"School", Enumeration::BuildingType::School);
schoolMenu->addChild(buttonCloseTab8);
towerMenu = tabs->addTab(L"Tower", Enumeration::BuildingType::Tower);
towerMenu->addChild(buttonCloseTab9);
wallMenu = tabs->addTab(L"Wall", Enumeration::BuildingType::Wall); 
wallMenu->addChild(buttonCloseTab10);
buttonCloseTab3 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab4 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab5 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab6 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab7 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab8 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab9 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab10 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
buttonCloseTab11 = new Button(Rect2D<int>(340, 10, 50, 20), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
*/