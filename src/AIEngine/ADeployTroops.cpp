#include "ADeployTroops.h"
#include "../IOEngine/IO.h"
#include "../IA.h"

ADeployTroops::ADeployTroops() : Action() {

}

ADeployTroops::~ADeployTroops() {

}

Enumeration::BehaviourState ADeployTroops::Update() {
    IO::Instance() -> getEventManager() -> triggerEvent("DeployTroopsIA");
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ADeployTroops::Update(std::string) {
    return Enumeration::BehaviourState::Failure;
}