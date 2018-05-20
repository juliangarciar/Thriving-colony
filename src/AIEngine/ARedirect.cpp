#include "ARedirect.h"
#include "../IA.h"
#include "../Human.h"
#include "../Map.h"

ARedirect::ARedirect() : Action() {

}

ARedirect::~ARedirect() {

}

Enumeration::BehaviourState ARedirect::Update() {
    if (IA::Instance()->getIdleTroops()) {
        if (IA::Instance() -> getTree() -> readyToAttack()) {
            IA::Instance() -> getUnitManager() -> commandAttack(Human::Instance() -> hallPosition.toVector2());
        } else {
            IA::Instance() -> getUnitManager() -> retractAllTroops();
        }
    }
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARedirect::Update(std::string) {
    return Enumeration::BehaviourState::Failure;
}