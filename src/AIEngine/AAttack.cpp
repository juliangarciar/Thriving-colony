#include "AAttack.h"
#include "../IA.h"
#include "../Human.h"
#include "../Map.h"

AAttack::AAttack() : Action() {

}

AAttack::~AAttack() {

}

Enumeration::BehaviourState AAttack::Update() {
    IA::Instance() -> getUnitManager() -> deployAllTroops(Human::Instance() -> hallPosition.toVector2());
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState AAttack::Update(std::string) {
    return Enumeration::BehaviourState::Failure;
}