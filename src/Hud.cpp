#include "Hud.h"

#include "Human.h"
#include "IA.h"
#include "IOEngine/IO.h"
#include "GraphicEngine/Window.h"

#define _WIDTH 100
#define _HEIGHT 30

Hud* Hud::pinstance = 0;

Hud* Hud::Instance() {
    if (pinstance == 0) {
        pinstance = new Hud();
    }
    return pinstance;
}

Hud::Hud() {
    popUpOpen = false;
}

Hud::~Hud() {
    //Al cleanUp
}

void Hud::Init() {
	debugTimer = nullptr;
	playerTimer = nullptr;

    toastTimer = new Timer(2, true);
    toastTimer -> setCallback([&]() {
		if (notificationQueue.size()) {
			showToast(notificationQueue.front());
			notificationQueue.pop();
		} else hideToast();
    });
	
    // Building buttons panel
    buildingsPanel = new Panel("Buildings");

    buildingsPanel -> setPosition(Vector2<i32>(125, 445));

    // General
    generalWidget = new Widget(buildingsPanel);
    generalWidget -> setVerticalLayout();

    new Label(generalWidget, "General functions");

    buttonExpandTerrain = new Button(generalWidget, "Expand terrain");
    buttonExpandTerrain -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonExpandTerrain -> setBackgroundColor(150, 0, 200, 200);

    buttonOpenPanel = new Button(generalWidget, "Open Panel");
    buttonOpenPanel -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonOpenPanel -> setBackgroundColor(150, 0, 200, 200);

    // Resources
    resourceWidget = new Widget(buildingsPanel);
    resourceWidget -> setVerticalLayout();
    resourceWidget -> setPosition(Vector2<i32>(20, 640));
    
    new Label(resourceWidget, "Resource buildings");
    buttonHouse = new Button(resourceWidget, "Home");
    buttonHouse -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonHouse -> setBackgroundColor(150, 0, 200, 0);

    buttonSiderurgy = new Button(resourceWidget, "Siderurgy");
    buttonSiderurgy -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonSiderurgy -> setBackgroundColor(150, 0, 200 ,0);

    buttonQuarry = new Button(resourceWidget, "Crystal quarry");
    buttonQuarry -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonQuarry -> setBackgroundColor(150, 0, 200, 0);

    // Services
    serviceWidget = new Widget(buildingsPanel);
    serviceWidget -> setVerticalLayout();
    serviceWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(serviceWidget, "Service buildings");
    buttonSchool = new Button(serviceWidget, "Reasearch lab");
    buttonSchool -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonSchool -> setBackgroundColor(150, 200, 0, 200);

    buttonMarket = new Button(serviceWidget, "Resource center");
    buttonMarket -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonMarket -> setBackgroundColor(150, 200, 0, 200);

    buttonHospital = new Button(serviceWidget, "Healing center");
    buttonHospital -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonHospital -> setBackgroundColor(150, 200, 0, 200);

    // Military
    militaryWidget = new Widget(buildingsPanel);
    militaryWidget -> setVerticalLayout();
    militaryWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(militaryWidget, "Military buildings");
    buttonBarrack = new Button(militaryWidget, "Infantry center");
    buttonBarrack -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonBarrack -> setBackgroundColor(150, 200, 0, 0);

    buttonBarn = new Button(militaryWidget, "Creature lab");
    buttonBarn -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonBarn -> setBackgroundColor(150, 200, 0, 0);

    buttonWorkshop = new Button(militaryWidget, "War factory");
    buttonWorkshop -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonWorkshop -> setBackgroundColor(150, 200, 0, 0);

    // Defense
    defenseWidget = new Widget(buildingsPanel);
    defenseWidget -> setVerticalLayout();
    defenseWidget -> setPosition(Vector2<i32>(20, 640));

    new Label(defenseWidget, "Defensive buildings");
    buttonTower = new Button(defenseWidget, "Watchtower");
    buttonTower -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonTower -> setBackgroundColor(150, 0, 0, 200);

    buttonWall = new Button(defenseWidget, "Wall");
    buttonWall -> setSize(Vector2<i32>(_WIDTH, _HEIGHT));
    buttonWall -> setBackgroundColor(150, 0, 0, 200);

    // Button callbacks
    buttonBarn->setTooltip("Build a barn that will allow you to train mounted military units.\n Metal cost: 800.");
    buttonBarn->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Barn");
    });

    buttonBarrack->setTooltip("Build a barrack that will allow you to train basic military units.\n Metal cost: 720.");
    buttonBarrack->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Barrack");
    });

    buttonHouse->setTooltip("Build a home that will increase your total citizens.\n Metal cost: 100.\nCitizens +10");
    buttonHouse->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("House");
    });

    buttonHospital->setTooltip("Build a hospital that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +15");
    buttonHospital->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Hospital");
    });

    buttonMarket->setTooltip("Build a market that will improve your citizens happiness.\n Metal cost: 800.\nHappiness +10");
    buttonMarket->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Market");
    });

    buttonQuarry->setTooltip("Build a quarry that will produce crystal over time.\n Metal cost: 2000.\nCrystal/second +10");
    buttonQuarry->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Quarry");
    });

    buttonSchool->setTooltip("Build a school that will improve your citizens happiness.\nMetal cost: 500.\nHappiness +5");
    buttonSchool->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("School");
    });

    buttonSiderurgy->setTooltip("Build a siderurgy that will produce metal over time.\n Metal cost: 500.\nMetal/second +10");
    buttonSiderurgy->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Siderurgy");
    });

    buttonTower->setTooltip("Build a wall that will protect your city from outsiders by attacking them.\n Metal cost: 300.");
    buttonTower->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Tower");
    });

    buttonWall->setTooltip("Build a wall that will protect your city from outsiders.\n Metal cost: 75.");
    buttonWall->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Wall");
    });

    buttonWorkshop->setTooltip("Build a workshop that will allow you to create siege weapons.\n Metal cost: 1100.\nCrystal cost: 230");
    buttonWorkshop->setCallback([]{
        Human::Instance() -> getBuildingManager() -> setBuildingMode("Workshop");
    });

    buttonExpandTerrain->setTooltip("Purchase a terrain expansion that will allow you to build a bigger city.\n Metal cost: 500.");
    buttonExpandTerrain->setCallback([&]{
		addToastToQueue("Se ha expandido el terreno");
        Human::Instance() -> increaseBuildableRange();
    });

    buttonOpenPanel->setTooltip("Open your panel to manage your city.");

    buttonOpenPanel->setCallback([&]{
        if (!tabContainer->isVisible()) {
            showPopup();
        } else {
            hidePopup();
        }
    });
    
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
                hidePopup();
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
                IO::Instance() -> getEventManager() -> triggerEvent("RetractTroopsHuman");
            });
        }
        //BarrackTab
        {
            Button *b = new Button(barrackTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                hidePopup();
            });

            barrackEmpty = new Widget(barrackTab);
            barrackEmpty -> setGroupLayout();
            new Label(barrackEmpty, "Este edificio no esta activo aun");

            barrackContent = new Widget(barrackTab);
            barrackContent -> setGroupLayout();

            b = new Button(barrackContent, "Create melee footman");
            b -> setTooltip("Create a melee unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("StandardM");
            });
            
            b = new Button(barrackContent, "Create ranged footman");
            b -> setTooltip("Create a ranged unit that moves around by feet\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("StandardR");
            });

            ScrollPanel *barrackScroll = new ScrollPanel(barrackContent);
            barrackScroll -> setSize(Vector2<i32>(250, 50));
            barrackTroopQueueWidget = new Widget(barrackScroll);
            barrackTroopQueueWidget -> setGroupLayout();
        }
        //BarnTab
        {
            Button *b = new Button(barnTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                hidePopup();
            });

            barnEmpty = new Widget(barnTab);
            barnEmpty -> setGroupLayout();
            new Label(barnEmpty, "Este edificio no esta activo aun");

            barnContent = new Widget(barnTab);
            barnContent -> setGroupLayout();

            b = new Button(barnContent, "Create mounted melee unit");
            b -> setTooltip("Create a melee unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("AdvancedM");
            });
            
            b = new Button(barnContent, "Create creature");
            b -> hide();
            b -> setTooltip("Create a ranged unit that rides a mighty beast\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("AdvancedR");
            });

            b = new Button(barnContent, "Create idol");
            b -> setTooltip("Create a overwhelmingly powerful creature to destroy your enemies\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("Idol");
            });

            ScrollPanel *barnScroll = new ScrollPanel(barnContent);
            barnScroll -> setSize(Vector2<i32>(250, 50));
            barnTroopQueueWidget = new Widget(barnScroll);
            barnTroopQueueWidget -> setVerticalLayout();
        }
        //Workshop tab
        {
            Button *b = new Button(workshopTab, "Close");
            b->setTooltip("Close popup");
            b->setCallback([&] {
                hidePopup();
            });

            workshopEmpty = new Widget(workshopTab);
            workshopEmpty -> setGroupLayout();
            new Label(workshopEmpty, "Este edificio no esta activo aun");

            workshopContent = new Widget(workshopTab);
            workshopContent -> setGroupLayout();

            b = new Button(workshopContent, "Create ram");
            b -> setTooltip("Create a ram that specializes in destroying buildings\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("Desintegrator");
            });
            
            b = new Button(workshopContent, "Create catapult");
            b -> setTooltip("Create a catapult that heavy area of damage\nMetal cost: 100\nCrystal cost:100");
            b->setCallback([&] {
                Human::Instance() -> getUnitManager() -> createTroop("Launcher");
            });

            ScrollPanel *workshopScroll = new ScrollPanel(workshopContent);
            workshopScroll -> setSize(Vector2<i32>(250, 50));
            workshopTroopQueueWidget = new Widget(workshopScroll);
            workshopTroopQueueWidget -> setVerticalLayout();
        }
    tabs->changeActiveTab(0);
    tabContainer->refreshLayout();
    tabContainer->center();

    toast = new Panel("");
    toast->setPosition(Vector2<i32>(600, 50));
    toastText = new Label(toast, "");

    //Hide tabs
    mainBuildingTab->hide();
    barrackContent -> hide();
    barnContent -> hide();
    workshopContent -> hide();
    tabContainer->hide();

    //Hide building buttons
    buttonHouse -> hide();
    buttonSiderurgy -> hide();
    buttonQuarry -> hide();
    buttonSchool -> hide();
    buttonMarket -> hide();
    buttonHospital -> hide();
    buttonBarrack -> hide();
    buttonBarn -> hide();
    buttonWorkshop -> hide();
    buttonTower -> hide();
    buttonWall -> hide();
    buttonExpandTerrain -> hide();

    //Hide panel widgets
    generalWidget -> hide();
    resourceWidget -> hide();
    serviceWidget -> hide();
    militaryWidget -> hide();
    defenseWidget -> hide();

    // Hide panel
    buildingsPanel -> hide();

    //Hide toast
    toast->hide();

    Window::Instance() -> setGUI();
}

