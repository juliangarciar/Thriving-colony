#include "ARecruit.h"
#include "../IA.h"

ARecruit::ARecruit(Enumeration::UnitType typeUnit) : Action() {
    type = typeUnit;
}

ARecruit::~ARecruit() {

}

Enumeration::BehaviourState ARecruit::Update() {
    if (IA::Instance() -> getTree() -> getNeedSoldiers()) {
        switch (type) {
            case Enumeration::UnitType::AdvancedM : 
                if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                    if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMountedCreatureMilestone()) {
                        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedMeleeMetalCost, Enumeration::UnitCost::MountedMeleeCrystalCost)) {
                            Execute();
                            IA::Instance() -> getRootNode() -> setPriority(NULL);
                        } else {
                            IA::Instance() -> getRootNode() -> setPriority(this);
                        }
                        return Enumeration::BehaviourState::Success;
                    }
                }
            break;
            case Enumeration::UnitType::AdvancedR : 
                if (IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                    if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree()  -> getMountedCreatureMilestone()) {
                        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MountedRangedMetalCost, Enumeration::UnitCost::MountedRangedCrystalCost)) {
                            Execute();
                            IA::Instance() -> getRootNode() -> setPriority(NULL);
                        } else {
                            IA::Instance() -> getRootNode() -> setPriority(this);
                        }
                        return Enumeration::BehaviourState::Success;
                    }
                }
            break;
            case Enumeration::UnitType::Desintegrator : 
                if (IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Desintegrator) <= IA::Instance() -> getUnitManager() -> getTroopAmount(Enumeration::UnitType::Launcher)) {
                    if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RamMetalCost, Enumeration::UnitCost::RamCrystalCost)) {
                        Execute();
                        IA::Instance() -> getRootNode() -> setPriority(NULL);
                    } else {
                        IA::Instance() -> getRootNode() -> setPriority(this);
                    }
                    return Enumeration::BehaviourState::Success;
                }
            break;
            case Enumeration::UnitType::Idol : 
                if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                    if (IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getCreatureMilestone()) {
                        if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CreatureMetalCost, Enumeration::UnitCost::CreatureCrystalCost)) {
                            Execute();
                            IA::Instance() -> getRootNode() -> setPriority(NULL);
                        } else {
                            IA::Instance() -> getRootNode() -> setPriority(this);
                        }
                        return Enumeration::BehaviourState::Success;
                    }
                }
            break;
            case Enumeration::UnitType::Launcher : 
                if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::CatapultMetalCost, Enumeration::UnitCost::CatapultCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            break;
            case Enumeration::UnitType::StandardM : 
                if (IA::Instance() -> getTree() -> calculateMeleeRate() < IA::Instance() -> getTree() -> getMeleeThreshold()) {
                    if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::MeleeFootmenMetalCost, Enumeration::UnitCost::MeleeFootmenCrystalCost)) {
                        Execute();
                        IA::Instance() -> getRootNode() -> setPriority(NULL);
                    } else {
                        IA::Instance() -> getRootNode() -> setPriority(this);
                    }
                    return Enumeration::BehaviourState::Success;
                }
            break;
            case Enumeration::UnitType::StandardR : 
                if (IA::Instance() -> getTree() -> calculateRangeRate() < IA::Instance() -> getTree()  -> getRangeThreshold()) {
                    if (IA::Instance() -> getUnitManager() -> isSolvent(Enumeration::UnitCost::RangedFootmenMetalCost, Enumeration::UnitCost::RangedFootmenCrystalCost)) {
                        Execute();
                        IA::Instance() -> getRootNode() -> setPriority(NULL);
                    } else {
                        IA::Instance() -> getRootNode() -> setPriority(this);
                    }
                    return Enumeration::BehaviourState::Success;
                }
            break;
        }
    }
    return Enumeration::BehaviourState::Failure;
}

void ARecruit::Execute() {
    IA::Instance() -> getUnitManager() -> createTroop(type);
}