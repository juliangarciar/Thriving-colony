#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>

using namespace irr;

//warningText = 0;//new Text(Rect2D<int>(200, 60, 50, 20), L"Edificio construido", true);

Hud::Hud() {
    updateTimer = 0.5;
    deleteTextTimer = 0;

    menuIDs = new std::vector<int>();
    buttons = new std::vector<Button*> ();
    // Building buttons panel
    buildingsPanel = new Panel("Buildings");
    buildingsPanel->setPosition(Vector2<int>(575, 546).getFixed());
    //Le botone iniciale
    buttonQuit = new Button("Quit");

    // General
    generalPanel = new Panel(buildingsPanel, "General functions");
    generalPanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonExpandTerrain = new Button(generalPanel, "Expand terrain");
    buttonOpenPanel = new Button(generalPanel, "Open Panel");

    buttonQuit->setPosition(Vector2<int>(30, 30));
    buttonOpenPanel->setPosition(Vector2<int>(100, 20));

    generalPanel -> setVerticalAlignment();

    // Resources
    resourcePanel = new Panel(buildingsPanel, "Resource buildings");
    resourcePanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonHome = new Button(resourcePanel, "Home");
    buttonSiderurgy = new Button(resourcePanel, "Siderurgy");
    buttonQuarry = new Button(resourcePanel, "Quarry");

    resourcePanel ->setVerticalAlignment();
    // Services
    servicePanel = new Panel(buildingsPanel, "Service buildings");
    servicePanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonSchool = new Button(servicePanel, "School");
    buttonMarket = new Button(servicePanel, "Market");
    buttonHospital = new Button(servicePanel, "Hospital");

    servicePanel -> setVerticalAlignment();
    // Military
    militaryPanel = new Panel(buildingsPanel, "Military buildings");
    militaryPanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonBarrack = new Button(militaryPanel, "Barrack");
    buttonBarn = new Button(militaryPanel, "Barn");
    buttonWorkshop = new Button(militaryPanel, "Workshop");

    militaryPanel -> setVerticalAlignment();
    // Defense
    defensePanel = new Panel(buildingsPanel, "Defensive buildings");
    defensePanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonTower = new Button(defensePanel, "Tower");
    buttonWall = new Button(defensePanel, "Wall");

    defensePanel -> setVerticalAlignment();

    //buildingsPanel -> center();

    buttonBarn->setTooltip("Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonBarrack->setTooltip("Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonHome->setTooltip("Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonHospital->setTooltip("Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonMarket->setTooltip("Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonQuarry->setTooltip("Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonSchool->setTooltip("Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonSiderurgy->setTooltip("Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonTower->setTooltip("Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");
    buttonWall->setTooltip("Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonWorkshop->setTooltip("Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonExpandTerrain->setTooltip("Purchase a terrain expansion that will allow you to build a bigger city.\n Metal cost: 500.");
    buttonOpenPanel->setTooltip("Open your panel to manage your city.");

    // Solo de debug
    resourceText = new Label("Player");
    iaResourceText = new TextBox("IA");
    warningText = new TextBox("Edificio construido");

    resourceText->setPosition(Vector2<int>(0,0).getFixed());
    iaResourceText->setPosition(Vector2<int>(1150,0).getFixed());
    warningText->setPosition(Vector2<int>(1000,650).getFixed());

    resourceText -> setSize(Vector2<int>(100,100));

    deleteWarning();
    
    tabContainer = new Panel("Tabs");
    tabContainer -> setGroupLayout();
    tabs = new TabPanel(tabContainer);
    tabContainer->center();
    tabContainer->hide();
}

Hud::~Hud() {
    delete menuIDs;

    delete buildingsPanel;
    delete resourcePanel;
    delete servicePanel;
    delete militaryPanel;
    delete defensePanel;

    //Los dos botones iniciales
    delete buttonQuit;
    delete buttonOpenPanel;

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

    delete resourceText;
    delete iaResourceText;

    delete tabContainer;
    delete tabs;

   /* 
    delete warningText; //Es estatico asi que no se yo...
    delete hallTroopText;
    delete hallTroopList;*/
}

void Hud::addTab(int id, int type){
    switch (type) {
        case Enumeration::BuildingType::MainBuilding:
        {
            Tab *t = tabs->createTab("Main Building", id);
            menuIDs -> push_back(id);

            Button *b = new Button(t, "Close");
            b->setTooltip("Cerrar popup");
            b->setCallback([&] {
                tabContainer -> hide();
            });
            buttons -> push_back(b);

            tabs->refreshLayout();
            tabs->changeActiveTab(0);

            /*
            b = new Button(Rect2D<int>(100, 10, 100, 20).getFixed(), Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON, L"Deploy selected troop", L"Deploy a troop");
            t -> addChild(b);
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(200, 10, 75, 20), Enumeration::idGUI::GUI_ID_DEPLOY_ALL_TROOPS_BUTTON, L"Deploy all troops", L"Deploy all troops");
            t -> addChild(b);
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(275, 10, 75, 20), Enumeration::idGUI::GUI_ID_RETRACT_ALL_TROOPS_BUTTON, L"Retract troops", L"Retract troops");
            t -> addChild(b);
            buttons -> push_back(b);

            hallTroopText = new Text(Rect2D<int>(20, 10, 100, 15).getFixed(), L"Tropas en el ayuntamiento");
            t -> addChild(hallTroopText);
            hallTroopList = new ListBox(Rect2D<int>(10, 40, 350, 150).getFixed());
            t -> addChild(hallTroopList);*/
        }
        break;
        case Enumeration::BuildingType::Barn:
        {
            Tab *t = tabs -> createTab("Barn", id);
            menuIDs -> push_back(id);

            tabs->refreshLayout();
            tabs->changeActiveTab(0);

            /*Button *b = new Button(Rect2D<int>(340, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t -> addChild(b);
            tabs -> disable();
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON, L"Crear tropa montada. Ataque cuerpo a cuerpo.", L"Probando");
            t -> addChild(b);
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(10, 50, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON, L"Crear tropa montada. Ataque a distancia.", L"Probando");
            t -> addChild(b);
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(10, 90, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON, L"Crear ente.", L"Probando");
            t -> addChild(b);
            buttons -> push_back(b);*/
        }
        break;
        case Enumeration::BuildingType::Barrack:
        {
            Tab *t = tabs -> createTab("Barrack", id);
            menuIDs -> push_back(id);

            tabs->refreshLayout();
            tabs->changeActiveTab(0);

            /*Button *b = new Button(Rect2D<int>(340, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t -> addChild(b);
            tabs -> disable();
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON, L"Crear tropa a pie. Ataque cuerpo a cuerpo.", L"Probando");
            t -> addChild(b);
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(10, 50, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON, L"Crear tropa a pie. Ataque a distancia.", L"Probando");
            t -> addChild(b);
            buttons -> push_back(b);*/
        }
        break;
        case Enumeration::BuildingType::Workshop:
        {
            Tab *t = tabs -> createTab("Workshop", id);
            menuIDs -> push_back(id);

            tabs->refreshLayout();
            tabs->changeActiveTab(0);

            /*Button *b = new Button(Rect2D<int>(340, 10, 50, 20).getFixed(), Enumeration::idGUI::GUI_ID_CLOSE_PANEL_BUTTON, L"Cerrar", L"Cerrar popup");
            t -> addChild(b);
            tabs -> disable();
            buttons -> push_back(b);
            b = new Button(Rect2D<int>(10, 10, 200, 30).getFixed(), Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON, L"Crear maquina de asedio.", L"Probando");
            t -> addChild(b);
            buttons -> push_back(b);*/
        }
        break;
        default: break;
    }
}

void Hud::showPopup(){
    tabContainer -> show();
}

void Hud::showPopup(int tabId){
    /*if (tabs -> changeActiveTab(tabId))
        tabs -> enable();*/
}

void Hud::hidePopup(){
    tabContainer -> hide();
}

void Hud::setHUDEvents(){
    //Le botone iniciale
    buttonQuit->setCallback([]{
        Game::Instance() -> getWindow() -> close();
    });

    buttonOpenPanel->setCallback([]{
        Game::Instance()->getGameState()->getHud()->showPopup();
    });

    buttonBarn->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barn);
    });

    buttonBarrack->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barrack);
    });

    buttonHome->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::House);
    });

    buttonHospital->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Hospital);
    });

    buttonMarket->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Market);
    });

    buttonQuarry->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Quarry);
    });

    buttonSchool->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::School);
    });

    buttonSiderurgy->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
    });

    buttonTower->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Tower);
    });

    buttonWall->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Wall);
    });

    buttonWorkshop->setCallback([]{
        Human::getInstance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Workshop);
    });

    buttonExpandTerrain->setCallback([]{
        //ToDo: hacer que se expanda el terreno edificable y que el susodicho exista
    });



    /*Game *g = Game::Instance();
    int id = g -> getIO() -> getGUIClickedID();

    switch(id) {
        //Los botones de cada tab
        case Enumeration::idGUI::GUI_ID_CREATE_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::StandardM;
                
                //unitData.unitClass = Enumeration::UnitType::Class::Melee;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa melee a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::StandardR;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::StandardR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa rango a pie");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_MELEE_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedM;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa melee en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MOUNTED_RANGED_TROOP_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::AdvancedR;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Tropa rango en montura");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MONSTER_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::Idol;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedM;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Ente");
            }
        break;
        case Enumeration::idGUI::GUI_ID_CREATE_MACHINE_BUTTON:
            {
                Enumeration::UnitType unitData = Enumeration::UnitType::Launcher;
                //unitData.unitClass = Enumeration::UnitType::Class::Ranged;
                //unitData.unitSubClass = Enumeration::UnitType::SubClass::AdvancedR;
                if (Human::getInstance() -> getUnitManager() -> createTroop(unitData))
                    hallTroopList -> addItem(L"Maquina de guerra 1");
            }
        break;
        case Enumeration::idGUI::GUI_ID_DEPLOY_TROOPS_BUTTON:
            {
                int index = hallTroopList -> getSelected();
                if (index >= 0) {
                    hallTroopList -> removeItem(index);
                    Human::getInstance() -> getUnitManager() -> startDeployingTroop(index);
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
    }*/
}

