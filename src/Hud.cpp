#include "Hud.h"

#include "Human.h"
#include "IA.h"
#include "IOEngine/IO.h"
#include "GraphicEngine/Window.h"

Hud* Hud::pinstance = 0;

Hud* Hud::Instance() {
    if (pinstance == 0) {
        pinstance = new Hud();
    }
    return pinstance;
}

Hud::Hud() {
    debugTime = 0.5;
    debugTimer = debugTime;

    toastBool = false;
    toastTime = 2;
    toastTimer = toastTime;

    popUpOpen = false;
}

Hud::~Hud() {
    //Al cleanUp
}

void Hud::Init(){
    // Building buttons panel
    buildingsPanel = new Panel("Buildings");
    buildingsPanel -> setPosition(Vector2<i32>(575, 546));

    // General
    Widget *generalWidget = new Widget(buildingsPanel);
    generalWidget -> setVerticalLayout();
    generalWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(generalWidget, "General functions");
    Button *buttonExpandTerrain = new Button(generalWidget, "Expand terrain");
    buttonOpenPanel = new Button(generalWidget, "Open Panel");
    buttonOpenPanel -> setPosition(Vector2<i32>(100, 20));

    // Resources
    Widget *resourceWidget = new Widget(buildingsPanel);
    resourceWidget -> setVerticalLayout();
    resourceWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(resourceWidget, "Resource buildings");
    Button *buttonHome = new Button(resourceWidget, "House");
    Button *buttonSiderurgy = new Button(resourceWidget, "Siderurgy");
    Button *buttonQuarry = new Button(resourceWidget, "Quarry");

    // Services
    Widget *serviceWidget = new Widget(buildingsPanel);
    serviceWidget -> setVerticalLayout();
    serviceWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(serviceWidget, "Service buildings");
    Button *buttonSchool = new Button(serviceWidget, "School");
    Button *buttonMarket = new Button(serviceWidget, "Market");
    Button *buttonHospital = new Button(serviceWidget, "Hospital");

    // Military
    Widget *militaryWidget = new Widget(buildingsPanel);
    militaryWidget -> setVerticalLayout();
    militaryWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(militaryWidget, "Military buildings");
    Button *buttonBarrack = new Button(militaryWidget, "Barrack");
    Button *buttonBarn = new Button(militaryWidget, "Barn");
    Button *buttonWorkshop = new Button(militaryWidget, "Workshop");

    // Defense
    Widget *defenseWidget = new Widget(buildingsPanel);
    defenseWidget -> setVerticalLayout();
    defenseWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(defenseWidget, "Defensive buildings");
    Button *buttonTower = new Button(defenseWidget, "Tower");
    Button *buttonWall = new Button(defenseWidget, "Wall");

    // Button callbacks
    buttonBarn->setTooltip("Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonBarn->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barn);
    });

    buttonBarrack->setTooltip("Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonBarrack->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Barrack);
    });

    buttonHome->setTooltip("Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonHome->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::House);
    });

    buttonHospital->setTooltip("Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonHospital->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Hospital);
    });

    buttonMarket->setTooltip("Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonMarket->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Market);
    });

    buttonQuarry->setTooltip("Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonQuarry->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Quarry);
    });

    buttonSchool->setTooltip("Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonSchool->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::School);
    });

    buttonSiderurgy->setTooltip("Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonSiderurgy->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Siderurgy);
    });

    buttonTower->setTooltip("Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");
    buttonTower->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Tower);
    });

    buttonWall->setTooltip("Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonWall->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Wall);
    });

    buttonWorkshop->setTooltip("Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonWorkshop->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode(Enumeration::BuildingType::Workshop);
    });

    buttonExpandTerrain->setTooltip("Purchase a terrain expansion that will allow you to build a bigger city.\n Metal cost: 500.");
    buttonExpandTerrain->setCallback([]{
        //ToDo: hacer que se expanda el terreno edificable y que el susodicho exista
    });

    buttonOpenPanel->setTooltip("Open your panel to manage your city.");

    buttonOpenPanel->setCallback([&]{
        if (!tabContainer->isVisible()){
            showPopup();
        } else {
            hidePopup();
        }
    });

    ///// DEBUG /////
    playerResources = new Panel("Player Resources");
    playerResources ->setVerticalLayout();
    playerResources -> setSize(Vector2<i32> (200, 230));
    i32 melees = 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
    i32 ranges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
    i32 sieges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);
    std::stringstream os;
    os << "Metal: " << std::to_string(Human::Instance() -> getMetalAmount());
    playerMetalAmount = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Crystal: " << std::to_string(Human::Instance() -> getCrystalAmount());
    playerCrystalAmount = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Citizens: " << std::to_string(Human::Instance() -> getCitizens());
    playerCitizens = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Happiness: " << std::to_string(Human::Instance() -> getHappiness());
    playerHappiness = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "City level: "<< std::to_string(Human::Instance() -> getCityLevel());
    playerCityLevel = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Army size: " << std::to_string(Human::Instance() -> getArmySize());
    playerArmySize = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Melee: " << std::to_string(melees);
    playerMelees = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Ranged: " << std::to_string(ranges);
    playerRangeds = new Label(playerResources, os.str());
    os = std::stringstream();
    os << "Siege: " << std::to_string(sieges);
    playerSieges = new Label(playerResources, os.str());
    os = std::stringstream();
    
    iaResources = new Panel("IA Resources");
    iaResources -> setVerticalLayout();
    iaResources -> setPosition(Vector2<i32>(1100, 0));
    iaResources -> setSize(Vector2<i32> (200, 270));
    melees = 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
    ranges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
    sieges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);
    std::stringstream iaos;
    iaos << "Metal: " << std::to_string(IA::Instance() -> getMetalAmount());
    iaMetalAmount = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Crystal: " << std::to_string(IA::Instance() -> getCrystalAmount());
    iaCrystalAmount = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Citizens: " << std::to_string(IA::Instance() -> getCitizens());
    iaCitizens = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Happiness: " << std::to_string(IA::Instance() -> getHappiness());
    iaHappiness = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "City level: "<< std::to_string(IA::Instance() -> getCityLevel());
    iaCityLevel = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Army size: " << std::to_string(IA::Instance() -> getArmySize());
    iaArmySize = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Melee: " << std::to_string(melees);
    iaMelees = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Ranged: " << std::to_string(ranges);
    iaRangeds = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Siege: " << std::to_string(sieges);
    iaSieges = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Next choice: " << IA::Instance() -> getNextChoice();
    iaNextChoice = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Behaviour: " << IA::Instance() -> getChosenBehaviour();
    iaBehaviour = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    
    tabContainer = new Panel("Building viewer");
        tabContainer -> setSize(Vector2<i32>(350, 300));
        tabContainer -> setGroupLayout();
        tabs = new TabPanel(tabContainer);
        Tab *mainBuildingTab = tabs->createTab("Main Building");
        Tab *barrackTab = tabs->createTab("Barrack");
        Tab *barnTab = tabs->createTab("Barn");
        Tab *workshopTab = tabs->createTab("Workshop");

        //MainBuildingTab
        {
            Button *b = new Button(mainBuildingTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            hallTroopList = new ComboBox(mainBuildingTab, {});

            b = new Button(mainBuildingTab, "Deploy selected troop");
            b -> setTooltip("Deploy your selected unit onto the map");
            b -> setCallback([&]{
                i32 index = hallTroopList -> getSelectedOption();
                if (index >= 0) {
                    i32 id = troopsInHallIDs . at(index);
                    Human::Instance() -> getUnitManager() -> startDeployingTroop(id);
                }
                hidePopup();
            });

            b = new Button(mainBuildingTab, "Deploy all troops");
            b -> setTooltip("Deploy all your units onto the map");
            b -> setCallback([&]{
                Human::Instance() -> getUnitManager() -> startDeployingAllTroops();
                hidePopup();
            });

            b = new Button(mainBuildingTab, "Retract all troops");
            b -> setTooltip("Retract your units back into your town hall");
            b -> setCallback([&]{
                IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::RetractTroopsHuman);
            });

            mainBuildingTab->hide();
        }
        //BarrackTab
        {
            Button *b = new Button(barrackTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            barrackEmpty = new Widget(barrackTab);
            barrackEmpty -> setGroupLayout();
            new Label(barrackEmpty, "Este edificio no esta activo aun");

            barrackContent = new Widget(barrackTab);
            barrackContent -> setGroupLayout();

            b = new Button(barrackContent, "Create melee footman");
            b -> setTooltip("Create a melee unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardM);
                //ToDo: añadir a la cola de produccion (HUD)
            });
            
            b = new Button(barrackContent, "Create ranged footman");
            b -> setTooltip("Create a ranged unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::StandardR);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            ScrollPanel *barrackScroll = new ScrollPanel(barrackContent);
            barrackScroll -> setSize(Vector2<i32>(250, 50));
            barrackTroopQueueWidget = new Widget(barrackScroll);
            barrackTroopQueueWidget -> setGroupLayout();

            barrackContent -> hide();
        }
        //BarnTab
        {
            Button *b = new Button(barnTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            barnEmpty = new Widget(barnTab);
            barnEmpty -> setGroupLayout();
            new Label(barnEmpty, "Este edificio no esta activo aun");

            barnContent = new Widget(barnTab);
            barnContent -> setGroupLayout();

            b = new Button(barnContent, "Create mounted melee unit");
            b -> setTooltip("Create a melee unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedM);
                //ToDo: añadir a la cola de produccion (HUD)
            });
            
            b = new Button(barnContent, "Create mounted ranged unit");
            b -> setTooltip("Create a ranged unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::AdvancedR);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            b = new Button(barnContent, "Create monster");
            b -> setTooltip("Create a overwhelmingly powerful creature to destroy your enemies\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Idol);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            ScrollPanel *barnScroll = new ScrollPanel(barnContent);
            barnScroll -> setSize(Vector2<i32>(250, 50));
            barnTroopQueueWidget = new Widget(barnScroll);
            barnTroopQueueWidget -> setVerticalLayout();

            barnContent -> hide();
        }
        //Workshop tab
        {
            Button *b = new Button(workshopTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                this->hidePopup();
            });

            workshopEmpty = new Widget(workshopTab);
            workshopEmpty -> setGroupLayout();
            new Label(workshopEmpty, "Este edificio no esta activo aun");

            workshopContent = new Widget(workshopTab);
            workshopContent -> setGroupLayout();

            b = new Button(workshopContent, "Create ram");
            b -> setTooltip("Create a ram that specializes in destroying buildings\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Desintegrator);
                //ToDo: añadir a la cola de produccion (HUD)
            });
            
            b = new Button(workshopContent, "Create catapult");
            b -> setTooltip("Create a catapult that heavy area of damage\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop(Enumeration::UnitType::Launcher);
                //ToDo: añadir a la cola de produccion (HUD)
            });

            ScrollPanel *workshopScroll = new ScrollPanel(workshopContent);
            workshopScroll -> setSize(Vector2<i32>(250, 50));
            workshopTroopQueueWidget = new Widget(workshopScroll);
            workshopTroopQueueWidget -> setVerticalLayout();

            workshopContent -> hide();
        }
        tabs->changeActiveTab(0);
    tabContainer->refreshLayout();
    tabContainer->center();
    tabContainer->hide();


    toast = new Panel("");
    toast->setPosition(Vector2<i32>(570, 50));
    toastText = new Label(toast, "");
    toast->hide();

    Window::Instance() -> setGUI();
}

