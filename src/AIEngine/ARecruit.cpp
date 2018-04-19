#include "ARecruit.h"
#include "../IA.h"

ARecruit::ARecruit() : Action() {

}

ARecruit::~ARecruit() {

}

Enumeration::BehaviourState ARecruit::Update(Enumeration::UnitType type) {
    IA::Instance() -> getUnitManager() -> createTroop(type);
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARecruit::Update() {
    return Enumeration::BehaviourState::Failure;
}

Enumeration::BehaviourState ARecruit::Update(Enumeration::BuildingType) {
    return Enumeration::BehaviourState::Failure;
}