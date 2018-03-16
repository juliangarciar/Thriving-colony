#include "CRecruit.h"
#include "../IA.h"

CRecruit::CRecruit(Action* relatedAction, Enumeration::UnitType typeUnit, Enumeration::UnitCost unitMetalCost, Enumeration::UnitCost unitCrystalCost) : Condition(relatedAction) {
    type = typeUnit;
    metal = unitMetalCost;
    crystal = unitCrystalCost;
}

CRecruit::~CRecruit() {

}

Enumeration::BehaviourState CRecruit::Update() {
    if (IA::Instance() -> getTree() -> getNeedSoldiers()) {
        switch (type) {
            case Enumeration::UnitType::AdvancedM : 
                if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                    if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMountedCreatureMilestone()) {
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                }
            break;
            case Enumeration::UnitType::AdvancedR : 
                if (IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                    if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree()  -> getMountedCreatureMilestone()) {
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                }
            break;
            case Enumeration::UnitType::Desintegrator : 
                if (IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) <= IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher)) {
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                }
            break;
            case Enumeration::UnitType::Idol : 
                if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                    if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getCreatureMilestone()) {
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                }
            break;
            case Enumeration::UnitType::Launcher : 
                actionToDo();
                return Enumeration::BehaviourState::Success;
            break;
            case Enumeration::UnitType::StandardM : 
                if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                }
            break;
            case Enumeration::UnitType::StandardR : 
                if (IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                    actionToDo();
                    return Enumeration::BehaviourState::Success;
                }
            break;
        }
    }
    return Enumeration::BehaviourState::Failure;
}

void CRecruit::actionToDo() {
    if (IA::Instance() -> getUnitManager() -> isSolvent(metal, crystal)) {
        action -> Update(type);
        IA::Instance() -> getRootNode() -> setPriority(NULL);
    } else {
        IA::Instance() -> getRootNode() -> setPriority(this);
    }
}