void Hud::Update() { 
	
}

void Hud::CleanUp() {
    delete toastTimer;
    if (debugTimer != nullptr) delete debugTimer;
	if (playerTimer != nullptr) delete playerTimer;

    delete buttonExpandTerrain;
    delete buttonOpenPanel;
    delete buttonHouse;
    delete buttonSiderurgy;
    delete buttonQuarry;
    delete resourceWidget;
    delete buttonSchool;
    delete buttonMarket;
    delete buttonHospital;
    delete serviceWidget;
    delete buttonBarrack;
    delete buttonBarn;
    delete buttonWorkshop;
    delete militaryWidget;
    delete buttonTower;
    delete buttonWall;
    delete defenseWidget;
    delete buildingsPanel;
    delete generalWidget;

    delete playerMetalAmount;
    delete playerCrystalAmount;
    delete playerPeople;
    delete playerCitizens;
    delete playerUnitFighters;
    delete playerHappiness;
    delete playerCityLevel;
    delete playerArmySize;
    delete playerMelees;
    delete playerRangeds;
    delete playerSieges;
    delete playerResources;

    delete iaMetalAmount;
    delete iaCrystalAmount;
    delete iaCitizens;
    delete iaHappiness;
    delete iaCityLevel;
    delete iaArmySize;
    delete iaMelees;
    delete iaRangeds;
    delete iaSieges;
    delete iaNextChoice;
    delete iaBehaviour;
    delete iaResources;

    delete hallTroopList;
    delete barrackEmpty;
    delete barrackTroopQueueWidget;
    delete barrackContent;
    delete barnEmpty;
    delete barnTroopQueueWidget;
    delete barnContent;
    delete workshopEmpty;
    delete workshopTroopQueueWidget;
    delete workshopContent;
    delete tabs;
    delete tabContainer;

    delete toastText;
    delete toast;
    delete framerateLabel;
}

