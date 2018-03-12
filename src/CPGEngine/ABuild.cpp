#include "ABuild.h"
#include "../IA.h"

ABuild::ABuild(Enumeration::BuildingType typeBuilding) : Action() {
    type = typeBuilding;
}

ABuild::~ABuild() {

}

Enumeration::BehaviourState ABuild::Update() {
    switch (type) {
        case Enumeration::BuildingType::Barn : 
            if (IA::Instance() -> getTree() -> getNeedBarn()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarnMetalCost, Enumeration::BuildingCost::BarnCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Barrack : 
            if (IA::Instance() -> getTree() -> getNeedBarracks()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::BarrackMetalCost, Enumeration::BuildingCost::BarrackCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Hospital : 
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getHospitalMilestone()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HospitalMetalCost, Enumeration::BuildingCost::HospitalCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::House : 
            if (IA::Instance() -> getTree() -> calculateCitizensRate() < IA::Instance() -> getTree() -> getCitizensThreshold()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::HomeMetalCost, Enumeration::BuildingCost::HomeCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Market : 
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getMarketMilestone()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::MarketMetalCost, Enumeration::BuildingCost::MarketCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Quarry : 
            if (IA::Instance() -> getTree() -> getRequireCrystal() || (IA::Instance() -> getTree() -> getShortOnCrystal() && IA::Instance() -> getCityLevel() >= IA::Instance() -> getTree() -> getQuarryMilestone())) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::QuarryMetalCost, Enumeration::BuildingCost::QuarryCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::School : 
            if (IA::Instance() -> getHappiness() < IA::Instance() -> getTree() -> getHappinessThreshold()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::SchoolMetalCost, Enumeration::BuildingCost::SchoolCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Siderurgy : 
            if (IA::Instance() -> getTree() -> getShortOnMetal()) { 
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::SiderurgyMetalCost, Enumeration::BuildingCost::SiderurgyCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
        case Enumeration::BuildingType::Workshop : 
            if (IA::Instance() -> getTree() -> getNeedWorkshop()) {
                if (IA::Instance() -> getBuildingManager() -> isSolvent(Enumeration::BuildingCost::WorkshopMetalCost, Enumeration::BuildingCost::WorkshopCrystalCost)) {
                    Execute();
                    IA::Instance() -> getRootNode() -> setPriority(NULL);
                } else {
                    IA::Instance() -> getRootNode() -> setPriority(this);
                }
                return Enumeration::BehaviourState::Success;
            } else {
                return Enumeration::BehaviourState::Failure;
            }
        break;
    }
}

void ABuild::Execute() {
    switch (type) {
        case Enumeration::BuildingType::Barn :
            IA::Instance() -> getTree() -> setRequireBarn(false);
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barn, false);
        break;
        case Enumeration::BuildingType::Barrack :
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Barrack, false);
        break;
        case Enumeration::BuildingType::Hospital : 
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Hospital, false);
        break;
        case Enumeration::BuildingType::House : 
            IA::Instance() -> getTree() -> setRequireCitizens(false);
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::House, false);
        break;
        case Enumeration::BuildingType::Market : 
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Market, false);
        break;
        case Enumeration::BuildingType::Quarry : 
            IA::Instance() -> getTree() -> setRequireCrystal(false);
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Quarry, false);
        break;
        case Enumeration::BuildingType::School : 
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::School, false);
        break;
        case Enumeration::BuildingType::Siderurgy : 
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Siderurgy, false);
        break;
        case Enumeration::BuildingType::Workshop : 
            IA::Instance() -> getTree() -> setRequireBarrack(false);
            Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
            IA::Instance() -> getBuildingManager() -> buildBuilding(v, Enumeration::BuildingType::Workshop, false);
        break;
    }
}