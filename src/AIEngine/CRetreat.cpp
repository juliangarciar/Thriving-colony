#include "CRetreat.h"
#include "../IA.h"

CRetreat::CRetreat(Action* relatedAction) : Condition(relatedAction) {
    
}

CRetreat::~CRetreat() {

}

Enumeration::BehaviourState CRetreat::Update() {
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() && IA::Instance() -> getTree() -> readyToAttack()) {
        std::cout << "NO TENGO TROPAS" << std::endl;
        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::RetractingTroops);
        action -> Update();
        return Enumeration::BehaviourState::Success;
    }
    return Enumeration::BehaviourState::Failure;
}