void Hud::InitProgressBar(){
	loadPanel = new Panel("");
	loadProgressBar = new ProgressBar(loadPanel);
	loadPanel->refreshLayout();
	loadPanel->center();
	loadPanel -> hide();
}

void Hud::InitPlayerStats(){
    playerTimer = new Timer (0.5, true);
    playerTimer -> setCallback([&]() {
        UpdatePlayerStats();
    });

    playerResources = new Panel("Player Resources");
    playerResources ->setVerticalLayout();
    playerResources -> setSize(Vector2<i32> (120, 165));

    std::stringstream os;
    os << "Metal: " << std::to_string(Human::Instance() -> metalAmount);
    playerMetalAmount = new Label(playerResources, os.str());
    playerMetalAmount -> setColor(255, 255, 255, 255);

    os = std::stringstream();
    os << "Crystal: " << std::to_string(Human::Instance() -> crystalAmount);
    playerCrystalAmount = new Label(playerResources, os.str());
    playerCrystalAmount -> setColor(255, 255, 255, 255);

    os = std::stringstream();
    os << "Denizens: " << std::to_string(Human::Instance() -> getMaxPeople());
    playerPeople = new Label(playerResources, os.str());
    playerPeople -> setColor(255, 255, 255, 170);

    os = std::stringstream();
    os << "Citizens: " << std::to_string(Human::Instance() -> getCitizens());
    playerCitizens = new Label(playerResources, os.str());
    playerCitizens -> setColor(255, 255, 255, 170);

    os = std::stringstream();
    os << "Warriors: " << std::to_string(Human::Instance() -> getUnitManager() -> getUnitFighters());
    playerUnitFighters = new Label(playerResources, os.str());
    playerUnitFighters -> setColor(255, 255, 255, 170);

    os = std::stringstream();
    os << "Army size: " << std::to_string(Human::Instance() -> getArmySize());
    playerArmySize = new Label(playerResources, os.str());
    playerArmySize -> setColor(150, 200, 200, 0);
    playerArmySize ->hide();

    os = std::stringstream();
    os << "Happiness: " << std::to_string(Human::Instance() -> getHappiness());
    playerHappiness = new Label(playerResources, os.str());
    playerHappiness -> setColor(255, 255, 255, 255);
    
	Window::Instance() -> setGUI();
}

