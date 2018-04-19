#include "ABuild.h"
#include "../IA.h"

ABuild::ABuild() : Action() {

}

ABuild::~ABuild() {

}

Enumeration::BehaviourState ABuild::Update(Enumeration::BuildingType type) {
    Vector3<f32> v = IA::Instance() -> determinatePositionBuilding();
    switch (type) {
        case Enumeration::BuildingType::Barn :
            IA::Instance() -> getTree() -> setRequireBarn(false);
        break;
        case Enumeration::BuildingType::Barrack :
            IA::Instance() -> getTree() -> setRequireBarrack(false);
        break;
        case Enumeration::BuildingType::House : 
            IA::Instance() -> getTree() -> setRequireCitizens(false);
        break;
        case Enumeration::BuildingType::Quarry : 
            IA::Instance() -> getTree() -> setRequireCrystal(false);
        break;
        break;
        case Enumeration::BuildingType::Workshop : 
            IA::Instance() -> getTree() -> setRequireBarrack(false);
        break;
    }
    IA::Instance() -> getBuildingManager() -> buildBuilding(v, type, false);
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ABuild::Update() {
    return Enumeration::BehaviourState::Failure;
}

Enumeration::BehaviourState ABuild::Update(Enumeration::UnitType) {
    return Enumeration::BehaviourState::Failure;
}