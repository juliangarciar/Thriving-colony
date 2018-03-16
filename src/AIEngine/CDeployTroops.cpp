#include "CDeployTroops.h"
#include "../IOEngine/IO.h"
#include "../IA.h"

CDeployTroops::CDeployTroops(Action* relatedAction) : Condition(relatedAction) {

}

CDeployTroops::~CDeployTroops() {

}

Enumeration::BehaviourState CDeployTroops::Update() {
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        action -> Update();
        return Enumeration::BehaviourState::Success;
    } else {
        return Enumeration::BehaviourState::Failure;
    }
}