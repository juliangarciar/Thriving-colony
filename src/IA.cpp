#include "IA.h"
#include "Game.h"
#include "Human.h"

IA::IA() : Player() {
    
}

void IA::init() {
    updateTimer = 0;
    // Choose a behaviour
    chooseBehaviour();
    // Create a behaviour and a root node and set them up according to the behaviour
    tree = new BehaviourTree();
    tree -> init(behaviour);
    nodeRootIA = new RootNode();
    nodeRootIA -> init(behaviour);

    buildings = new BuildingManager();
    units = new UnitManager(Enumeration::Team::IA, Enumeration::BreedType::Kaonov);

    // Choices for the debugging system
    choiceIndex = 0;
    initializeChoices();
}

void IA::cleanUp() {
    delete tree;
    delete nodeRootIA;
    delete buildings;
    delete units;
    choices -> clear();
    delete choices;
}

IA::~IA() {
    delete tree;
    delete nodeRootIA;
    delete buildings;
    delete units;
    choices -> clear();
    delete choices;
}

IA* IA::instance = 0;

bool IA::deployedTroops = false;
bool IA::closedDoors = false;

IA* IA::getInstance() {
    if (instance == 0) {
        instance = new IA();
    }
    return instance;
}

BehaviourTree* IA::getTree() {
    return tree;
}

void IA::update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    if (updateTimer <= 0) {
        gainResources();
        nodeRootIA -> question();
        if (units -> getInMapTroops() -> empty()) {
            deployedTroops = false;
        }
        if (units -> getInHallTroops() -> empty()) {
            deployedTroops = true;
        }
        updateTimer = 1;
    } else {
        updateTimer -= Game::Instance() -> getWindow() -> getDeltaTime();
    }
}

/*
* Return a position of the map where there is nothing built
* Goes over the vector of buildings looking up, right, down and left of every building built
* until find the first empty position
*/
Vector3<float> IA::determinatePositionBuilding() {
    Vector3<float> v;
    bool found = false;
    bool occupied = false;
    std::map<int, Building*> *b = buildings -> getBuildings();

    // If it is the first building start always on the same position
    if (b -> size() == 0) {
        /**
         * These coordinates determine the position of the main building
         * the y component of it is determined based on the map
         */
        float startingX = 2000;
        float startingZ = 2000;
        v.set(startingX, 0, startingZ);
        v.y = Game::Instance() -> getGameState()  -> getTerrain() -> getY(v.x, v.z);
    } else {

        //When there are some buildings
        Vector3<float> *v2 = 0;
        Vector3<float> *v3 = 0;
        for (std::map<int,Building*>::iterator it = b -> begin(); it != b -> end() && found == false; ++it){
            v2 = it -> second -> getPosition();
            occupied = false;
            v = Vector3<float>(v2 -> x, v2 -> y, v2 -> z + 200);
            for (std::map<int,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                v3 = it2 -> second -> getPosition();
                if (v3 -> x == v.x && v3 -> z == v.z) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = Vector3<float>(v2 -> x + 200, v2 -> y, v2 -> z);
                occupied = false;
                for (std::map<int,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                    v3 = it2 -> second -> getPosition();
                    if (v3 -> x == v.x && v3 -> z == v.z) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = Vector3<float>(v2 -> x, v2 -> y, v2 -> z - 200);
                    occupied = false;
                    for (std::map<int,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                        v3 = it2 -> second -> getPosition();
                        if (v3 -> x == v.x && v3 -> z == v.z) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = Vector3<float>(v2 -> x - 200, v2 -> y, v2 -> z);
                        occupied = false;
                        for (std::map<int,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                            v3 = it2 -> second -> getPosition();
                            if (v3 -> x == v.x && v3 -> z == v.z) {
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
        v.y = Game::Instance() -> getGameState()  -> getTerrain() -> getY(v.x, v.z);
    }
    return v;
}

void IA::deployTroops() {
    Vector3<float> v = *(IA::getInstance() -> getBuildingManager() -> getBuildings() -> begin() -> second -> getPosition());
    v.x = v.x + 100;
    v.y = Game::Instance() -> getGameState() -> getTerrain() -> getY(v.x, v.z);
    IA::getInstance() -> getUnitManager() -> deployAllTroops(v);
    deployedTroops = true;
}

void IA::closeDoors() {
    // ToDo: hacer de verdad
    closedDoors = true;
}

void IA::openDoors() {
    // ToDo: hacer de verdad
    closedDoors = false;
}

/*
* Troops come back to their building (barn, barrack or workshop)
*/
void IA::retractTroops() {
    Vector3<float> v = *(IA::getInstance() -> getBuildingManager() -> getBuildings() -> begin() -> second -> getPosition());
    IA::getInstance() -> getUnitManager() -> retractAllTroops(v);
}

bool IA::getUnderAttack() {
    if(underAttack == false){
        Vector3<float> *pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        int requesterRange = 1000;
        
        float xaux = 0;
        float yaux = 0;
        float dist = 0;

        // Get units in the map of the opposing team
        std::map<int, Unit*> *inMapTroops = Human::getInstance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<int,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it){
            if (it -> second != NULL) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() -> x - pos -> x;
                yaux = it -> second -> getPosition() -> y - pos -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange) {
                    underAttack = true;
                }
            }
        }
    }
    return underAttack;
}

void IA::chooseBehaviour() {
    // RAndomize the seed
    srand(time(NULL));
    // Determine a number between 0 and 4, the number of possible behaviours for the AI to choose
    behaviour = (Enumeration::IABehaviour)(rand()%(4-0 + 1) + 0);
    switch (behaviour) {
        case Enumeration::IABehaviour::VeryHappy: 
            chosenBehaviour = "Very happy";
        break;
        case Enumeration::IABehaviour::Happy: 
            chosenBehaviour = "Happy";    
        break;
        case Enumeration::IABehaviour::Neutral:
            chosenBehaviour = "Neutral"; 
        break;
        case Enumeration::IABehaviour::Unhappy: 
            chosenBehaviour = "Unhappy";
        break;
        case Enumeration::IABehaviour::VeryUnhappy: 
            chosenBehaviour = "Very unhappy";
        break;
    }
}

// Return wether or not our troops are deployed
bool IA::getDeployedTroops() {
    return deployedTroops;
}

bool IA::getClosedDoors() {
    return closedDoors;
}

std::string IA::getNextChoice() {
    return choices -> at(choiceIndex);
}

void IA::setChoiceIndex(int newIndex) {
    choiceIndex = newIndex;
}

std::string IA::getChosenBehaviour() {
    return chosenBehaviour;
}

// Down here so it doesn't clutter the constructor
void IA::initializeChoices() {
    //IMPORTANTE::::::::
    // TIENE QUE ESTAR EN EL ORDEN DE LA ENUMERACION
    // IAChoices QUE HAY EN enumeration.h, SI NO NO IRA BIEN
    // Y NOS LIAREMOS. SI SE PUEDE PASAR ALGUN DIA A ARRAY
    // ENTONCES SE PUEDE QUEDAR CONTROLAR QUE INDICE TIENE QUE STRING
    // Y TODO ES MAS MANEJABLE. PERO POR AHORA NO HACE MAS QUE DAR ERRORES
    // ASI QUE LO HE DEJADO COMO VECTOR Y AU (Y quizas un map?)
    choices = new std::vector<std::string>();
    choices -> push_back("Closing Doors");
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
    choices[Enumeration::IAChoices::ClosingDoors] = "Closing doors";
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
    //choices[0] = "Home"
    */
}