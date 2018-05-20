#include "CRecruit.h"
#include "../IA.h"

CRecruit::CRecruit(Action* relatedAction, std::string typeUnit, i32 unitMetalCost, i32 unitCrystalCost):Condition(relatedAction) {
    type = typeUnit;
    metal = unitMetalCost;
    crystal = unitCrystalCost;
	citizens = 10; //ToDo: parametrizar
}

CRecruit::~CRecruit() {

}

Enumeration::BehaviourState CRecruit::Update() {
    if (IA::Instance() -> getRootNode() -> getPriority() == nullptr) {
        if (IA::Instance() -> getTree() -> getNeedSoldiers()) {
            if (type == "AdvancedM") {
                    if (IA::Instance() -> getTree() -> getRequireBarn() == false && IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                        if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMountedCreatureMilestone()) {
                            IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedMelee);
                            actionToDo();
                            return Enumeration::BehaviourState::Success;
                        }
                    }
            } else if (type == "AdvancedR") {
                    if (IA::Instance() -> getTree() -> getRequireBarn() == false && IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                        if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree()  -> getMountedCreatureMilestone()) {
                            IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMountedRanged);
                            actionToDo();
                            return Enumeration::BehaviourState::Success;
                        }
                    }
            } else if (type == "Desintegrator") {
                    if (IA::Instance() -> getTree() -> getRequireWorkshop() == false && IA::Instance() -> getUnitManager() -> getTroopAmount("Desintegrator") <= IA::Instance() -> getUnitManager() -> getTroopAmount("Launcher")) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainRam);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
            } else if (type == "Idol") {
                    if (IA::Instance() -> getTree() -> getRequireBarn() == false && IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                        if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getCreatureMilestone()) {
                            IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainCreature);
                            actionToDo();
                            return Enumeration::BehaviourState::Success;
                        }
                    }
            } else if (type == "Launcher") {
                    if (IA::Instance() -> getTree() -> getRequireWorkshop() == false) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainCatapult);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
            } else if (type == "StandardM") {
                    if (IA::Instance() -> getTree() -> getRequireBarrack() == false && IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMeleeFootman);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
            } else if (type == "DefenseStandardM") {
                    if (IA::Instance() -> getUnderAttack() == true && IA::Instance() -> getTree() -> getRequireBarrack() == false) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainMeleeFootman);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
            } else if (type == "StandardR") {
                    if (IA::Instance() -> getTree() -> getRequireBarrack() == false && IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::TrainRangedFootman);
                        actionToDo();
                        return Enumeration::BehaviourState::Success;
                    }
            }
        }
        return Enumeration::BehaviourState::Failure;
    } else {
        actionToDo();
        return Enumeration::BehaviourState::Success;
    }
}

void CRecruit::actionToDo() {
    if (IA::Instance() -> isSolvent(metal, crystal, citizens)) {
        action -> Update(type);
        IA::Instance() -> getRootNode() -> setPriority(nullptr);
    } else {
        IA::Instance() -> getRootNode() -> setPriority(this);
    }
}