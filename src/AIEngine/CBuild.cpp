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
    if (IA::Instance() -> getRootNode() -> getPriority() == NULL) {
        switch (type) {
            case Enumeration::BuildingType::Barn : 
                if (IA::Instance() -> getTree() -> getNeedBarn()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarn);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::Barrack : 
                if (IA::Instance() -> getTree() -> getNeedBarracks()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::DefenseBarrack : 
                if (IA::Instance() -> getUnderAttack() == true && IA::Instance() -> getTree() -> getNeedBarracks()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildBarrack);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::Hospital : 
                if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getHospitalMilestone()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHospital);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::House : 
                if (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHome);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::LastChoiceHouse : 
                IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildHome);
                actionToDo();
                return Enumeration::BehaviourState::Success;
            break;
            case Enumeration::BuildingType::Market : 
                if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMarketMilestone()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildMarket);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::Quarry : 
                if (IA::Instance() -> getTree() -> getRequireCrystal() || (IA::Instance() -> getTree() -> getShortOnCrystal() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getQuarryMilestone())) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildQuarry);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::School : 
                if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildSchool);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::Siderurgy : 
                if (IA::Instance() -> getTree() -> getShortOnMetal()) { 
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildSiderurgy);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
            case Enumeration::BuildingType::Workshop : 
                if (IA::Instance() -> getTree() -> getNeedWorkshop()) {
                    IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::BuildWorkshop);
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                } else {
                    return Enumeration::BehaviourState::Failure;
                }
            break;
        }
    } else {
        actionToDo();
        return Enumeration::BehaviourState::Success;
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