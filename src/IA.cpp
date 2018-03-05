#include "IA.h"

#include "GraphicEngine/Window.h"
#include "Human.h"
#include "Map.h"

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
    delete nodeRootIA;
    delete buildings;
    delete units;
    choices -> clear();
    delete choices;
}

void IA::Init() {
    Player::Init();
    // Choose a behaviour
    chooseBehaviour();
    // Create a behaviour and a root node and set them up according to the behaviour
    tree = new BehaviourTree();
    tree -> init(behaviour);
    nodeRootIA = new RootNode();
    nodeRootIA -> init(behaviour);

    buildings = new BuildingManager(Enumeration::Team::IA, Enumeration::BreedType::Drorania);
    units = new UnitManager(Enumeration::Team::IA, Enumeration::BreedType::Kaonov);

    // Choices for the debugging system
    choiceIndex = 0;
    initializeChoices();
}

void IA::Update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    if (updateTimer <= 0.0) {
        gainResources();
        nodeRootIA -> question();
        updateTimer = 1.0;
    } else {
        updateTimer -= Window::Instance() -> getDeltaTime();
    }
}

void IA::CleanUp() {
    delete tree;
    delete nodeRootIA;
    delete buildings;
    delete units;
    choices -> clear();
    delete choices;
}

BehaviourTree* IA::getTree() {
    return tree;
}

/*
* Return a position of the map where there is nothing built
* Goes over the vector of buildings looking up, right, down and left of every building built
* until find the first empty position
*/
Vector3<f32> IA::determinatePositionBuilding() {
    Vector3<f32> v;
    bool found = false;
    bool occupied = false;
    std::map<i32, Building*> *b = buildings -> getBuildings();

    // If it is the first building start always on the same position
    if (b -> size() == 0) {
        /**
         * These coordinates determine the position of the main building
         * the y component of it is determined based on the map
         */
        f32 startingX = 2000;
        f32 startingZ = 2000;
        v.set(startingX, 0, startingZ);
        v.y = Map::Instance() -> getTerrain() -> getY(v.x, v.z);
    } else {

        //When there are some buildings
        Vector3<f32> *v2 = 0;
        Vector3<f32> *v3 = 0;
        for (std::map<i32,Building*>::iterator it = b -> begin(); it != b -> end() && found == false; ++it){
            v2 = it -> second -> getPosition();
            occupied = false;
            v = Vector3<f32>(v2 -> x, v2 -> y, v2 -> z + 200);
            for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                v3 = it2 -> second -> getPosition();
                if (v3 -> x == v.x && v3 -> z == v.z) {
                    occupied = true;
                }
            }
            if (occupied == false ) {
                found = true;
            } else {
                v = Vector3<f32>(v2 -> x + 200, v2 -> y, v2 -> z);
                occupied = false;
                for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                    v3 = it2 -> second -> getPosition();
                    if (v3 -> x == v.x && v3 -> z == v.z) {
                        occupied = true;
                    }
                }
                if (occupied == false ) {
                    found = true;
                } else {
                    v = Vector3<f32>(v2 -> x, v2 -> y, v2 -> z - 200);
                    occupied = false;
                    for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
                        v3 = it2 -> second -> getPosition();
                        if (v3 -> x == v.x && v3 -> z == v.z) {
                            occupied = true;
                        }
                    }
                    if (occupied == false ) {
                        found = true;
                    } else {
                        v = Vector3<f32>(v2 -> x - 200, v2 -> y, v2 -> z);
                        occupied = false;
                        for (std::map<i32,Building*>::iterator it2 = b -> begin(); it2 != b -> end() && occupied == false; ++it2){
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
        v.y = Map::Instance() -> getTerrain() -> getY(v.x, v.z);
    }
    return v;
}

bool IA::getUnderAttack() {
    underAttack = false;
    Vector3<f32> *pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
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
                xaux = it -> second -> getPosition() -> x - pos -> x;
                yaux = it -> second -> getPosition() -> y - pos -> y;
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

std::string IA::getNextChoice() {
    return choices -> at(choiceIndex);
}

void IA::setChoiceIndex(i32 newIndex) {
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
    //choices[0] = "Home"
    */
}