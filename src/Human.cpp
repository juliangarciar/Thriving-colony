#include "Human.h"

#include "Enumeration.h"
#include "Player.h"
#include "IA.h"
#include "GraphicEngine/Window.h"
#include "IOEngine/IO.h"
#include <OBDEngine/ResourceManager/ResourceJSON.h>

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
    buildings = new BuildingManager(Enumeration::Team::Human, "kaonov");
    units = new UnitManager(Enumeration::Team::Human, "kaonov");
    
}

void Human::Update() {
    buildings -> updateBuildingManager();
    units -> updateUnitManager();
    updateTimer ->tick();
}

void Human::CleanUp() {
// Add a call to clean the cells the buildings inhabit
    delete buildings;
    delete units;
    delete updateTimer;
}

bool Human::getUnderAttack() {
    if(underAttack == false){
        Vector2<f32> pos = buildings -> getBuildings() -> begin() -> second -> getPosition();
        i32 requesterRange = 1000;
        
        f32 xaux = 0;
        f32 yaux = 0;
        f32 dist = 0;
        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = IA::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end() && underAttack == false; ++it){
            if (it  -> second != nullptr) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition().x - pos.x;
                yaux = it -> second -> getPosition().y - pos.y;
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