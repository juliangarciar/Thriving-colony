#include "ADeployTroops.h"
#include "../IOEngine/IO.h"

ADeployTroops::ADeployTroops() : Action() {

}

ADeployTroops::~ADeployTroops() {

}

Enumeration::BehaviourState ADeployTroops::Update() {
    if (IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        Execute();
        return Enumeration::BehaviourState::Success;
    } else {
        return Enumeration::BehaviourState::Failure;
    }
}

void ADeployTroops::Execute() {
    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::DeployTroopsIA);
}