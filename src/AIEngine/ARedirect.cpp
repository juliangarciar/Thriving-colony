#include "ARedirect.h"
#include "../IA.h"
#include "../Human.h"
#include "../Map.h"

ARedirect::ARedirect() : Action() {

}

ARedirect::~ARedirect() {

}

Enumeration::BehaviourState ARedirect::Update() {
    if (IA::Instance()->getIdleTroops()) {

    }
    return Enumeration::BehaviourState::Success;
}

Enumeration::BehaviourState ARedirect::Update(std::string) {
    return Enumeration::BehaviourState::Failure;
}