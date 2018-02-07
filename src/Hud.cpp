#include "Hud.h"
#include "Game.h"
#include "Human.h"
#include "IA.h"
#include "Enumeration.h"
#include "GraphicEngine/Window.h"

#include <string>
#include <sstream>

using namespace irr;

//warningText = 0;//new Text(Rect2D<int>(200, 60, 50, 20), L"Edificio construido", true);

Hud::Hud() {
    updateTimer = 0.5;
    deleteTextTimer = 0;

    popUpOpen = false;

    buttons = new std::vector<Button*>();

    // Building buttons panel
    buildingsPanel = new Panel("Buildings");
    buildingsPanel->setPosition(Vector2<int>(575, 546).getFixed());

    // General
    generalPanel = new Panel(buildingsPanel, "General functions");
    generalPanel->setPosition(Vector2<int>(20, 640).getFixed());

    buttonExpandTerrain = new Button(generalPanel, "Expand terrain");

    buttonOpenPanel = new Button(generalPanel, "Open Panel");
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
    resourceText = new Label("");
    iaResourceText = new Label("");

    warningText = new TextBox("Edificio construido");

    backgroundText = new TextBox("");
    backgroundText -> setPosition(Vector2<int>(0,0));
    backgroundText -> setSize(Vector2<int>(950,35));

    resourceText->setPosition(Vector2<int>(0,0).getFixed());
    iaResourceText->setPosition(Vector2<int>(0,20).getFixed());
    warningText->setPosition(Vector2<int>(1000,650).getFixed());

    resourceText -> setSize(Vector2<int>(1000,100));
    iaResourceText -> setSize(Vector2<int>(1000,100));

    deleteWarning();
    
    tabContainer = new Panel("Building viewer");
        tabContainer -> setSize(Vector2<int>(350, 280));
        tabContainer -> setGroupLayout();
        tabs = new TabPanel(tabContainer);
        mainBuildingTab = tabs->createTab("Main Building");
        barrackTab = tabs->createTab("Barrack");
        barnTab = tabs->createTab("Barn");
        workshopTab = tabs->createTab("Workshop");

        //MainBuildingTab
        {
            Button *b = new Button(mainBuildingTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });
            buttons -> push_back(b);

            hallTroopList = new ComboBox(mainBuildingTab, {});

            b = new Button(mainBuildingTab, "Deploy selected troop");
            b -> setTooltip("Deploy your selected unit onto the map");
            b -> setCallback([&]{
                int index = hallTroopList -> getSelectedOption();
                if (index >= 0) {
                    hallTroopList -> removeOption(index);
                    Human::getInstance() -> getUnitManager() -> startDeployingTroop(index);
                    Window::Instance()->getGUIEnvironment()->performLayout();
                }
            });
            buttons -> push_back(b);

            b = new Button(mainBuildingTab, "Deploy all troops");
            b -> setTooltip("Deploy all your units onto the map");
            b -> setCallback([&]{
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::DeployTroopsHuman);
            });
            buttons -> push_back(b);

            b = new Button(mainBuildingTab, "Retract all troops");
            b -> setTooltip("Retract your units back into your town hall");
            b -> setCallback([&]{
                Game::Instance() -> getEvents() -> triggerEvent(Enumeration::RetractTroopsHuman);
            });
            buttons -> push_back(b);

            mainBuildingTab->hide();
        }
        //BarrackTab
        {
            Button *b = new Button(barrackTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });
            buttons -> push_back(b);

            barrackEmpty = new Panel(barrackTab, "");
            barrackEmptyLabel = new Label(barrackEmpty, "Este edificio no esta activo aun");

            barrackContent = new Panel(barrackTab, "");
            barrackContent -> setGroupLayout();

            b = new Button(barrackContent, "Create melee footman");
            b -> setTooltip("Create a melee unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardM);
                hallTroopList -> addOption("Melee footman");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            
            b = new Button(barrackContent, "Create ranged footman");
            b -> setTooltip("Create a ranged unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardR);
                hallTroopList -> addOption("Ranged footman");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);

            barrackScroll = new ScrollPanel(barrackContent);
            barrackTroopListPanel = new Panel(barrackScroll, "");

            barrackContent -> hide();
        }
        //BarnTab
        {
            Button *b = new Button(barnTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });
            buttons -> push_back(b);

            barnEmpty = new Panel(barnTab, "");
            barnEmptyLabel = new Label(barnEmpty, "Este edificio no esta activo aun");

            barnContent = new Panel(barnTab, "");
            barnContent -> setGroupLayout();

            b = new Button(barnContent, "Create mounted melee unit");
            b -> setTooltip("Create a melee unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedM);
                hallTroopList -> addOption("Mounted melee unit");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            
            b = new Button(barnContent, "Create mounted ranged unit");
            b -> setTooltip("Create a ranged unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedR);
                hallTroopList -> addOption("Mounted ranged unit");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);

            b = new Button(barnContent, "Create monster");
            b -> setTooltip("Create a overwhelmingly powerful creature to destroy your enemies\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Idol);
                hallTroopList -> addOption("Create monster");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);

            barnScroll = new ScrollPanel(barnContent);
            barnTroopListPanel = new Panel(barnScroll, "");

            barnContent -> hide();
        }
        //Workshop tab
        {
            Button *b = new Button(workshopTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });
            buttons -> push_back(b);

            workshopEmpty = new Panel(workshopTab, "");
            workshopEmptyLabel = new Label(workshopEmpty, "Este edificio no esta activo aun");

            workshopContent = new Panel(workshopTab, "");
            workshopContent -> setGroupLayout();

            b = new Button(workshopContent, "Create ram");
            b -> setTooltip("Create a ram that specializes in destroying buildings\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Desintegrator);
                hallTroopList -> addOption("Ram");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);
            
            b = new Button(workshopContent, "Create catapult");
            b -> setTooltip("Create a catapult that heavy area of damage\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::getInstance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Launcher);
                hallTroopList -> addOption("Catapult");
                Window::Instance()->getGUIEnvironment()->performLayout();
            });
            buttons -> push_back(b);

            workshopScroll = new ScrollPanel(workshopContent);
            workshopTroopListPanel = new Panel(workshopScroll, "");

            workshopContent -> hide();
        }
        tabs->changeActiveTab(0);
    tabContainer->refreshLayout();
    tabContainer->center();
    tabContainer->hide();

    setHUDEvents();
}

