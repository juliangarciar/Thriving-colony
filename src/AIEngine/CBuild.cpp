#include "CBuild.h"
#include "../IA.h"

CBuild::CBuild(Action* relatedAction, Enumeration::BuildingType buildingType, Enumeration::BuildingCost buildingMetalCost, Enumeration::BuildingCost BuildingCrystalCost) : Condition(relatedAction) {
    type = buildingType;
    metal = buildingMetalCost;
    crystal = BuildingCrystalCost;
}

CBuild::~CBuild() {

}

Enumeration::BehaviourState CBuild::Update() {
    switch (type) {
        case Enumeration::BuildingType::Barn : 
            if (IA::Instance() -> getTree() -> getNeedBarn()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Barrack : 
            if (IA::Instance() -> getTree() -> getNeedBarracks()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Hospital : 
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getHospitalMilestone()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::House : 
            if (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Market : 
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMarketMilestone()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Quarry : 
            if (IA::Instance() -> getTree() -> getRequireCrystal() || (IA::Instance() -> getTree() -> getShortOnCrystal() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getQuarryMilestone())) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::School : 
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Siderurgy : 
            if (IA::Instance() -> getTree() -> getShortOnMetal()) { 
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Workshop : 
            if (IA::Instance() -> getTree() -> getNeedWorkshop()) {
                actionToDo();
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
    }
}

void CBuild::actionToDo() {
    if (IA::Instance() -> getBuildingManager() -> isSolvent(metal, crystal)) {
        action -> Update(type);
        IA::Instance() -> getRootNode() -> setPriority(NULL);
    } else {
        IA::Instance() -> getRootNode() -> setPriority(this);
    }
}