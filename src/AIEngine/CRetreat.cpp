#include "CRetreat.h"
#include "../IA.h"

CRetreat::CRetreat(Action* relatedAction) : Condition(relatedAction) {
    
}

CRetreat::~CRetreat() {

}

Enumeration::BehaviourState CRetreat::Update() {
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() && IA::Instance() -> getTree() -> readyToAttack()) {
        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::RetractingTroops);
        action -> Update();
        return Enumeration::BehaviourState::Success;
    }
    return Enumeration::BehaviourState::Failure;
}