Hud::~Hud() {
    delete buildingsPanel;
    delete generalPanel;
    delete resourcePanel;
    delete servicePanel;
    delete militaryPanel;
    delete defensePanel;

    //Le botone iniciale
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

    //Moar
    delete backgroundText;
    delete resourceText;
    delete iaResourceText;

    delete hallTroopList;

    delete tabContainer;
    delete tabs;

    //ToDo: Es estatico asi que no se yo...
    delete warningText; 
}

void Hud::enableTab(Enumeration::BuildingType t){
    switch (t){
        case Enumeration::BuildingType::Barrack:
            barrackEmpty->hide();
            barrackContent->show();
        break;
        case Enumeration::BuildingType::Barn:
            barnEmpty->hide();
            barnContent->show();
        break;
        case Enumeration::BuildingType::Workshop:
            workshopEmpty->hide();
            workshopContent->show();
        break;
        default: break;
    }
    tabContainer->refreshLayout();
}

void Hud::disableTab(Enumeration::BuildingType t){
    switch (t){
        case Enumeration::BuildingType::Barrack:
            barrackEmpty->show();
            barrackContent->hide();
        break;
        case Enumeration::BuildingType::Barn:
            barnEmpty->show();
            barnContent->hide();
        break;
        case Enumeration::BuildingType::Workshop:
            workshopEmpty->show();
            workshopContent->hide();
        break;
        default: break;
    }
    tabContainer->refreshLayout();
}

void Hud::showPopup(){
    tabContainer -> show();
    buttonOpenPanel -> setText("Close Panel");
    popUpOpen = true;
}

