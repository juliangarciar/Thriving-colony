#include "ARecruit.h"
#include "../IA.h"

ARecruit::ARecruit() : Action() {

}

ARecruit::~ARecruit() {

}

Enumeration::BehaviourState ARecruit::Update(Enumeration::UnitType type) {
    if (type == Enumeration::UnitType::DefenseStandardM) {
        type = Enumeration::UnitType::StandardM;
    }
    IA::Instance() -> getUnitManager() -> createTroop(type);
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARecruit::Update() {
    return Enumeration::BehaviourState::Failure;
}

Enumeration::BehaviourState ARecruit::Update(Enumeration::BuildingType) {
    return Enumeration::BehaviourState::Failure;
}