void Hud::UpdatePlayerStats(){
    std::stringstream os;
    os << "Metal: " << std::to_string(Human::Instance() -> metalAmount);
    playerMetalAmount -> setLabel(os.str());
    os = std::stringstream();
    os << "Crystal: " << std::to_string(Human::Instance() -> crystalAmount);
    playerCrystalAmount -> setLabel(os.str());
    os = std::stringstream();
    os << "Denizens: " << std::to_string(Human::Instance() -> getMaxPeople());
    playerPeople -> setLabel(os.str());
    os = std::stringstream();
    os << "Citizens: " << std::to_string(Human::Instance() -> getCitizens());
    playerCitizens -> setLabel(os.str());
    os = std::stringstream();
    os << "Warriors: " << std::to_string(Human::Instance() -> getUnitManager() -> getUnitFighters());
    playerUnitFighters -> setLabel(os.str());
    os = std::stringstream();
    os << "Army Size: " << std::to_string(Human::Instance() -> getArmySize());
    playerArmySize -> setLabel(os.str());
    os = std::stringstream();
    os << "Happiness: " << std::to_string(Human::Instance() -> getHappiness());
    playerHappiness -> setLabel(os.str());
}

void Hud::enableTab(std::string t) {
    if (t == "Barrack") {
        barrackEmpty -> hide();
        barrackContent -> show();
    } else if (t == "Barn") {
        barnEmpty -> hide();
        barnContent -> show();
    } else if (t == "Workshop") {
        workshopEmpty -> hide();
        workshopContent -> show();
    } 

    tabContainer -> refreshLayout();
}

