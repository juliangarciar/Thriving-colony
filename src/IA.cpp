#include "IA.h"
#include "Game.h"
#include <WorldEngine/WorldGeometry.h>

#include "GraphicEngine/Window.h"
#include "Human.h"
#include "Map.h"
#include "AIEngine/CAttack.h"
#include "AIEngine/CBuild.h"
#include "AIEngine/CDeployTroops.h"
#include "AIEngine/CRecruit.h"
#include "AIEngine/CRetreat.h"
#include "AIEngine/AAttack.h"
#include "AIEngine/ABuild.h"
#include "AIEngine/ADeployTroops.h"
#include "AIEngine/ARecruit.h"
#include "AIEngine/ARetreat.h"

IA* IA::instance = 0;

IA* IA::Instance() {
    if (instance == 0) {
        instance = new IA();
    }
    return instance;
}

IA::IA() : Player() {
    
}

IA::~IA() {
    delete tree;
    //delete nodeRootIA;
    delete buildings;
    delete units;
    choices -> clear();
    delete choices;
    delete rootNode;
    delete updateFastTimer;
    delete updateSlowTimer;
}

void IA::Init(std::string _race) {
    Player::Init();

    buildings = new BuildingManager(Enumeration::Team::IA, _race);
    units = new UnitManager(Enumeration::Team::IA, _race);

    // Choose a behaviour
    chooseBehaviour();
    // Create a behaviour and a root node and set them up according to the behaviour
    tree = new BehaviourTree();
    tree -> init(behaviour);
    //nodeRootIA = new RootNode();
    //nodeRootIA -> init(behaviour);

    // Choices for the debugging system
    choiceIndex = 0;
    initializeChoices();

    updateFastTimer = new Timer(1.00, true);
	updateFastTimer -> setCallback([&](){
		//nodeRootIA -> question();
		rootNode -> Update();
		updateFastTimer -> restart();
		updateSlowTimer -> restart();
	});
    updateSlowTimer = new Timer(3.00, true);
	updateSlowTimer -> setCallback([&](){
		//nodeRootIA -> question();
		rootNode -> Update();
		updateFastTimer -> restart();
		updateSlowTimer -> restart();
	});
}

void IA::Update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    Vector3<f32> tarPos = Map::Instance() -> getCamera() -> getTarPos();
    Vector2<f32> IAPos = buildings -> getBuilding(0) -> getPosition();
    fast = false;
    if (((IAPos . x + 2000 > tarPos.x && IAPos . x - 2000 < tarPos.x) && (IAPos . y + 2000 > tarPos.z && IAPos . y - 2000 < tarPos.z)) || underAttack) {
        fast = true;
    }
    if (fast == true) {
		updateFastTimer -> tick();
    } else {
		updateSlowTimer -> tick();
    }
	updateTimer -> tick();
}

void IA::CleanUp() {
    delete tree;
    //delete nodeRootIA;
    // Add a method to clean the cells the buildings inahbit
    delete buildings;
    delete units;
    choices -> clear();
    delete choices;
    delete updateTimer;
    delete updateFastTimer;
    delete updateSlowTimer;
    delete rootNode;
}

BehaviourTree* IA::getTree() {
    return tree;
}

