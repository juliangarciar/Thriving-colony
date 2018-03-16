#include "ADeployTroops.h"
#include "../IOEngine/IO.h"
#include "../IA.h"

ADeployTroops::ADeployTroops() : Action() {

}

ADeployTroops::~ADeployTroops() {

}

Enumeration::BehaviourState ADeployTroops::Update() {
    IO::Instance() -> getEventManager() -> triggerEvent(Enumeration::DeployTroopsIA);
    return Enumeration::BehaviourState::Success;
}