void Hud::update() {
    float dt = Game::Instance()  -> getWindow() -> getDeltaTime();
    if (updateTimer <= 0) {
        
        std::stringstream os;
        os << "Player resources:" << 
        "Metal: " << std::to_string(Human::getInstance() -> getMetalAmount()) << 
        "Crystal: " << std::to_string(Human::getInstance() -> getCrystalAmount()) << 
        "Citizens: " << std::to_string(Human::getInstance() -> getCitizens()) << 
        "Happiness: " << std::to_string(Human::getInstance() -> getHappiness()) << 
        "City level: "<< std::to_string(Human::getInstance() -> getCityLevel()) << 
        "Army size: " << std::to_string(Human::getInstance() -> getArmySize()) << 
        " - Melees: " << std::to_string(Human::getInstance() -> getMeleeAmount()) << 
        " - Ranged: " << std::to_string(Human::getInstance() -> getRangeAmount()) << 
        " - Siege: " << std::to_string(Human::getInstance() -> getSiegeAmount());
        resourceText -> setLabel(os.str());

        std::stringstream iaos;
        iaos << "IA resources:" << 
        "Metal: " << std::to_string(IA::getInstance() -> getMetalAmount()) << 
        "Crystal: " << std::to_string(IA::getInstance() -> getCrystalAmount()) << 
        "Citizens: " << std::to_string(IA::getInstance() -> getCitizens()) << 
        "Happiness: " << std::to_string(IA::getInstance() -> getHappiness()) << 
        "City level: "<< std::to_string(IA::getInstance() -> getCityLevel()) << 
        "Army size: " << std::to_string(IA::getInstance() -> getArmySize()) << 
        " - Melees: " << std::to_string(IA::getInstance() -> getMeleeAmount()) << 
        " - Ranged: " << std::to_string(IA::getInstance() -> getRangeAmount()) << 
        " - Siege: " << std::to_string(IA::getInstance() -> getSiegeAmount());
        /* << //ToDo: change type
        "Next choice: " << IA::getInstance() -> getNextChoice() << 
        "Behaviour: " << IA::getInstance() -> getChosenBehaviour();*/

        iaResourceText -> setText(iaos.str());

        updateTimer = 0.5;

        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DisableText);
    } else {
        updateTimer -= dt;
    }
}


