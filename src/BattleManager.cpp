#include "BattleManager.h"
#include "Human.h"
#include "IA.h"

BattleManager::BattleManager() {
    
}

BattleManager::~BattleManager() {
     std::cout << "Destructor de BattleManager init" << std::endl;
     std::cout << "Destructor de BattleManager finish" << std::endl;
}

void BattleManager::askForTarget(Entity* requester) {
    Vector2<f32> requesterPos = requester -> getPosition();
    i32 requesterRange = requester -> getViewRadius();
    Entity* target = nullptr;
    f32 minDistance = FLT_MAX; // Maximum value of f32
    
    f32 xaux = 0;
    f32 yaux = 0;
    f32 dist = 0;

    if (requester  -> getTeam() == Enumeration::Team::Human) { // Requester is human
        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = IA::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
            if (it  -> second != nullptr) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() . x - requesterPos . x;
                yaux = it -> second -> getPosition() . y - requesterPos . y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange && dist < minDistance) {
                    minDistance = dist;
                    target = it -> second;
                    target -> addHostile(requester);
                }
            }
        }
        if (target == nullptr) { // No target unit found, search buildings
            std::map<i32, Building*> *buildings = IA::Instance() -> getBuildingManager() -> getBuildings();
            for (std::map<i32,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
                if (it  -> second != nullptr) {
                // Calculate distance between troop requesting target and posible targets
                    xaux = it -> second -> getPosition() . x - (requesterPos . x);
                    yaux = it -> second -> getPosition() . y - (requesterPos . y);
                    dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                    if (dist <= requesterRange && dist < minDistance) {
                        minDistance = dist;
                        target = it -> second;
                        target -> addHostile(requester);
                    }
                }
            }
        }
    } else { // Requester is IA
        // Get units in the map of the opposing team
        std::map<i32, Unit*> *inMapTroops = Human::Instance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<i32,Unit*>::iterator it = inMapTroops -> begin(); it != inMapTroops -> end(); ++it) {
            if (it  -> second != nullptr) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() . x - requesterPos . x;
                yaux = it -> second -> getPosition() . y - requesterPos . y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange && dist < minDistance) {
                    minDistance = dist;
                    target = it -> second;
                    target -> addHostile(requester);
                }
            }
        }
        
        if (target == nullptr) { // No target unit found, search buildings
            std::map<i32, Building*> *buildings = Human::Instance() -> getBuildingManager() -> getBuildings();
            for (std::map<i32,Building*>::iterator it = buildings -> begin(); it != buildings -> end(); ++it) {
                if (it  -> second != nullptr) {
                // Calculate distance between troop requesting target and posible targets
                    xaux = it -> second -> getPosition() . x - requesterPos . x;
                    yaux = it -> second -> getPosition() . y - requesterPos . y;
                    dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                    if (dist <= requesterRange && dist < minDistance) {
                        minDistance = dist;
                        target = it -> second;
                        target -> addHostile(requester);
                    }
                }
            }
        }
    }
    requester -> setTarget(target);
}