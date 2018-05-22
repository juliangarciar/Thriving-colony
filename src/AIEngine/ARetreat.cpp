#include "ARetreat.h"
#include "../IOEngine/IO.h"

ARetreat::ARetreat() : Action() {
    
}

ARetreat::~ARetreat() {

}

Enumeration::BehaviourState ARetreat::Update() {
    IO::Instance() -> getEventManager() -> triggerEvent("RetractTroopsIA");
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARetreat::Update(std::string) {
    return Enumeration::BehaviourState::Failure;
}