void Hud::disableTab(std::string t) {
    if (t == "Barrack") {
        barrackEmpty->show();
        barrackContent->hide();
    } else if (t == "Barn") {
        barnEmpty->show();
        barnContent->hide();
    } else if (t == "Workshop") {
        workshopEmpty->show();
        workshopContent->hide();
    } 

    tabContainer->refreshLayout();
}

void Hud::showPopup() {
    tabContainer -> show();
    buttonOpenPanel -> setText("Close Panel");
    popUpOpen = true;
}

void Hud::showPopup(std::string t) {
    bool show = false;
    if (t == "MainBuilding") {
        show = true;
        tabs -> changeActiveTab(0);
    } else if (t == "Barrack") {
        show = true;
        tabs -> changeActiveTab(1);
    } else if (t == "Barn") {
        show = true;
        tabs -> changeActiveTab(2);
    } else if (t == "Workshop") {
        show = true;
        tabs -> changeActiveTab(3);
    }
    if (show) {
        tabContainer -> show();
        buttonOpenPanel -> setText("Close Panel");
        popUpOpen = true;
    }
}

void Hud::hidePopup() {
    tabContainer -> hide();
    buttonOpenPanel -> setText("Open Panel");
    popUpOpen = false;
}

void Hud::addTroopToHall(i32 idTroop, std::string t) {
    if (t == "StandardM") {
        hallTroopList -> addOption("Melee footman");
    } else if (t == "StandardR") {
        hallTroopList -> addOption("Ranged footman");
    } else if (t == "AdvancedM") {
        hallTroopList -> addOption("Mounted melee unit");
    } else if (t == "AdvancedR") {
        hallTroopList -> addOption("Mounted ranged unit");
    } else if (t == "Idol") {
        hallTroopList -> addOption("Create idol");
    } else if (t == "Launcher") {
        hallTroopList -> addOption("Catapult");
    } else if (t == "Desintegrator") {
        hallTroopList -> addOption("Ram");
    }
    
    troopsInHallIDs.push_back(idTroop);
    tabContainer -> refreshLayout();
}

