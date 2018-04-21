#include "CAttack.h"
#include "../IA.h"
#include "../Map.h"

CAttack::CAttack(Action* relatedAction) : Condition(relatedAction) {

}

CAttack::~CAttack() {
    
}

Enumeration::BehaviourState CAttack::Update() {
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::Attacking);
        action -> Update();
        return Enumeration::BehaviourState::Success;
    } else {
        return Enumeration::BehaviourState::Failure;
    }
}