void Hud::updatePositions() {
    buttonQuit -> setPosition(Vector2<int>(20, 20).getFixed());
    buttonOpenPanel -> setPosition(Vector2<int>(100,20).getFixed());

    buildingsPanel->setPosition(Vector2<int>(20, 640).getFixed());

    resourceText->setPosition(Vector2<int>(1000,0).getFixed());
    iaResourceText->setPosition(Vector2<int>(1150,0).getFixed());
    warningText->setPosition(Vector2<int>(1000,650).getFixed());

    tabContainer->center();
}

void Hud::drawWarning() {
    //std::cout <<  "¡Se ha construido un edificio!" << std::endl;
    warningText -> show();
}

void Hud::deleteWarning() {
    //std::cout << "¡Se ha borrado un texto que dice que se ha dibujado un texto!" << std::endl;
    warningText -> hide();
}

/*hospitalMenu = tabs -> addTab(L"Hospital", Enumeration::BuildingType::Hospital);
hospitalMenu -> addChild(buttonCloseTab3);
homeMenu = tabs -> addTab(L"Home", Enumeration::BuildingType::House);
homeMenu -> addChild(buttonCloseTab4);
marketMenu = tabs -> addTab(L"Market", Enumeration::BuildingType::Market);
marketMenu -> addChild(buttonCloseTab5);
quarryMenu = tabs -> addTab(L"Quarry", Enumeration::BuildingType::Quarry);
quarryMenu -> addChild(buttonCloseTab6);
siderurgyMenu = tabs -> addTab(L"Siderurgy", Enumeration::BuildingType::Siderurgy);
siderurgyMenu -> addChild(buttonCloseTab7);
schoolMenu = tabs -> addTab(L"School", Enumeration::BuildingType::School);
schoolMenu -> addChild(buttonCloseTab8);
towerMenu = tabs -> addTab(L"Tower", Enumeration::BuildingType::Tower);
towerMenu -> addChild(buttonCloseTab9);
wallMenu = tabs -> addTab(L"Wall", Enumeration::BuildingType::Wall); 
wallMenu -> addChild(buttonCloseTab10);
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