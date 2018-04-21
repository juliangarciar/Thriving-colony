#include "CDeployTroops.h"
#include "../IOEngine/IO.h"
#include "../IA.h"

CDeployTroops::CDeployTroops(Action* relatedAction) : Condition(relatedAction) {

}

CDeployTroops::~CDeployTroops() {

}

Enumeration::BehaviourState CDeployTroops::Update() {
    if (IA::Instance() -> getUnderAttack() == true && IA::Instance() -> getUnitManager() -> areTroopsDeployed() == false) {
        std::cout<<"llega11"<<std::endl;
        IA::Instance() -> setChoiceIndex(Enumeration::IAChoices::DeployingTroops);
        action -> Update();
        return Enumeration::BehaviourState::Success;
    } else {
        std::cout<<"llega12"<<std::endl;
        return Enumeration::BehaviourState::Failure;
    }
}