void Hud::showPopup(Enumeration::BuildingType t){
    bool show = false;
    switch(t){
        case Enumeration::BuildingType::MainBuilding:
            show = true;
            tabs -> changeActiveTab(0);
        break;
        case Enumeration::BuildingType::Barrack:
            show = true;
            tabs -> changeActiveTab(1);
        break;
        case Enumeration::BuildingType::Barn:
            show = true;
            tabs -> changeActiveTab(2);
        break;
        case Enumeration::BuildingType::Workshop:
            show = true;
            tabs -> changeActiveTab(3);
        break;
        default: break;
    }
    if (show) {
        tabContainer -> show();
        buttonOpenPanel -> setText("Close Panel");
        popUpOpen = true;
    }
}

void Hud::hidePopup(){
    tabContainer -> hide();
    buttonOpenPanel -> setText("Open Panel");
    popUpOpen = false;
}

void Hud::setHUDEvents(){
    buttonOpenPanel->setCallback([&]{
        if (!tabContainer->isVisible()){
            showPopup();
        } else {
            hidePopup();
        }
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

}

void Hud::update() {
    float dt = Game::Instance()  -> getWindow() -> getDeltaTime();
    if (updateTimer <= 0) {
        int melees = 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
        int ranges = 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
        int sieges = 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
            Human::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

        std::stringstream os;
        os << "Player resources: " << 
        "Metal: " << std::to_string(Human::getInstance() -> getMetalAmount()) << " " <<
        "Crystal: " << std::to_string(Human::getInstance() -> getCrystalAmount()) << " " <<
        "Citizens: " << std::to_string(Human::getInstance() -> getCitizens()) << " " <<
        "Happiness: " << std::to_string(Human::getInstance() -> getHappiness()) <<  " " <<
        "City level: "<< std::to_string(Human::getInstance() -> getCityLevel()) <<  " " <<
        "Army size: " << std::to_string(Human::getInstance() -> getArmySize()) << " " <<
        "- Melees: " << std::to_string(melees) <<  " " <<
        "- Ranged: " << std::to_string(ranges) << " " <<
        "- Siege: " << std::to_string(sieges);
        resourceText -> setLabel(os.str());

        melees = 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
        ranges = 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
        sieges = 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
            IA::getInstance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

        std::stringstream iaos;
        iaos << "IA resources:" << 
        "Metal: " << std::to_string(IA::getInstance() -> getMetalAmount()) <<  " " <<
        "Crystal: " << std::to_string(IA::getInstance() -> getCrystalAmount()) <<  " " <<
        "Citizens: " << std::to_string(IA::getInstance() -> getCitizens()) <<  " " <<
        "Happiness: " << std::to_string(IA::getInstance() -> getHappiness()) <<  " " <<
        "City level: "<< std::to_string(IA::getInstance() -> getCityLevel()) <<  " " <<
        "Army size: " << std::to_string(IA::getInstance() -> getArmySize()) <<  " " <<
        " - Melees: " << std::to_string(melees) <<  " " <<
        " - Ranged: " << std::to_string(ranges) <<  " " <<
        " - Siege: " << std::to_string(sieges) <<  " " <<
        "Next choice: " << IA::getInstance() -> getNextChoice() <<  " " <<
        "Behaviour: " << IA::getInstance() -> getChosenBehaviour();

        iaResourceText -> setLabel(iaos.str());

        updateTimer = 0.5;

        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::DisableText);
    } else {
        updateTimer -= dt;
    }
}

void Hud::updatePositions() {
    buttonOpenPanel -> setPosition(Vector2<int>(100,20).getFixed());

    buildingsPanel->setPosition(Vector2<int>(20, 640).getFixed());

    resourceText->setPosition(Vector2<int>(1000,0).getFixed());
    iaResourceText->setPosition(Vector2<int>(1150,0).getFixed());
    warningText->setPosition(Vector2<int>(1000,650).getFixed());

    tabContainer->center();
}

void Hud::drawWarning() {
    //¡Se ha construido un edificio!
    warningText -> show();
}

void Hud::deleteWarning() {
    //¡Se ha borrado un texto que dice que se ha dibujado un texto!
    warningText -> hide();
}

bool Hud::getPopUpOpen() {
    return popUpOpen;
}