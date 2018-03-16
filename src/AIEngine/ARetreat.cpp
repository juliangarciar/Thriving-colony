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