void Hud::removeTroopFromHall(i32 idTroop) {
   std::vector<i32>::iterator it = find(troopsInHallIDs.begin(), troopsInHallIDs.end(), idTroop);
   if (it != troopsInHallIDs.end()) {
        i32 nPosition = std::distance(troopsInHallIDs.begin(), it);
        hallTroopList -> removeOption(nPosition);
        troopsInHallIDs.erase(it);
        tabContainer -> refreshLayout();
   }
}
/* Kind of trash code */
void Hud::addTroopToQueue(i32 idTroop, std::string t) {
    if (t == "StandardM") {
        Widget *p = new Widget(barrackTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Melee footman");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    } else if (t == "StandardR") {
        Widget *p = new Widget(barrackTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Ranged footman");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    } else if (t == "AdvancedM") {
        Widget *p = new Widget(barrackTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Mounted melee unit");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    } else if (t == "AdvancedR") {
        Widget *p = new Widget(barrackTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Mounted ranged unit");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    } else if (t == "Idol") {
        Widget *p = new Widget(barnTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Create idol");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    } else if (t == "Launcher") {
        Widget *p = new Widget(workshopTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Catapult");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    } else if (t == "Desintegrator") {
        Widget *p = new Widget(workshopTroopQueueWidget);
        p->setVerticalLayout();
        new Label(p, "Ram");
        ProgressBar *pb = new ProgressBar(p);
        troopQueueProgressBars . insert(std::pair<i32, ProgressBar*>(idTroop, pb));
        troopQueueList . insert(std::pair<i32, Widget*>(idTroop, p));
    }

    tabContainer->refreshLayout();
}

void Hud::modifyTroopFromQueue(i32 idTroop, f32 newValue) {
    std::map<i32,ProgressBar*>::iterator it = troopQueueProgressBars . find(idTroop);
    if (it != troopQueueProgressBars.end()) {
        it -> second -> setValue(newValue);
    }
    tabContainer->refreshLayout();
}

void Hud::removeTroopFromQueue(i32 idTroop) {
    std::map<i32,ProgressBar*>::iterator it = troopQueueProgressBars . find(idTroop);
    if (it != troopQueueProgressBars.end()) {
        troopQueueProgressBars.erase(it);
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

void Hud::addToastToQueue(std::string s) {
	notificationQueue.push(s);
}

void Hud::showToast(std::string s) {
    toastText->setLabel(s);
    toast->refreshLayout();
    toast->show();
}

void Hud::hideToast() {
    toast->hide();
}

void Hud::setProgressBar(f32 a){
	loadProgressBar->setValue(a);
    loadPanel->refreshLayout();
}

void Hud::showProgressBar(bool a){
	if (a) loadPanel->show();
	else loadPanel->hide();
}

void Hud::setButtonStatus(std::string t, bool status) {
    if (t == "Barn") {
        if (status) buttonBarn -> show();
        else buttonBarn -> hide();
    } else if (t == "Barrack") {
        if (status) buttonBarrack -> show();
        else buttonBarrack -> hide();
    } else if (t == "Hospital") {
        if (status) buttonHospital -> show();
        else buttonHospital -> hide();
    } else if (t == "House") {
        if (status) buttonHouse -> show();
        else buttonHouse -> hide();
    } else if (t == "Market") {
        if (status) buttonMarket -> show();
        else buttonMarket -> hide();
    } else if (t == "Quarry") {
        if (status) buttonQuarry -> show();
        else buttonQuarry -> hide();
    } else if (t == "School") {
        if (status) buttonSchool -> show();
        else buttonSchool -> hide();
    } else if (t == "Siderurgy") {
        if (status) buttonSiderurgy -> show();
        else buttonSiderurgy -> hide();
    } else if (t == "Tower") {
        if (status) buttonTower -> show();
        else buttonTower -> hide();
    } else if (t == "Wall") {
        if (status) buttonWall -> show();
        else buttonWall -> hide();
    } else if (t == "Workshop") {
        if (status) buttonWorkshop -> show();
        else buttonWorkshop -> hide();
    } else if (t == "expandableTerrain") {
        if (status) buttonExpandTerrain -> show();
        else buttonExpandTerrain -> hide();
    } 
    
    adjustMenuVisibility();
    buildingsPanel -> refreshLayout();
}

void Hud::adjustMenuVisibility() {
    if (!buttonSiderurgy -> isVisible() && !buttonQuarry -> isVisible() && !buttonHouse -> isVisible()) resourceWidget -> hide();
    else resourceWidget -> show();

    if (!buttonSchool -> isVisible() && !buttonMarket -> isVisible() && !buttonHospital -> isVisible()) serviceWidget -> hide();
    else serviceWidget -> show();

    if (!buttonBarrack -> isVisible() && !buttonBarn -> isVisible() && !buttonWorkshop -> isVisible()) militaryWidget -> hide();
    else militaryWidget -> show();

    if (!buttonTower -> isVisible() && !buttonWall -> isVisible()) defenseWidget -> hide();
    else defenseWidget -> show();

    if (!buttonExpandTerrain -> isVisible() && !militaryWidget -> isVisible()) generalWidget -> hide();
    else generalWidget -> show();

    if (!generalWidget -> isVisible() && !resourceWidget -> isVisible() && !serviceWidget -> isVisible() && !militaryWidget -> isVisible() && !defenseWidget->isVisible()) buildingsPanel -> hide();
    else buildingsPanel -> show();
}

bool Hud::getPopUpOpen() {
    return popUpOpen;
}

/////////////////////DEBUG/////////////////////////
void Hud::InitDebug(){
    debugTimer = new Timer (0.5, true);
    debugTimer -> setCallback([&]() {
        debug();
    });

    ///// DEBUG /////
    i32 melees = 
        Human::Instance() -> getUnitManager() -> getTroopAmount("StandardM") + 
        Human::Instance() -> getUnitManager() -> getTroopAmount("AdvancedM");
    i32 ranges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount("StandardR") + 
        Human::Instance() -> getUnitManager() -> getTroopAmount("AdvancedR");
    i32 sieges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount("Desintegrator") + 
        Human::Instance() -> getUnitManager() -> getTroopAmount("Launcher");

    std::stringstream os;
    os = std::stringstream();
    os << "Melee: " << std::to_string(melees);
    playerMelees = new Label(playerResources, os.str());
    os = std::stringstream();
    playerMelees ->hide();
    os << "Ranged: " << std::to_string(ranges);
    playerRangeds = new Label(playerResources, os.str());
    os = std::stringstream();
    playerRangeds ->hide();
    os << "Siege: " << std::to_string(sieges);
    playerSieges = new Label(playerResources, os.str());
    os = std::stringstream();
    playerSieges ->hide();
    os << "FPS: " << std::to_string(Window::Instance() -> getFrameRate());
    framerateLabel = new Label(os.str());
    framerateLabel -> setSize(Vector2<i32> (50, 15));
    framerateLabel -> setPosition(Vector2<i32> (0, 0));
    os = std::stringstream();
    
    iaResources = new Panel("IA Resources");
    iaResources -> hide();
    iaResources -> setVerticalLayout();
    iaResources -> setPosition(Vector2<i32>(1000, 0));
    iaResources -> setSize(Vector2<i32> (200, 270));
    melees = 
        IA::Instance() -> getUnitManager() -> getTroopAmount("StandardM") + 
        IA::Instance() -> getUnitManager() -> getTroopAmount("AdvancedM");
    ranges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount("StandardR") + 
        IA::Instance() -> getUnitManager() -> getTroopAmount("AdvancedR");
    sieges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount("Desintegrator") + 
        IA::Instance() -> getUnitManager() -> getTroopAmount("Launcher");
    std::stringstream iaos;
    iaos << "Metal: " << std::to_string(IA::Instance() -> metalAmount);
    iaMetalAmount = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Crystal: " << std::to_string(IA::Instance() -> crystalAmount);
    iaCrystalAmount = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Citizens: " << std::to_string(IA::Instance() -> getCitizens());
    iaCitizens = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Warriors: " << std::to_string(IA::Instance() -> getUnitManager() -> getUnitFighters());
    iaUnitFighters = new Label(iaResources, iaos.str());
    iaos = std::stringstream();
    iaos << "Happiness: " << std::to_string(IA::Instance() -> getHappiness());
    iaHappiness = new Label(iaResources, iaos.str());
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
    
	Window::Instance() -> setGUI();
}

void Hud::debug() {
    i32 melees = 
        Human::Instance() -> getUnitManager() -> getTroopAmount("StandardM") + 
        Human::Instance() -> getUnitManager() -> getTroopAmount("AdvancedM");
    i32 ranges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount("StandardR") + 
        Human::Instance() -> getUnitManager() -> getTroopAmount("AdvancedR");
    i32 sieges = 
        Human::Instance() -> getUnitManager() -> getTroopAmount("Desintegrator") + 
        Human::Instance() -> getUnitManager() -> getTroopAmount("Launcher");

    std::stringstream os;
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
    os << "FPS: " << std::to_string(Window::Instance() -> getFrameRate());
    framerateLabel -> setLabel(os.str());
    os = std::stringstream();

    melees = 
        IA::Instance() -> getUnitManager() -> getTroopAmount("StandardM") + 
        IA::Instance() -> getUnitManager() -> getTroopAmount("AdvancedM");
    ranges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount("StandardR") + 
        IA::Instance() -> getUnitManager() -> getTroopAmount("AdvancedR");
    sieges = 
        IA::Instance() -> getUnitManager() -> getTroopAmount("Desintegrator") + 
        IA::Instance() -> getUnitManager() -> getTroopAmount("Launcher");

    std::stringstream iaos;
    iaos << "Metal: " << std::to_string(IA::Instance() -> metalAmount);
    iaMetalAmount -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Crystal: " << std::to_string(IA::Instance() -> crystalAmount);
    iaCrystalAmount -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Citizens: " << std::to_string(IA::Instance() -> getCitizens());
    iaCitizens -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "UnitFighters: " << std::to_string(IA::Instance() -> getUnitManager() -> getUnitFighters());
    iaUnitFighters -> setLabel(iaos.str());
    iaos = std::stringstream();
    iaos << "Happiness: " << std::to_string(IA::Instance() -> getHappiness());
    iaHappiness -> setLabel(iaos.str());
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
    if (IA::Instance() -> getFast() == true) {
        iaos << "Timer: Fast";
    } else {
        iaos << "Timer: Slow";
    }
    iaBehaviour -> setLabel(iaos.str());
    iaos = std::stringstream();
}