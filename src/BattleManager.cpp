#include "BattleManager.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"



BattleManager::BattleManager() {
    
}

BattleManager::~BattleManager() {

}



void BattleManager::askForTarget(Entity* requester) {

    Vector3<float> *requesterPos = requester -> getPosition();
    int requesterRange = requester -> getAttackRange();
    Entity* target = NULL;
    float minDistance = FLT_MAX; // Maximum value of float
    
    float xaux = 0;
    float yaux = 0;
    float dist = 0;

    if (requester ->getTeam() == Enumeration::Team::Human) { // Requester is human
        
        // Get units in the map of the opposing team
        std::map<int, Unit*> *inMapTroops = IA::getInstance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<int,Unit*>::iterator it = inMapTroops->begin(); it != inMapTroops->end(); ++it){
            if (it ->second != NULL) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() -> x - requesterPos -> x;
                yaux = it -> second -> getPosition() -> y - requesterPos -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange && dist < minDistance) {
                    minDistance = dist;
                    target = it -> second;
                }
            }
        }
        
        if (target == NULL) { // No target unit found, search buildings
            
            std::map<int, Building*> *buildings = IA::getInstance() -> getBuildingManager() -> getBuildings();
            for (std::map<int,Building*>::iterator it = buildings->begin(); it != buildings->end(); ++it){
                if (it ->second != NULL) {
                // Calculate distance between troop requesting target and posible targets
                    xaux = it -> second -> getPosition() -> x - requesterPos -> x;
                    yaux = it -> second -> getPosition() -> y - requesterPos -> y;
                    dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                    if (dist <= requesterRange && dist < minDistance) {
                        minDistance = dist;
                        target = it -> second;
                    }
                }
            }
        }

    } else { // Requester is IA

        // Get units in the map of the opposing team
        std::map<int, Unit*> *inMapTroops = Human::getInstance() -> getUnitManager() -> getInMapTroops();
        // Iterate through the map
        for (std::map<int,Unit*>::iterator it = inMapTroops->begin(); it != inMapTroops->end(); ++it){
            if (it ->second != NULL) {
            // Calculate distance between troop requesting target and posible targets
                xaux = it -> second -> getPosition() -> x - requesterPos -> x;
                yaux = it -> second -> getPosition() -> y - requesterPos -> y;
                dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                if (dist <= requesterRange && dist < minDistance) {
                    minDistance = dist;
                    target = it -> second;
                }
            }
        }
        
        if (target == NULL) { // No target unit found, search buildings
            
            std::map<int, Building*> *buildings = Human::getInstance() -> getBuildingManager() -> getBuildings();
            for (std::map<int,Building*>::iterator it = buildings->begin(); it != buildings->end(); ++it){
                if (it ->second != NULL) {
                // Calculate distance between troop requesting target and posible targets
                    xaux = it -> second -> getPosition() -> x - requesterPos -> x;
                    yaux = it -> second -> getPosition() -> y - requesterPos -> y;
                    dist = sqrtf(pow(xaux, 2) - pow(yaux, 2));

                    if (dist <= requesterRange && dist < minDistance) {
                        minDistance = dist;
                        target = it -> second;
                    }
                }
            }
        }
    }
    requester -> updateTarget(target);
}