#include "CRetreat.h"
#include "../IA.h"

CRetreat::CRetreat(Action* relatedAction) : Condition(relatedAction) {
    
}

CRetreat::~CRetreat() {

}

Enumeration::BehaviourState CRetreat::Update() {
    //if (IA::Instance() -> losingBattle()) {
        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::RetractingTroops);
        action -> Update();
        return Enumeration::BehaviourState::Success;
    //}
    return Enumeration::BehaviourState::Failure;
}