/*
* Return a position of the map where there is nothing built
* Goes over the vector of buildings looking up, right, down and left of every building built
* until find the first empty position
*/
Vector2<f32> IA::determinatePositionBuilding() {
    Vector2<f32> v;
    bool found = false;
    bool occupied = false;
    std::map<i32, Building*> *b = buildings -> getBuildings();

    // If it is the first building start always on the same position
    if (b -> size() == 0) {
        /**
         * These coordinates determine the position of the main building
         * the y component of it is determined based on the map
         */
		//ToDo: parametrizar
        f32 startingX = 2000;
        f32 startingZ = 2000;
        v.set(startingX, startingZ);
        v.y = Map::Instance() -> getTerrain() -> getY(v.x, v.y);
    } else {
        //When there are some buildings
        Vector2<f32> v2;
        Vector2<f32> v3;
        for (std::map<i32,Building*>::iterator it = b -> begin(); it != b -> end() && found == false; ++it){
            v2 = it -> second -> getPosition();
            occupied = false;
            v = Vector2<f32>(v2 . x, v2 . y + 300);
            for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                v3 = it2 -> second -> getPosition();
                if (v3 . x == v.x && v3 . y == v.y) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = Vector2<f32>(v2 . x + 300, v2 . y);
                occupied = false;
                for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                    v3 = it2 -> second -> getPosition();
                    if (v3 . x == v.x && v3 . y == v.y) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = Vector2<f32>(v2 . x, v2 . y - 300);
                    occupied = false;
                    for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                        v3 = it2 -> second -> getPosition();
                        if (v3 . x == v.x && v3 . y == v.y) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = Vector2<f32>(v2 . x - 300, v2 . y);
                        occupied = false;
                        for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                            v3 = it2 -> second -> getPosition();
                            if (v3 . x == v.x && v3 . y == v.y) {
                                occupied = true;
                            }
                        }
                        if (occupied == false ) {
                            found = true;
                        }
                    }
                }
            }
        }
        v.y = Map::Instance() -> getTerrain() -> getY(v.x, v.y);
    }
    return v;
}

bool IA::getUnderAttack() {
    underAttack = false;
    Vector2<f32> pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
    i32 requesterRange = 1000;
    
    f32 xaux = 0;
    f32 yaux = 0;
    f32 dist = 0;

        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = Human::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it){
            if (it -> second != nullptr) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() . x - pos . x;
                yaux = it -> second -> getPosition() . y - pos . y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

            if (dist <= requesterRange) {
                underAttack = true;
            }
        }
    }
    return underAttack;
}

void IA::chooseBehaviour() {
    // RAndomize the seed
    srand(time(nullptr));
    // Determine a number between 0 and 4, the number of possible behaviours for the AI to choose
    behaviour = (Enumeration::IABehaviour)(rand()%(4-0 + 1) + 0);
    switch (behaviour) {
        case Enumeration::IABehaviour::VeryHappy:
            chosenBehaviour = "Very happy";
            veryHappyBehaviour();
        break;
        case Enumeration::IABehaviour::Happy: 
            chosenBehaviour = "Happy";   
            happyBehaviour(); 
        break;
        case Enumeration::IABehaviour::Neutral:
            chosenBehaviour = "Neutral"; 
            neutralBehaviour();
        break;
        case Enumeration::IABehaviour::Unhappy: 
            chosenBehaviour = "Unhappy";
            unhappyBehaviour();
        break;
        case Enumeration::IABehaviour::VeryUnhappy: 
            chosenBehaviour = "Very unhappy";
            veryUnhappyBehaviour();
        break;
    }
}

