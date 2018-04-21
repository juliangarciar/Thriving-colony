#include "CDeployTroops.h"
#include "../IOEngine/IO.h"
#include "../IA.h"

CDeployTroops::CDeployTroops(Action* relatedAction) : Condition(relatedAction) {

}

CDeployTroops::~CDeployTroops() {

}

Enumeration::BehaviourState CDeployTroops::Update() {
    if (IA::Instance() -> getUnderAttack() == true && IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::DeployingTroops);
        action -> Update();
        return Enumeration::BehaviourState::Success;
    } else {
        return Enumeration::BehaviourState::Failure;
    }
}