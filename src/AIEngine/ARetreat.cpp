#include "ARetreat.h"
#include "../IOEngine/IO.h"

ARetreat::ARetreat() : Action() {
    
}

ARetreat::~ARetreat() {

}

Enumeration::BehaviourState ARetreat::Update() {
    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::EventType::RetractTroopsIA);
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARetreat::Update(Enumeration::UnitType) {
    return Enumeration::BehaviourState::Failure;
}

Enumeration::BehaviourState ARetreat::Update(Enumeration::BuildingType) {
    return Enumeration::BehaviourState::Failure;
}