void IA::veryHappyBehaviour() {
    std::vector<Behaviour*> auxroot;

    //Defend
    std::vector<Behaviour*> auxdef;
    auxdef.push_back(new CDeployTroops(new ADeployTroops()));
    std::vector<Behaviour*> aux1;
    aux1.push_back(new CBuild(new ABuild(), "DefenseBarrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    aux1.push_back(new CRecruit(new ARecruit(), "DefenseStandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxdef.push_back(new Selector(aux1));
    auxroot.push_back(new Selector(auxdef));

    //Attack
    std::vector<Behaviour*> auxat;
    auxat.push_back(new CRetreat(new ARetreat()));
    auxat.push_back(new CAttack(new AAttack()));
    auxroot.push_back(new Selector(auxat));

    //City
    std::vector<Behaviour*> auxcity;
    //Services
    std::vector<Behaviour*> auxser;
    auxser.push_back(new CBuild(new ABuild(), "Hospital", buildings->getBuildingData("Hospital").metalCost, buildings->getBuildingData("Hospital").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "Market", buildings->getBuildingData("Market").metalCost, buildings->getBuildingData("Market").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "School", buildings->getBuildingData("School").metalCost, buildings->getBuildingData("School").crystalCost));
    auxcity.push_back(new Selector(auxser));
    //Resources
    std::vector<Behaviour*> auxres;
    auxres.push_back(new CBuild(new ABuild(), "Quarry", buildings->getBuildingData("Quarry").metalCost, buildings->getBuildingData("Quarry").crystalCost));
    auxres.push_back(new CBuild(new ABuild(), "Siderurgy", buildings->getBuildingData("Siderurgy").metalCost, buildings->getBuildingData("Siderurgy").crystalCost));
    auxcity.push_back(new Selector(auxres));
    //Houses
    auxcity.push_back(new CBuild(new ABuild(), "House", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));
    //Army
    std::vector<Behaviour*> auxarmy;
    //Units
    std::vector<Behaviour*> auxunits;
    //Melees
    std::vector<Behaviour*> auxmel;
    auxmel.push_back(new CRecruit(new ARecruit(), "Idol", units->getUnitData("Idol").metalCost, units->getUnitData("Idol").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "AdvancedM", units->getUnitData("AdvancedM").metalCost, units->getUnitData("AdvancedM").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "StandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxunits.push_back(new Selector(auxmel));
    //Ranged
    std::vector<Behaviour*> auxran;
    auxran.push_back(new CRecruit(new ARecruit(), "AdvancedR", units->getUnitData("AdvancedR").metalCost, units->getUnitData("AdvancedR").crystalCost));
    auxran.push_back(new CRecruit(new ARecruit(), "StandardR", units->getUnitData("StandardR").metalCost, units->getUnitData("StandardR").crystalCost));
    auxunits.push_back(new Selector(auxran));
    //Siege
    std::vector<Behaviour*> auxsie;
    auxsie.push_back(new CRecruit(new ARecruit(), "Desintegrator", units->getUnitData("Desintegrator").metalCost, units->getUnitData("Desintegrator").crystalCost));
    auxsie.push_back(new CRecruit(new ARecruit(), "Launcher", units->getUnitData("Launcher").metalCost, units->getUnitData("Launcher").crystalCost));
    auxunits.push_back(new Selector(auxsie));
    auxarmy.push_back(new Selector(auxunits));
    //Buildings
    std::vector<Behaviour*> auxbuil;
    auxbuil.push_back(new CBuild(new ABuild(), "Barrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Barn", buildings->getBuildingData("Barn").metalCost, buildings->getBuildingData("Barn").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Workshop", buildings->getBuildingData("Workshop").metalCost, buildings->getBuildingData("Workshop").crystalCost));
    auxarmy.push_back(new Selector(auxbuil));
    auxcity.push_back(new Selector(auxarmy));
    auxroot.push_back(new Selector(auxcity));

    //Last choice
    auxroot.push_back(new CBuild(new ABuild(), "LastChoiceHouse", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));

    rootNode = new ActiveSelector(auxroot);
}

void IA::happyBehaviour() {
    std::vector<Behaviour*> auxroot;

    //Defend
    std::vector<Behaviour*> auxdef;
    auxdef.push_back(new CDeployTroops(new ADeployTroops()));
    std::vector<Behaviour*> aux1;
    aux1.push_back(new CBuild(new ABuild(), "DefenseBarrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    aux1.push_back(new CRecruit(new ARecruit(), "DefenseStandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxdef.push_back(new Selector(aux1));
    auxroot.push_back(new Selector(auxdef));

    //Attack
    std::vector<Behaviour*> auxat;
    auxat.push_back(new CRetreat(new ARetreat()));
    auxat.push_back(new CAttack(new AAttack()));
    auxroot.push_back(new Selector(auxat));

    //City
    std::vector<Behaviour*> auxcity;
    //Houses
    auxcity.push_back(new CBuild(new ABuild(), "House", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));
    //Services
    std::vector<Behaviour*> auxser;
    auxser.push_back(new CBuild(new ABuild(), "Hospital", buildings->getBuildingData("Hospital").metalCost, buildings->getBuildingData("Hospital").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "Market", buildings->getBuildingData("Market").metalCost, buildings->getBuildingData("Market").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "School", buildings->getBuildingData("School").metalCost, buildings->getBuildingData("School").crystalCost));
    auxcity.push_back(new Selector(auxser));
    //Resources
    std::vector<Behaviour*> auxres;
    auxres.push_back(new CBuild(new ABuild(), "Quarry", buildings->getBuildingData("Quarry").metalCost, buildings->getBuildingData("Quarry").crystalCost));
    auxres.push_back(new CBuild(new ABuild(), "Siderurgy", buildings->getBuildingData("Siderurgy").metalCost, buildings->getBuildingData("Siderurgy").crystalCost));
    auxcity.push_back(new Selector(auxres));
    //Army
    std::vector<Behaviour*> auxarmy;
    //Units
    std::vector<Behaviour*> auxunits;
    //Melees
    std::vector<Behaviour*> auxmel;
    auxmel.push_back(new CRecruit(new ARecruit(), "Idol", units->getUnitData("Idol").metalCost, units->getUnitData("Idol").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "AdvancedM", units->getUnitData("AdvancedM").metalCost, units->getUnitData("AdvancedM").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "StandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxunits.push_back(new Selector(auxmel));
    //Ranged
    std::vector<Behaviour*> auxran;
    auxran.push_back(new CRecruit(new ARecruit(), "AdvancedR", units->getUnitData("AdvancedR").metalCost, units->getUnitData("AdvancedR").crystalCost));
    auxran.push_back(new CRecruit(new ARecruit(), "StandardR", units->getUnitData("StandardR").metalCost, units->getUnitData("StandardR").crystalCost));
    auxunits.push_back(new Selector(auxran));
    //Siege
    std::vector<Behaviour*> auxsie;
    auxsie.push_back(new CRecruit(new ARecruit(), "Desintegrator", units->getUnitData("Desintegrator").metalCost, units->getUnitData("Desintegrator").crystalCost));
    auxsie.push_back(new CRecruit(new ARecruit(), "Launcher", units->getUnitData("Launcher").metalCost, units->getUnitData("Launcher").crystalCost));
    auxunits.push_back(new Selector(auxsie));
    auxarmy.push_back(new Selector(auxunits));
    //Buildings
    std::vector<Behaviour*> auxbuil;
    auxbuil.push_back(new CBuild(new ABuild(), "Barrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Barn", buildings->getBuildingData("Barn").metalCost, buildings->getBuildingData("Barn").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Workshop", buildings->getBuildingData("Workshop").metalCost, buildings->getBuildingData("Workshop").crystalCost));
    auxarmy.push_back(new Selector(auxbuil));
    auxcity.push_back(new Selector(auxarmy));
    auxroot.push_back(new Selector(auxcity));
    
    //Last choice
    auxroot.push_back(new CBuild(new ABuild(), "LastChoiceHouse", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));

    rootNode = new ActiveSelector(auxroot);
}

void IA::neutralBehaviour() {
    std::vector<Behaviour*> auxroot;

    //Defend
    std::vector<Behaviour*> auxdef;
    auxdef.push_back(new CDeployTroops(new ADeployTroops()));
    std::vector<Behaviour*> aux1;
    aux1.push_back(new CBuild(new ABuild(), "DefenseBarrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    aux1.push_back(new CRecruit(new ARecruit(), "DefenseStandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxdef.push_back(new Selector(aux1));
    auxroot.push_back(new Selector(auxdef));

    //Attack
    std::vector<Behaviour*> auxat;
    auxat.push_back(new CRetreat(new ARetreat()));
    auxat.push_back(new CAttack(new AAttack()));
    auxroot.push_back(new Selector(auxat));

    //City
    std::vector<Behaviour*> auxcity;
    //Resources
    std::vector<Behaviour*> auxres;
    auxres.push_back(new CBuild(new ABuild(), "Quarry", buildings->getBuildingData("Quarry").metalCost, buildings->getBuildingData("Quarry").crystalCost));
    auxres.push_back(new CBuild(new ABuild(), "Siderurgy", buildings->getBuildingData("Siderurgy").metalCost, buildings->getBuildingData("Siderurgy").crystalCost));
    auxcity.push_back(new Selector(auxres));
    //Houses
    auxcity.push_back(new CBuild(new ABuild(), "House", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));
    //Services
    std::vector<Behaviour*> auxser;
    auxser.push_back(new CBuild(new ABuild(), "Hospital", buildings->getBuildingData("Hospital").metalCost, buildings->getBuildingData("Hospital").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "Market", buildings->getBuildingData("Market").metalCost, buildings->getBuildingData("Market").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "School", buildings->getBuildingData("School").metalCost, buildings->getBuildingData("School").crystalCost));
    auxcity.push_back(new Selector(auxser));
    //Army
    std::vector<Behaviour*> auxarmy;
    //Units
    std::vector<Behaviour*> auxunits;
    //Melees
    std::vector<Behaviour*> auxmel;
    auxmel.push_back(new CRecruit(new ARecruit(), "Idol", units->getUnitData("Idol").metalCost, units->getUnitData("Idol").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "AdvancedM", units->getUnitData("AdvancedM").metalCost, units->getUnitData("AdvancedM").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "StandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxunits.push_back(new Selector(auxmel));
    //Ranged
    std::vector<Behaviour*> auxran;
    auxran.push_back(new CRecruit(new ARecruit(), "AdvancedR", units->getUnitData("AdvancedR").metalCost, units->getUnitData("AdvancedR").crystalCost));
    auxran.push_back(new CRecruit(new ARecruit(), "StandardR", units->getUnitData("StandardR").metalCost, units->getUnitData("StandardR").crystalCost));
    auxunits.push_back(new Selector(auxran));
    //Siege
    std::vector<Behaviour*> auxsie;
    auxsie.push_back(new CRecruit(new ARecruit(), "Desintegrator", units->getUnitData("Desintegrator").metalCost, units->getUnitData("Desintegrator").crystalCost));
    auxsie.push_back(new CRecruit(new ARecruit(), "Launcher", units->getUnitData("Launcher").metalCost, units->getUnitData("Launcher").crystalCost));
    auxunits.push_back(new Selector(auxsie));
    auxarmy.push_back(new Selector(auxunits));
    //Buildings
    std::vector<Behaviour*> auxbuil;
    auxbuil.push_back(new CBuild(new ABuild(), "Barrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Barn", buildings->getBuildingData("Barn").metalCost, buildings->getBuildingData("Barn").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Workshop", buildings->getBuildingData("Workshop").metalCost, buildings->getBuildingData("Workshop").crystalCost));
    auxarmy.push_back(new Selector(auxbuil));
    auxcity.push_back(new Selector(auxarmy));
    auxroot.push_back(new Selector(auxcity));

    //Last choice
    auxroot.push_back(new CBuild(new ABuild(), "LastChoiceHouse", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));

    rootNode = new ActiveSelector(auxroot);
}

void IA::unhappyBehaviour() {
   std::vector<Behaviour*> auxroot;

    //Defend
    std::vector<Behaviour*> auxdef;
    auxdef.push_back(new CDeployTroops(new ADeployTroops()));
    std::vector<Behaviour*> aux1;
    aux1.push_back(new CBuild(new ABuild(), "DefenseBarrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    aux1.push_back(new CRecruit(new ARecruit(), "DefenseStandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxdef.push_back(new Selector(aux1));
    auxroot.push_back(new Selector(auxdef));

    //Attack
    std::vector<Behaviour*> auxat;
    auxat.push_back(new CRetreat(new ARetreat()));
    auxat.push_back(new CAttack(new AAttack()));
    auxroot.push_back(new Selector(auxat));

    //City
    std::vector<Behaviour*> auxcity;
    //Resources
    std::vector<Behaviour*> auxres;
    auxres.push_back(new CBuild(new ABuild(), "Quarry", buildings->getBuildingData("Quarry").metalCost, buildings->getBuildingData("Quarry").crystalCost));
    auxres.push_back(new CBuild(new ABuild(), "Siderurgy", buildings->getBuildingData("Siderurgy").metalCost, buildings->getBuildingData("Siderurgy").crystalCost));
    auxcity.push_back(new Selector(auxres));
    //Army
    std::vector<Behaviour*> auxarmy;
    //Units
    std::vector<Behaviour*> auxunits;
    //Melees
    std::vector<Behaviour*> auxmel;
    auxmel.push_back(new CRecruit(new ARecruit(), "Idol", units->getUnitData("Idol").metalCost, units->getUnitData("Idol").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "AdvancedM", units->getUnitData("AdvancedM").metalCost, units->getUnitData("AdvancedM").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "StandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxunits.push_back(new Selector(auxmel));
    //Ranged
    std::vector<Behaviour*> auxran;
    auxran.push_back(new CRecruit(new ARecruit(), "AdvancedR", units->getUnitData("AdvancedR").metalCost, units->getUnitData("AdvancedR").crystalCost));
    auxran.push_back(new CRecruit(new ARecruit(), "StandardR", units->getUnitData("StandardR").metalCost, units->getUnitData("StandardR").crystalCost));
    auxunits.push_back(new Selector(auxran));
    //Siege
    std::vector<Behaviour*> auxsie;
    auxsie.push_back(new CRecruit(new ARecruit(), "Desintegrator", units->getUnitData("Desintegrator").metalCost, units->getUnitData("Desintegrator").crystalCost));
    auxsie.push_back(new CRecruit(new ARecruit(), "Launcher", units->getUnitData("Launcher").metalCost, units->getUnitData("Launcher").crystalCost));
    auxunits.push_back(new Selector(auxsie));
    auxarmy.push_back(new Selector(auxunits));
    //Buildings
    std::vector<Behaviour*> auxbuil;
    auxbuil.push_back(new CBuild(new ABuild(), "Barrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Barn", buildings->getBuildingData("Barn").metalCost, buildings->getBuildingData("Barn").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Workshop", buildings->getBuildingData("Workshop").metalCost, buildings->getBuildingData("Workshop").crystalCost));
    auxarmy.push_back(new Selector(auxbuil));
    auxcity.push_back(new Selector(auxarmy));
    auxroot.push_back(new Selector(auxcity));
    //Houses
    auxcity.push_back(new CBuild(new ABuild(), "House", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));
    //Services
    std::vector<Behaviour*> auxser;
    auxser.push_back(new CBuild(new ABuild(), "Hospital", buildings->getBuildingData("Hospital").metalCost, buildings->getBuildingData("Hospital").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "Market", buildings->getBuildingData("Market").metalCost, buildings->getBuildingData("Market").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "School", buildings->getBuildingData("School").metalCost, buildings->getBuildingData("School").crystalCost));
    auxcity.push_back(new Selector(auxser));

    //Last choice
    auxroot.push_back(new CBuild(new ABuild(), "LastChoiceHouse", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));

    rootNode = new ActiveSelector(auxroot);
}

void IA::veryUnhappyBehaviour() {
    std::vector<Behaviour*> auxroot;

    //Defend
    std::vector<Behaviour*> auxdef;
    auxdef.push_back(new CDeployTroops(new ADeployTroops()));
    std::vector<Behaviour*> aux1;
    aux1.push_back(new CBuild(new ABuild(), "DefenseBarrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    aux1.push_back(new CRecruit(new ARecruit(), "DefenseStandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxdef.push_back(new Selector(aux1));
    auxroot.push_back(new Selector(auxdef));

    //Attack
    std::vector<Behaviour*> auxat;
    auxat.push_back(new CRetreat(new ARetreat()));
    auxat.push_back(new CAttack(new AAttack()));
    auxroot.push_back(new Selector(auxat));

    //City
    std::vector<Behaviour*> auxcity;
    //Army
    std::vector<Behaviour*> auxarmy;
    //Units
    std::vector<Behaviour*> auxunits;
    //Melees
    std::vector<Behaviour*> auxmel;
    auxmel.push_back(new CRecruit(new ARecruit(), "Idol", units->getUnitData("Idol").metalCost, units->getUnitData("Idol").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "AdvancedM", units->getUnitData("AdvancedM").metalCost, units->getUnitData("AdvancedM").crystalCost));
    auxmel.push_back(new CRecruit(new ARecruit(), "StandardM", units->getUnitData("StandardM").metalCost, units->getUnitData("StandardM").crystalCost));
    auxunits.push_back(new Selector(auxmel));
    //Ranged
    std::vector<Behaviour*> auxran;
    auxran.push_back(new CRecruit(new ARecruit(), "AdvancedR", units->getUnitData("AdvancedR").metalCost, units->getUnitData("AdvancedR").crystalCost));
    auxran.push_back(new CRecruit(new ARecruit(), "StandardR", units->getUnitData("StandardR").metalCost, units->getUnitData("StandardR").crystalCost));
    auxunits.push_back(new Selector(auxran));
    //Siege
    std::vector<Behaviour*> auxsie;
    auxsie.push_back(new CRecruit(new ARecruit(), "Desintegrator", units->getUnitData("Desintegrator").metalCost, units->getUnitData("Desintegrator").crystalCost));
    auxsie.push_back(new CRecruit(new ARecruit(), "Launcher", units->getUnitData("Launcher").metalCost, units->getUnitData("Launcher").crystalCost));
    auxunits.push_back(new Selector(auxsie));
    auxarmy.push_back(new Selector(auxunits));
    //Buildings
    std::vector<Behaviour*> auxbuil;
    auxbuil.push_back(new CBuild(new ABuild(), "Barrack", buildings->getBuildingData("Barrack").metalCost, buildings->getBuildingData("Barrack").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Barn", buildings->getBuildingData("Barn").metalCost, buildings->getBuildingData("Barn").crystalCost));
    auxbuil.push_back(new CBuild(new ABuild(), "Workshop", buildings->getBuildingData("Workshop").metalCost, buildings->getBuildingData("Workshop").crystalCost));
    auxarmy.push_back(new Selector(auxbuil));
    auxcity.push_back(new Selector(auxarmy));
    auxroot.push_back(new Selector(auxcity));
    //Houses
    auxcity.push_back(new CBuild(new ABuild(), "House", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));
    //Resources
    std::vector<Behaviour*> auxres;
    auxres.push_back(new CBuild(new ABuild(), "Quarry", buildings->getBuildingData("Quarry").metalCost, buildings->getBuildingData("Quarry").crystalCost));
    auxres.push_back(new CBuild(new ABuild(), "Siderurgy", buildings->getBuildingData("Siderurgy").metalCost, buildings->getBuildingData("Siderurgy").crystalCost));
    auxcity.push_back(new Selector(auxres));
    //Services
    std::vector<Behaviour*> auxser;
    auxser.push_back(new CBuild(new ABuild(), "Hospital", buildings->getBuildingData("Hospital").metalCost, buildings->getBuildingData("Hospital").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "Market", buildings->getBuildingData("Market").metalCost, buildings->getBuildingData("Market").crystalCost));
    auxser.push_back(new CBuild(new ABuild(), "School", buildings->getBuildingData("School").metalCost, buildings->getBuildingData("School").crystalCost));
    auxcity.push_back(new Selector(auxser));

    //Last choice
    auxroot.push_back(new CBuild(new ABuild(), "LastChoiceHouse", buildings->getBuildingData("House").metalCost, buildings->getBuildingData("House").crystalCost));

    rootNode = new ActiveSelector(auxroot);
}

std::string IA::getNextChoice() {
    return choices -> at(choiceIndex);
}

void IA::setChoiceIndex(i32 newIndex) {
    choiceIndex = newIndex;
}

std::string IA::getChosenBehaviour() {
    return chosenBehaviour;
}

ActiveSelector* IA::getRootNode() {
    return rootNode;
}

bool IA::getFast() {
    return fast;
}

// Down here so it doesn't clutter the constructor
void IA::initializeChoices() {
    // IMPORTANTE::::::::
    // TIENE QUE ESTAR EN EL ORDEN DE LA ENUMERACION
    // IAChoices QUE HAY EN enumeration.h, SI NO NO IRA BIEN
    // Y NOS LIAREMOS. SI SE PUEDE PASAR ALGUN DIA A ARRAY
    // ENTONCES SE PUEDE QUEDAR CONTROLAR QUE INDICE TIENE QUE STRING
    // Y TODO ES MAS MANEJABLE. PERO POR AHORA NO HACE MAS QUE DAR ERRORES
    // ASI QUE LO HE DEJADO COMO VECTOR Y AU (Y quizas un map?)
    choices = new std::vector<std::string>();
    choices -> push_back("Deploying troops");
    choices -> push_back("Train melee footman");
    choices -> push_back("Build barrack");
    choices -> push_back("Attacking");
    choices -> push_back("Retracting troops");
    choices -> push_back("Build school");
    choices -> push_back("Build market");
    choices -> push_back("Build hospital");
    choices -> push_back("Build siderurgy");
    choices -> push_back("Build quarry");
    choices -> push_back("Build home");
    //choices -> push_back(L"Melee footman");
    choices -> push_back("Train mounted melee");
    choices -> push_back("Train creature");
    choices -> push_back("Train ranged footman");
    choices -> push_back("Train mounted ranged");
    choices -> push_back("Train catapult");
    choices -> push_back("Train ram");
    //choices -> push_back(L"Barrack");
    choices -> push_back("Build barn");
    choices -> push_back("Build workshop");
    choices -> push_back("Build tower");
    choices -> push_back("Build wall");
    
    //ARRAY FORM
    // SI ALGUN DIA SE PONE ASI SERIA FANTISTOCOSO
    /*
    // Commented choices are repeated through
    choices[Enumeration::IAChoices::DeployingTroops] = "Deploying troops";
    choices[Enumeration::IAChoices::TrainMeleeFootman] = "Train melee footman";
    choices[Enumeration::IAChoices::BuildBarrack] = "Build barrack";
    choices[Enumeration::IAChoices::Attacking] = "Attacking";
    choices[Enumeration::IAChoices::RetractingTroops] = "Retracting troops";
    choices[Enumeration::IAChoices::BuildSchool] = "Build school";
    choices[Enumeration::IAChoices::BuildMarket] = "Build market";
    choices[Enumeration::IAChoices::BuildHospital] = "Build hospital";
    choices[Enumeration::IAChoices::BuildSiderurgy] = "Build siderurgy";
    choices[Enumeration::IAChoices::BuildQuarry] = "Build quarry";
    choices[Enumeration::IAChoices::BuildHome] = "Build home";
    //choices[0] = "Melee footman";
    choices[Enumeration::IAChoices::TrainMountedMelee] = "Train mounted melee";
    choices[Enumeration::IAChoices::TrainCreature] = "Train creature";
    choices[Enumeration::IAChoices::TrainRangedFootman] = "Train ranged footman";
    choices[Enumeration::IAChoices::TrainMountedRanged] = "Train mounted ranged";
    choices[Enumeration::IAChoices::TrainCatapult] = "Train catapult";
    choices[Enumeration::IAChoices::TrainRam] = "Train ram";
    //choices[0] = "Barrack";
    choices[Enumeration::IAChoices::BuildBarn] = "Build barn";
    choices[Enumeration::IAChoices::BuildWorkshop] = "Build workshop";
    choices[Enumeration::IAChoices::BuildTower] = "Build tower";
    choices[Enumeration::IAChoices::BuildWall] = "Build wall";
    //choices[0] = "House"
    */
}