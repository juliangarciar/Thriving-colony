#include "Human.h"
#include "Game.h"

Human* Human::instance = 0;

Human* Human::Instance() {
    if (instance == 0) {
        instance = new Human();
    }
    return instance;
}

Human::Human() : Player() {
    
}

Human::~Human() {
    delete buildings;
    delete units;
}

void Human::Init() {
    Player::Init();
    buildings = new BuildingManager(Enumeration::Team::Human, Enumeration::BreedType::Drorania);
    units = new UnitManager(Enumeration::Team::Human, Enumeration::BreedType::Drorania);
}

void Human::Update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    if (updateTimer <= 0.0) {
        gainResources();
        updateTimer = 1.0;
    } else {
       updateTimer -= Game::Instance() -> getWindow() -> getDeltaTime();
    }
}

void Human::CleanUp() {
    delete buildings;
    delete units;
}

bool Human::getUnderAttack() {
    if(underAttack == false){
        Vector3<f32> *pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        i32 requesterRange = 1000;
        
        f32 xaux = 0;
        f32 yaux = 0;
        f32 dist = 0;
        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = IA::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it){
            if (it  -> second != NULL) {
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

/*
void Human::receiveMetal() {
    metalAmount = metalAmount + 200;
}

void Human::receiveCrystal() {
    crystalAmount = crystalAmount + 200;
}

void Human::receiveCitizens() {
    citizens = citizens + 100;
}
*/