void Hud::Update() { 
    f32 dt = Window::Instance() -> getDeltaTime();
    if (debugTimer <= 0) {
        debug();
        debugTimer = 0.5;
    } else {
        debugTimer -= dt;
    }
    if (toastBool){
        if (toastTimer <= 0) {
            hideToast();
        } else {
            toastTimer -= dt;
        }
    }
}

void Hud::CleanUp(){
    delete buildingsPanel;
    delete tabContainer;
    delete playerResources;
    delete iaResources;
    //ToDo: incompleto
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

void Hud::addTroopToHall(i32 idTroop, Enumeration::UnitType t){
    switch(t){
        case Enumeration::UnitType::StandardM:
            hallTroopList -> addOption("Melee footman");
        break;
        case Enumeration::UnitType::StandardR:
            hallTroopList -> addOption("Ranged footman");
        break;
        case Enumeration::UnitType::AdvancedM:
            hallTroopList -> addOption("Mounted melee unit");
        break;
        case Enumeration::UnitType::AdvancedR:
            hallTroopList -> addOption("Mounted ranged unit");
        break;
        case Enumeration::UnitType::Idol:
            hallTroopList -> addOption("Create idol");
        break;
        case Enumeration::UnitType::Launcher:
            hallTroopList -> addOption("Catapult");
        break;
        case Enumeration::UnitType::Desintegrator:
            hallTroopList -> addOption("Ram");
        break;
        default: break;
    }
    troopsInHallIDs . push_back(idTroop);
    tabContainer->refreshLayout();
}

void Hud::removeTroopFromHall(i32 idTroop){
   std::vector<i32>::iterator it = find(troopsInHallIDs.begin(), troopsInHallIDs.end(), idTroop);
   if (it != troopsInHallIDs.end()) {
        i32 nPosition = std::distance(troopsInHallIDs.begin(), it);
        hallTroopList -> removeOption(nPosition);
        troopsInHallIDs . erase(it);
        tabContainer->refreshLayout();
   }
}

void Hud::addTroopToQueue(i32 idTroop, Enumeration::UnitType t){
    switch(t){
        case Enumeration::UnitType::StandardM:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Melee footman");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::StandardR:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Ranged footman");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::AdvancedM:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Mounted melee unit");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::AdvancedR:
        {
            Widget *p = new Widget(barrackTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Mounted ranged unit");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::Idol:
        {
            Widget *p = new Widget(barnTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Create idol");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::Launcher:
        {
            Widget *p = new Widget(workshopTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Catapult");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        case Enumeration::UnitType::Desintegrator:
        {
            Widget *p = new Widget(workshopTroopQueueWidget);
            p->setVerticalLayout();
            new Label(p, "Ram");
            ProgressBar *pb = new ProgressBar(p);
            troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
            troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
        }
        break;
        default: break;
    }
    tabContainer->refreshLayout();
}

void Hud::modifyTroopFromQueue(i32 idTroop, f32 newValue){
    std::map<i32,ProgressBar*>::iterator it = troopQueueProgressBars . find(idTroop);
    if (it != troopQueueProgressBars.end()) {
        it->second->setValue(newValue);
    }
    tabContainer->refreshLayout();
}

void Hud::removeTroopFromQueue(i32 idTroop){
    std::map<i32,ProgressBar*>::iterator it = troopQueueProgressBars . find(idTroop);
    if (it != troopQueueProgressBars.end()) {
        troopQueueProgressBars . erase(it);
    }
    std::map<i32, Widget*>::iterator it2 = troopQueueList . find(idTroop);
    if (it2 != troopQueueList.end()) {
        delete it2->second;
        troopQueueList . erase(it2);
        Window::Instance()->getGUIEnvironment()->performLayout();
    }
}

void Hud::updatePositions() {
    buttonOpenPanel -> setPosition(Vector2<i32>(100,20));

    buildingsPanel->setPosition(Vector2<i32>(20, 640));

    tabContainer->center();
}

void Hud::showToast(std::string s){
    //ToDo: queue?
    if (!toastBool){
        toastText->setLabel(s);
        toast->refreshLayout();
        toast->show();
        toastTimer = toastTime;
        toastBool = true;
    }
}

void Hud::hideToast(){
    toast->hide();
    toastBool = false;
}

void Hud::debug(){
    i32 melees = 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
    i32 ranges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
    i32 sieges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
        Human::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

    std::stringstream os;
    os << "Metal: " << std::to_string(Human::Instance() -> getMetalAmount());
    playerMetalAmount -> setLabel(os.str());
    os = std::stringstream();
    os << "Crystal: " << std::to_string(Human::Instance() -> getCrystalAmount());
    playerCrystalAmount -> setLabel(os.str());
    os = std::stringstream();
    os << "Citizens: " << std::to_string(Human::Instance() -> getCitizens());
    playerCitizens -> setLabel(os.str());
    os = std::stringstream();
    os << "Happiness: " << std::to_string(Human::Instance() -> getHappiness());
    playerHappiness -> setLabel(os.str());
    os = std::stringstream();
    os << "City level: "<< std::to_string(Human::Instance() -> getCityLevel());
    playerCityLevel -> setLabel(os.str());
    os = std::stringstream();
    os << "Army size: " << std::to_string(Human::Instance() -> getArmySize());
    playerArmySize -> setLabel(os.str());
    os = std::stringstream();
    os << "Melee: " << std::to_string(melees);
    playerMelees -> setLabel(os.str());
    os = std::stringstream();
    os << "Ranged: " << std::to_string(ranges);
    playerRangeds -> setLabel(os.str());
    os = std::stringstream();
    os << "Siege: " << std::to_string(sieges);
    playerSieges -> setLabel(os.str());
    os = std::stringstream();

    melees = 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardM) + 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedM);
    ranges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::StandardR) + 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::AdvancedR);
    sieges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) + 
        IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher);

    std::stringstream iaos;
    iaos << "Metal: " << std::to_string(IA::Instance() -> getMetalAmount());
    iaMetalAmount -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Crystal: " << std::to_string(IA::Instance() -> getCrystalAmount());
    iaCrystalAmount -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Citizens: " << std::to_string(IA::Instance() -> getCitizens());
    iaCitizens -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Happiness: " << std::to_string(IA::Instance() -> getHappiness());
    iaHappiness -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "City level: "<< std::to_string(IA::Instance() -> getCityLevel());
    iaCityLevel -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Army size: " << std::to_string(IA::Instance() -> getArmySize());
    iaArmySize -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Melee: " << std::to_string(melees);
    iaMelees -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Ranged: " << std::to_string(ranges);
    iaRangeds -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Siege: " << std::to_string(sieges);
    iaSieges -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Next choice: " << IA::Instance() -> getNextChoice();
    iaNextChoice -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Behaviour: " << IA::Instance() -> getChosenBehaviour();
    iaBehaviour -> setLabel(iaos.str());
    iaos = std::stringstream();
}

bool Hud::getPopUpOpen() {
    return popUpOpen;
}