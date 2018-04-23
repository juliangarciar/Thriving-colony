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
    if (IA::Instance() -> getRootNode() -> getPriority() == nullptr) {
        if (IA::Instance() -> getTree() -> getNeedSoldiers()) {
            switch (type) {
                case Enumeration::UnitType::AdvancedM : 
                    if (IA::Instance() -> getTree() -> getRequireBarn() == false && IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                        if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMountedCreatureMilestone()) {
                            IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedMelee);
                            actionToDo();
                            return Enumeration::BehaviourState::Success;
                        }
                    }
                break;
                case Enumeration::UnitType::AdvancedR : 
                    if (IA::Instance() -> getTree() -> getRequireBarn() == false && IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                        if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree()  -> getMountedCreatureMilestone()) {
                            IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedRanged);
                            actionToDo();
                            return Enumeration::BehaviourState::Success;
                        }
                    }
                break;
                case Enumeration::UnitType::Desintegrator : 
                    if (IA::Instance() -> getTree() -> getRequireWorkshop() == false && IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) <= IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher)) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainRam);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                break;
                case Enumeration::UnitType::Idol : 
                    if (IA::Instance() -> getTree() -> getRequireBarn() == false && IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                        if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getCreatureMilestone()) {
                            IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainCreature);
                            actionToDo();
                            return Enumeration::BehaviourState::Success;
                        }
                    }
                break;
                case Enumeration::UnitType::Launcher : 
                    if (IA::Instance() -> getTree() -> getRequireWorkshop() == false) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainCatapult);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                break;
                case Enumeration::UnitType::StandardM : 
                    if (IA::Instance() -> getTree() -> getRequireBarrack() == false && IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMeleeFootman);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                break;
                case Enumeration::UnitType::DefenseStandardM : 
                    if (IA::Instance() -> getUnderAttack() == true && IA::Instance() -> getTree() -> getRequireBarrack() == false) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMeleeFootman);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                break;
                case Enumeration::UnitType::StandardR : 
                    if (IA::Instance() -> getTree() -> getRequireBarrack() == false && IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainRangedFootman);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
                break;
            }
        }
        return Enumeration::BehaviourState::Failure;
    } else {
        actionToDo();
        return Enumeration::BehaviourState::Success;
    }
}

void CRecruit::actionToDo() {
    if (IA::Instance() -> getUnitManager() -> isSolvent(metal, crystal)) {
        action -> Update(type);
        IA::Instance() -> getRootNode() -> setPriority(nullptr);
    } else {
        IA::Instance() -> getRootNode() -> setPriority(this);
    }
}